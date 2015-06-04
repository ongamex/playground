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

%token <no_type>		EQUALS MINUS PLUS ASTERISK FSLASH 
%token <no_type>		LPAREN RPAREN SEMICOLON COMMA BLOCK_BEGIN BLOCK_END
%token <no_type>		IF ELSE WHILE
%token <str_val>		IDENTIFIER
%token <float_val>		NUMBER

%left PLUS MINUS
%left ASTERISK FSLASH

%type <node>	expression
%type <node>	vardecl_var vardecl_var_list vardecl assign_statement
%type <node>	statement
%type <node>	statement_list

%start grammar

%%

grammar : statement_list;


vardecl_var : 	
		IDENTIFIER { $$ = ast->push<Ident>({$1.c_str()}); }
	;

vardecl_var_list : 
		vardecl_var { $$ = ast->push<VarDecl>({"unk", {$1}, {nullptr}}); } // unk used for unknown
	|	vardecl_var EQUALS expression { $$ = ast->push<VarDecl>({"unk", {$1}, {$3}}); } // unk used for unknown
	|	vardecl_var_list COMMA vardecl_var { $$->As<VarDecl>().ident.push_back($3);	}
	|	vardecl_var_list COMMA vardecl_var EQUALS expression { 
			$$ = $1; 
			$$->As<VarDecl>().ident.push_back($3);
			$$->As<VarDecl>().expr.push_back($5);
		}

vardecl :
		IDENTIFIER vardecl_var_list SEMICOLON	{ $2->As<VarDecl>().type = $1; $$ = $2; }
	;
	
statement : 
		
		vardecl { $$ = $1; }
	|	assign_statement SEMICOLON { $$ = $1; }
	|	WHILE LPAREN expression RPAREN statement {  $$ = ast->push(StmtWhile($3, $5)); }
	|	IF LPAREN expression RPAREN statement { $$ = ast->push(StmtIf($3, $5, nullptr)); }
	|	BLOCK_BEGIN statement_list BLOCK_END { $$ = $2; }
	;

statement_list : 
		statement { $$ = ast->push<NodeList>({}); $$->As<NodeList>().nodes.push_back($1); }
	|	statement_list statement { 
			$$ = $1;
			$1->As<NodeList>().nodes.push_back( {$2} );
		}
	;
	
assign_statement : 
		IDENTIFIER EQUALS expression				{ 
			$$ = ast->push<Assign>({$1.c_str(), $3});
		}
	;

	
	
expression :
		LPAREN expression RPAREN				{ $$ = $2; }
	|	IDENTIFIER								{ $$ = ast->push<Ident>({$1.c_str()}); }
	|	expression PLUS expression				{ $$ = ast->push<ExprBin>({'+',$1, $3}); } 
	|	expression MINUS expression				{ $$ = ast->push<ExprBin>({'-',$1, $3}); } 	
	|	expression ASTERISK expression			{ $$ = ast->push<ExprBin>({'*',$1, $3}); } 
	|	expression FSLASH expression			{ $$ = ast->push<ExprBin>({'/',$1, $3}); }
	|	NUMBER									{ $$ = ast->push<ExprLiteral>({EL_Float, $1}); }
	;


%%

void yyerror (yyscan_t yyscanner, char const *msg){
    fprintf(stderr, "%s\n", msg);
}

void yyerror (yyscan_t yyscanner, Ast* ast, char const *msg) {
	yyerror(yyscanner, msg);
}
