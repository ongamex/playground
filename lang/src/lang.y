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
		VOID 	{ $$ = g_ast.add(new Node(NT_Type, "void")); }
	| 	INT		{ $$ = g_ast.add(new Node(NT_Type, "int")); }
	|	FLOAT	{ $$ = g_ast.add(new Node(NT_Type, "float")); }
	;

vardecl_var : 	
		IDENTIFIER { $$ = g_ast.add(new Node(NT_VarInit, $1->c_str())); }
	;

vardecl_var_list : 
		vardecl_var { $$ = $1; }
	|	vardecl_var EQUALS expression { $$ = $1; $1->nodes.push_back($3); }
	|	vardecl_var_list COMMA vardecl_var { $$ = g_ast.add(new Node(NT_NtList, {$1, $3})); }
	|	vardecl_var_list COMMA vardecl_var EQUALS expression { 
			$$ = $1; 
			$1->nodes.push_back($3); 
			$3->nodes.push_back($5); 
		}

vardecl :
		type vardecl_var_list SEMICOLON	{ $$ = g_ast.add(new Node(NT_VarDecl, {$1, $2}));; }
	;
	
statement : 
		
		vardecl { $$ = $1; }
	|	assign_expression SEMICOLON { $$ = $1; }
	|	WHILE LPAREN expression RPAREN statement { $$ = g_ast.add(new Node(NT_While, {$3, $5})); }
	|	IF LPAREN expression RPAREN statement { $$ = g_ast.add(new Node(NT_If, {$3, $5})); }
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
		IDENTIFIER EQUALS expression				{ 
			Node* ident = $$ = g_ast.add(new Node(NT_Identifier, $1->c_str()));
			$$ = g_ast.add(new Node(NT_Assign, {ident, $3})); 
		}
	;

	
	
expression :
		LPAREN expression RPAREN					{ $$ = $2; }
	|	IDENTIFIER								{ $$ = g_ast.add(new Node(NT_Identifier, $1->c_str())); }
	|	expression PLUS expression				{ $$ = g_ast.add(new Node(NT_Add, {$1, $3})); } 
	|	expression MINUS expression				{ $$ = g_ast.add(new Node(NT_Sub, {$1, $3})); } 	
	|	expression ASTERISK expression			{ $$ = g_ast.add(new Node(NT_Mul, {$1, $3})); } 
	|	expression FSLASH expression			{ $$ = g_ast.add(new Node(NT_Div, {$1, $3})); }
	|	NUMBER									{ $$ = g_ast.add(new Node(NT_Num, $1)); }
	;


%%