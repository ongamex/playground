%{
#include <stdio.h>
#include <stdlib.h>
#include <string>
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

%token <int_token>	EQUALS MINUS PLUS ASTERISK FSLASH LPAREN RPAREN SEMICOLON PRINT QUIT QMARK COLON
%token <str_val>	VARIABLE
%token <double_val>	NUMBER


%type <double_val>	expresson;
%type <double_val>	expresson_level0;
%type <double_val>	expresson_level1;
%type <double_val>	expresson_level2;
%type <double_val>	expresson_level3;

%start grammar

%%

grammar : expressons;
expressons : | expressons base_expressionlist SEMICOLON;

base_expressionlist : expresson | print_expression | quit_expression;

quit_expression : QUIT { exit(0); };
print_expression : PRINT expresson { printf("%f\n", $2); };

expresson : 
		VARIABLE EQUALS expresson_level0							{ vars[*$1] = $3; $$ = vars[*$1]; }
	|	expresson_level0;
	;

expresson_level0 : 
		
		expresson_level0 QMARK expresson_level1 COLON expresson_level1		{ if($1) $$ = $3; else $$ = $5; }
	|	expresson_level1;
	
expresson_level1 : 
			
		expresson_level1 PLUS expresson_level2				{ $$ = $1 + $3; }
	|	expresson_level1 MINUS expresson_level2				{ $$ = $1 - $3; }
	|	expresson_level2;
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
		;

%%