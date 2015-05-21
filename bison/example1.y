%{
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <math.h>
#include <map>
std::map<std::string, double> vars;
extern int yylex();
extern void yyerror(char*);
int yyparse();
%}

%union{
	int int_token;
	double double_val;
	std::string* str_val;
};

%token <int_token>	EQUALS MINUS PLUS ASTERISK FSLASH LPAREN RPAREN SEMICOLON QMARK COLON
%token <str_val>	VARIABLE
%token <double_val>	NUMBER


%type <double_val>	expresson;
%type <double_val>	expresson_level0;
%type <double_val>	expresson_level1;
%type <double_val>	expresson_level2;
%type <double_val>	expresson_level3;
%type <double_val>	function_call_expression;

%start grammar

%%

grammar : expressons;
expressons : | expressons expresson SEMICOLON;


function_call_expression : 
	VARIABLE LPAREN expresson RPAREN {
		if(*$1 == "sqr") { $$ = $3 * $3; }
		else if(*$1 == "sqrt") { $$ = sqrt($3); }
		else if(*$1 == "print") { printf("%f\n", $3); $$ = 0;}
		else if(*$1 == "quit") 	{ if($3) exit(0); $$ = $3; }
		else $$ = 0;
	};

expresson : 
		VARIABLE EQUALS expresson_level0			{ vars[*$1] = $3; $$ = vars[*$1]; }
	|	expresson_level0
	;

expresson_level0 : 
		
		expresson_level0 QMARK expresson_level1 COLON expresson_level1		{ if($1) $$ = $3; else $$ = $5; }
	|	expresson_level1
	;
	
expresson_level1 : 
		expresson_level1 PLUS expresson_level2				{ $$ = $1 + $3; }
	|	expresson_level1 MINUS expresson_level2				{ $$ = $1 - $3; }
	|	expresson_level2
	;
	
expresson_level2 : 

		expresson_level2 ASTERISK expresson_level3	{ $$ = $1 * $3; }
	|	expresson_level2 FSLASH expresson_level3	{ $$ = $1 / $3; }
	|	expresson_level3;
	;
		
expresson_level3 :

		NUMBER							{ $$ = $1; }
	|	VARIABLE						{ $$ = vars[*$1]; }
	|	LPAREN expresson RPAREN 		{ $$ = $2; }
	|	function_call_expression
	;

%%