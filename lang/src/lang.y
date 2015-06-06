%define api.pure full
%lex-param {yyscan_t scanner}
%parse-param {yyscan_t scanner}
%parse-param {Ast* ast}

%{

#include <string>
#include <cstring>
#include <math.h>
#include <map>
#include "ast.h"
#include "lang.yystype.h"

typedef void* yyscan_t;
void yyerror (yyscan_t yyscanner, char const *msg);
void yyerror (yyscan_t yyscanner, Ast* ast, char const *msg);
int yylex(YYSTYPE *yylval_param, yyscan_t yyscanner);
bool parseExpression(const std::string& inp);
%}

%token <no_type>		AND OR LEQUALS LESS GEQUALS GREATER EQUALS NOTEQUALS
%token <no_type>		ASSIGN MINUS PLUS ASTERISK FSLASH
%token <no_type>		LPAREN RPAREN SEMICOLON COMMA BLOCK_BEGIN BLOCK_END
%token <no_type>		IF ELSE WHILE
%token <str_val>		IDENTIFIER
%token <float_val>		NUM_FLOAT
%token <int_val>		NUM_INT

%left AND OR
%left EQUALS NOTEQUALS
%left LEQUALS LESS GEQUALS GREATER
%left PLUS MINUS
%left ASTERISK FSLASH

%type <node>	fncall_args expression_fncall
%type <node>	expression
%type <node>	vardecl_var_list vardecl assign_statement
%type <node>	statement
%type <node>	statement_list function_decl

%type <node>	program grammar_elem grammar_list

%start program

%%

program : grammar_list { ast->program = $1; $$ = $1; }

grammar_elem :
		function_decl { $$ = $1; }
	;

grammar_list : 
		grammar_elem  				{ $$ = ast->push<ProgramElem>({{$1}}); }
	|	grammar_list grammar_elem	{ $1->As<ProgramElem>().nodes.push_back($2); $$ = $1; }
	;

function_decl : 
	IDENTIFIER IDENTIFIER LPAREN vardecl RPAREN BLOCK_BEGIN statement_list BLOCK_END {
		$$ = ast->push<FuncDecl>({$1, $2, $4, $7});
	}
	|
	IDENTIFIER IDENTIFIER LPAREN RPAREN statement_list {
		$$ = ast->push<FuncDecl>({$1, $2, nullptr, $5});
	}
	;

vardecl_var_list : 
		IDENTIFIER { $$ = ast->push<VarDecl>({"unk", {$1}, {nullptr}}); } // unk used for unknown
	|	IDENTIFIER ASSIGN expression { $$ = ast->push<VarDecl>({"unk", {$1}, {$3}}); } // unk used for unknown
	|	vardecl_var_list COMMA IDENTIFIER { $$->As<VarDecl>().ident.push_back($3);	}
	|	vardecl_var_list COMMA IDENTIFIER ASSIGN expression { 
			$$ = $1; 
			$$->As<VarDecl>().ident.push_back($3);
			$$->As<VarDecl>().expr.push_back($5);
		}

vardecl :
		IDENTIFIER vardecl_var_list	{ $2->As<VarDecl>().type = $1; $$ = $2; }
	;
	
statement : 
		
		vardecl SEMICOLON { $1->hasSemicolon = true; ; $$ = $1; }
	|	expression SEMICOLON { $1->hasSemicolon = true; $$ = $1; }
	|	assign_statement SEMICOLON { $1->hasSemicolon = true; $$ = $1; }
	|	WHILE LPAREN expression RPAREN statement {  $$ = ast->push(StmtWhile($3, $5)); }
	|	IF LPAREN expression RPAREN statement { $$ = ast->push(StmtIf($3, $5, nullptr)); }
	|	IF LPAREN expression RPAREN statement ELSE statement{ $$ = ast->push(StmtIf($3, $5, $7)); } //[SHIFT-REDUCE]
	|	BLOCK_BEGIN statement_list BLOCK_END { $2->inBlock = true; $$ = $2; }
	;

statement_list : 
		statement { $$ = ast->push<NodeList>({}); $$->As<NodeList>().nodes.push_back($1); }
	|	statement_list statement { 
			$$ = $1;
			$1->As<NodeList>().nodes.push_back( {$2} );
		}
	;
	
assign_statement : 
		IDENTIFIER ASSIGN expression				{ 
			$$ = ast->push<Assign>({$1.c_str(), $3});
		}
	;

	
	
expression :
		LPAREN expression RPAREN				{ $2->inParens = true; $$ = $2; }
	|	IDENTIFIER								{ $$ = ast->push<Ident>({$1}); }
	|	expression OR expression				{ $$ = ast->push<ExprBin>({EBT_Or, $1, $3}); }
	|	expression AND expression				{ $$ = ast->push<ExprBin>({EBT_And, $1, $3}); }
	|	expression LEQUALS expression			{ $$ = ast->push<ExprBin>({EBT_LEquals, $1, $3}); }
	|	expression LESS expression				{ $$ = ast->push<ExprBin>({EBT_Less, $1, $3}); }
	|	expression GEQUALS expression			{ $$ = ast->push<ExprBin>({EBT_GEquals, $1, $3}); }
	|	expression GREATER expression			{ $$ = ast->push<ExprBin>({EBT_Greater, $1, $3}); }
	|	expression PLUS expression				{ $$ = ast->push<ExprBin>({EBT_Add, $1, $3}); } 
	|	expression MINUS expression				{ $$ = ast->push<ExprBin>({EBT_Sub, $1, $3}); } 	
	|	expression ASTERISK expression			{ $$ = ast->push<ExprBin>({EBT_Mul, $1, $3}); } 
	|	expression FSLASH expression			{ $$ = ast->push<ExprBin>({EBT_Div, $1, $3}); }
	|	NUM_FLOAT								{ $$ = ast->push(ExprLiteral($1)); }
	|	NUM_INT									{ $$ = ast->push(ExprLiteral($1)); }
	|	expression_fncall						{ $$ = $1; }
	;
	
	// Function calls in expression
fncall_args :
		expression	{ $$ = ast->push<FuncCallArgs>({{$1}}); }
	|	fncall_args COMMA expression { $1->As<FuncCallArgs>().args.push_back($3); $$ = $1; }
	
expression_fncall :
		IDENTIFIER LPAREN fncall_args RPAREN { $$ = ast->push<FuncCall>({$1, $3}); }
	|	IDENTIFIER LPAREN RPAREN { $$ = ast->push<FuncCall>({$1, nullptr}); }

%%

void yyerror (yyscan_t yyscanner, char const *msg){
    fprintf(stderr, "%s\n", msg);
}

void yyerror (yyscan_t yyscanner, Ast* ast, char const *msg) {
	yyerror(yyscanner, msg);
}
