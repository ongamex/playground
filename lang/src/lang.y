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
%token <no_type>		VOID INT FLOAT
%token <no_type>		LPAREN RPAREN SEMICOLON COMMA BLOCK_BEGIN BLOCK_END
%token <no_type>		IF ELSE WHILE
%token <str_val>		IDENTIFIER
%token <double_val>		NUMBER

%left PLUS MINUS
%left ASTERISK FSLASH

%type <node>	expression
%type <node>	vardecl_var vardecl_var_list vardecl assign_expression
%type <node>	statement
%type <node>	statement_list
%type <node>	type

%start grammar

%%

grammar : statement_list;

type : 
		VOID 	{ $$ = ast->add(new Node(NT_Type, "void")); }
	| 	INT		{ $$ = ast->add(new Node(NT_Type, "int")); }
	|	FLOAT	{ $$ = ast->add(new Node(NT_Type, "float")); }
	;

vardecl_var : 	
		IDENTIFIER { $$ = ast->add(new Node(NT_VarInit, $1->c_str())); }
	;

vardecl_var_list : 
		vardecl_var { $$ = $1; }
	|	vardecl_var EQUALS expression { $$ = $1; $1->nodes.push_back($3); }
	|	vardecl_var_list COMMA vardecl_var { $$ = ast->add(new Node(NT_NtList, {$1, $3})); }
	|	vardecl_var_list COMMA vardecl_var EQUALS expression { 
			$$ = $1; 
			$1->nodes.push_back($3); 
			$3->nodes.push_back($5); 
		}

vardecl :
		type vardecl_var_list SEMICOLON	{ $$ = ast->add(new Node(NT_VarDecl, {$1, $2}));; }
	;
	
statement : 
		
		vardecl { $$ = $1; }
	|	assign_expression SEMICOLON { $$ = $1; }
	|	WHILE LPAREN expression RPAREN statement { $$ = ast->add(new Node(NT_While, {$3, $5})); }
	|	IF LPAREN expression RPAREN statement { $$ = ast->add(new Node(NT_If, {$3, $5})); }
	|	BLOCK_BEGIN statement_list BLOCK_END { $$ = $2; }
	;

statement_list : 
		statement { $$ = ast->add(new Node(NT_NtList, {$1})); }
	|	statement_list statement { 
			$$ = $1;
			$1->nodes.push_back( {$2} );
		}
	;
	
assign_expression : 
		IDENTIFIER EQUALS expression				{ 
			Node* ident = $$ = ast->add(new Node(NT_Identifier, $1->c_str()));
			$$ = ast->add(new Node(NT_Assign, {ident, $3})); 
		}
	;

	
	
expression :
		LPAREN expression RPAREN				{ $$ = $2; }
	|	IDENTIFIER								{ $$ = ast->add(new Node(NT_Identifier, $1->c_str())); }
	|	expression PLUS expression				{ $$ = ast->add(new Node(NT_Add, {$1, $3})); } 
	|	expression MINUS expression				{ $$ = ast->add(new Node(NT_Sub, {$1, $3})); } 	
	|	expression ASTERISK expression			{ $$ = ast->add(new Node(NT_Mul, {$1, $3})); } 
	|	expression FSLASH expression			{ $$ = ast->add(new Node(NT_Div, {$1, $3})); }
	|	NUMBER									{ $$ = ast->add(new Node(NT_Num, $1)); }
	;


%%

void yyerror (yyscan_t yyscanner, char const *msg){
    fprintf(stderr, "%s\n", msg);
}

void yyerror (yyscan_t yyscanner, Ast* ast, char const *msg) {
	yyerror(yyscanner, msg);
}
