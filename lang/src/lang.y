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

%token <no_type>		AND OR LE GE EQUALS NOTEQUALS
%token <no_type>		IF ELSE WHILE FOR
%token <str_val>		IDENT
%token <float_val>		NUM_FLOAT
%token <int_val>		NUM_INT

%left AND OR
%left EQUALS NOTEQUALS
%left LE '<' GE '>'
%left '+' '-'
%left '*' '/'

%type <node>	fncall_args expr_fncall
%type <node>	expr
%type <node>	vardecl_var_list vardecl assign_stmt
%type <node>	stmt
%type <node>	stmt_list function_decl

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
	IDENT IDENT '(' vardecl ')' '{' stmt_list '}' {
		$$ = ast->push<FuncDecl>({$1, $2, $4, $7});
	}
	|
	IDENT IDENT '(' ')' stmt_list {
		$$ = ast->push<FuncDecl>({$1, $2, nullptr, $5});
	}
	;

vardecl_var_list : 
		IDENT 								{ $$ = ast->push<VarDecl>({"unk", {$1}, {nullptr}}); } // unk used for unknown
	|	IDENT '=' expr 						{ $$ = ast->push<VarDecl>({"unk", {$1}, {$3}}); } // unk used for unknown
	|	vardecl_var_list ',' IDENT 			{ $$->As<VarDecl>().ident.push_back($3);	}
	|	vardecl_var_list ',' IDENT '=' expr	{ 
			$$ = $1; 
			$$->As<VarDecl>().ident.push_back($3);
			$$->As<VarDecl>().expr.push_back($5);
		}

vardecl :
		IDENT vardecl_var_list	{ $2->As<VarDecl>().type = $1; $$ = $2; }
	;
	
stmt : 
		vardecl ';'									{ $1->hasSemicolon = true; ; $$ = $1; }
	|	expr ';' 									{ $1->hasSemicolon = true; $$ = $1; }
	|	assign_stmt ';' 							{ $1->hasSemicolon = true; $$ = $1; }
	|	FOR '(' vardecl ';' expr ';' expr ')' stmt	{ $$ = ast->push(StmtFor{$3, $5, $7, $9}); }
	|	WHILE '(' expr ')' stmt 					{ $$ = ast->push(StmtWhile{$3, $5}); }
	|	IF '(' expr ')' stmt 						{ $$ = ast->push(StmtIf($3, $5, nullptr)); }
	|	IF '(' expr ')' stmt ELSE stmt				{ $$ = ast->push(StmtIf($3, $5, $7)); } //[SHIFT-REDUCE]
	|	'{' stmt_list '}' 							{ $2->inBlock = true; $$ = $2; }
	;

stmt_list : 
		stmt 				{ $$ = ast->push<NodeList>({}); $$->As<NodeList>().nodes.push_back($1); }
	|	stmt_list stmt 		{ 
			$$ = $1;
			$1->As<NodeList>().nodes.push_back( {$2} );
		}
	;
	
assign_stmt : 
		IDENT '=' expr				{ $$ = ast->push<Assign>({$1.c_str(), $3}); }
	;

expr :
		'(' expr ')'			{ $2->inParens = true; $$ = $2; }
	|	IDENT					{ $$ = ast->push<Ident>({$1}); }
	|	expr OR expr			{ $$ = ast->push<ExprBin>({EBT_Or, $1, $3}); }
	|	expr AND expr			{ $$ = ast->push<ExprBin>({EBT_And, $1, $3}); }
	|	expr NOTEQUALS expr		{ $$ = ast->push<ExprBin>({EBT_NEquals, $1, $3}); }
	|	expr EQUALS expr		{ $$ = ast->push<ExprBin>({EBT_Equals, $1, $3}); }
	|	expr LE expr			{ $$ = ast->push<ExprBin>({EBT_LEquals, $1, $3}); }
	|	expr '<' expr			{ $$ = ast->push<ExprBin>({EBT_Less, $1, $3}); }
	|	expr GE expr			{ $$ = ast->push<ExprBin>({EBT_GEquals, $1, $3}); }
	|	expr '>' expr			{ $$ = ast->push<ExprBin>({EBT_Greater, $1, $3}); }
	|	expr '+' expr			{ $$ = ast->push<ExprBin>({EBT_Add, $1, $3}); } 
	|	expr '-' expr			{ $$ = ast->push<ExprBin>({EBT_Sub, $1, $3}); } 	
	|	expr '*' expr			{ $$ = ast->push<ExprBin>({EBT_Mul, $1, $3}); } 
	|	expr '/' expr			{ $$ = ast->push<ExprBin>({EBT_Div, $1, $3}); }
	|	NUM_FLOAT				{ $$ = ast->push(ExprLiteral($1)); }
	|	NUM_INT					{ $$ = ast->push(ExprLiteral($1)); }
	|	expr_fncall				{ $$ = $1; }
	;
	
	// Function calls in expr
fncall_args :
		expr					{ $$ = ast->push<FuncCallArgs>({{$1}}); }
	|	fncall_args ',' expr 	{ $1->As<FuncCallArgs>().args.push_back($3); $$ = $1; }
	
expr_fncall :
		IDENT '(' fncall_args ')'	{ $$ = ast->push<FuncCall>({$1, $3}); }
	|	IDENT '(' ')' 				{ $$ = ast->push<FuncCall>({$1, nullptr}); }

%%

void yyerror (yyscan_t yyscanner, char const *msg){
    fprintf(stderr, "%s\n", msg);
}

void yyerror (yyscan_t yyscanner, Ast* ast, char const *msg) {
	yyerror(yyscanner, msg);
}
