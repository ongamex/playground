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

%token <int_token>	EQUALS LPAREN RPAREN SEMICOLON QMARK COLON
%token <str_val>	VARIABLE
%token <double_val>	NUMBER

%left MINUS PLUS 
%left ASTERISK FSLASH



%type <double_val>	expresson;
%type <double_val>	function_call_expression;

%start grammar

%%

grammar : expressons;
expressons : | expressons function_call_expression SEMICOLON;


function_call_expression : 
	VARIABLE LPAREN expresson RPAREN {
		if(*$1 == "sqr") { $$ = $3 * $3; }
		else if(*$1 == "sqrt") { $$ = sqrt($3); }
		else if(*$1 == "print") { printf("%f\n", $3); $$ = 0;}
		else if(*$1 == "quit") 	{ if($3) exit(0); $$ = $3; }
		else $$ = 0;
	};

expresson : 
		NUMBER								{ $$ = $1; }
	|	MINUS expresson						{ $$ = -$2; }
	|	expresson PLUS expresson			{ $$ = $1 + $3; }
	|	expresson MINUS expresson			{ $$ = $1 - $3; }
	|	expresson ASTERISK expresson		{ $$ = $1 * $3; }
	|	expresson FSLASH expresson			{ $$ = $1 / $3; }

	;
		
%%