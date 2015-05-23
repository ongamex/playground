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
%token <no_type>		LPAREN RPAREN SEMICOLON BLOCK_BEGIN BLOCK_END
%token <no_type>		IF ELSE
%token <str_val>		VARIABLE
%token <double_val>		NUMBER

%left PLUS MINUS
%left ASTERISK FSLASH

%type <node>	expresson
%type <node>	statement
%type <node>	statement_list

%start grammar

%%

grammar : statement_list;

statement : 
		expresson SEMICOLON { $$ = $1; }
	|	IF LPAREN expresson RPAREN statement { $$ = g_ast.add(new Node(NT_If, {$3, $5})); }
	|	BLOCK_BEGIN statement_list BLOCK_END { $$ = $2; }
	;

statement_list : 
		statement { $$ = $1; }
	|	statement_list statement { $$ = g_ast.add(new Node(NT_NtList, {$1, $2})); }
	;

expresson : 
		NUMBER									{ $$ = g_ast.add(new Node($1)); } 
	|	expresson PLUS expresson				{ $$ = g_ast.add(new Node(NT_Add, {$1, $3})); } 
	|	expresson MINUS expresson				{ $$ = g_ast.add(new Node(NT_Sub, {$1, $3})); } 
	|	expresson ASTERISK expresson			{ $$ = g_ast.add(new Node(NT_Mul, {$1, $3})); } 
	|	expresson FSLASH expresson				{ $$ = g_ast.add(new Node(NT_Div, {$1, $3})); }
	|	LPAREN expresson RPAREN					{ $$ = $2; }
	;
	
%%