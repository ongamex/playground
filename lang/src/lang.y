%{
#include <string>
#include <cstring>
#include <math.h>
#include <map>

#include "ast.h"

extern int yylex();
extern void yyerror(char*);
int yyparse();
%}

%union{
	struct Node* node;
	std::string* str_val;
	double double_val;
	struct {} no_type;
};

%token <no_type>		EQUALS MINUS PLUS ASTERISK FSLASH 
%token <no_type>		VOID INT FLOAT
%token <no_type>		LPAREN RPAREN SEMICOLON COMMA BLOCK_BEGIN BLOCK_END
%token <no_type>		IF ELSE WHILE
%token <str_val>		IDENTIFIER
%token <double_val>		NUMBER

%left ASTERISK FSLASH

%type <node>	expresson expresson_0 expresson_1 expresson_2
%type <node>	vardecl_var vardecl_var_list vardecl assign_expression
%type <node>	statement
%type <node>	statement_list
%type <node>	type

%start grammar

%%

grammar : statement_list;

type : 
		VOID 	{ $$ = g_ast.add(new Node(NT_Type, "void")); }
	| 	INT		{ $$ = g_ast.add(new Node(NT_Type, "int")); }
	|	FLOAT	{ $$ = g_ast.add(new Node(NT_Type, "float")); }
	;

vardecl_var : 	
		IDENTIFIER { $$ = g_ast.add(new Node(NT_VarInit, $1->c_str())); }
	;

vardecl_var_list : 
		vardecl_var { $$ = $1; }
	|	vardecl_var EQUALS expresson { $$ = $1; $1->nodes.push_back($3); }
	|	vardecl_var_list COMMA vardecl_var { $$ = g_ast.add(new Node(NT_NtList, {$1, $3})); }

vardecl :
		type vardecl_var_list SEMICOLON	{ $$ = g_ast.add(new Node(NT_VarDecl, {$1, $2}));; }
	;
	
statement : 
		
		vardecl { $$ = $1; }
	|	assign_expression SEMICOLON { $$ = $1; }
	|	WHILE LPAREN expresson RPAREN statement { $$ = g_ast.add(new Node(NT_While, {$3, $5})); }
	|	IF LPAREN expresson RPAREN statement { $$ = g_ast.add(new Node(NT_If, {$3, $5})); }
	|	BLOCK_BEGIN statement_list BLOCK_END { $$ = $2; }
	;

statement_list : 
		statement { $$ = g_ast.add(new Node(NT_NtList, {$1})); }
	|	statement_list statement { 
			$$ = $1;
			$1->nodes.push_back( {$2} );
		}
	;
	
assign_expression : 
		IDENTIFIER EQUALS expresson				{ 
			Node* ident = $$ = g_ast.add(new Node(NT_Identifier, $1->c_str()));
			$$ = g_ast.add(new Node(NT_Assign, {ident, $3})); 
		}
	;
expresson : expresson_0;
	
expresson_0 : 
		expresson_0 PLUS expresson_1				{ $$ = g_ast.add(new Node(NT_Add, {$1, $3})); } 
	|	expresson_0 MINUS expresson_1				{ $$ = g_ast.add(new Node(NT_Sub, {$1, $3})); } 
	|	expresson_1
	;
expresson_1 : 
		expresson_1 ASTERISK expresson_2			{ $$ = g_ast.add(new Node(NT_Mul, {$1, $3})); } 
	|	expresson_1 FSLASH expresson_2				{ $$ = g_ast.add(new Node(NT_Div, {$1, $3})); }
	|	expresson_2
	;

expresson_2 :
		LPAREN expresson RPAREN					{ $$ = $2; }
	|	NUMBER									{ $$ = g_ast.add(new Node(NT_Num, $1)); } 
	|	IDENTIFIER								{ $$ = g_ast.add(new Node(NT_Identifier, $1->c_str())); };
	;

%%