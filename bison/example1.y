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

%token <int_token>	EQUALS MINUS PLUS ASTERISK FSLASH LPAREN RPAREN SEMICOLON PRINT
%token <str_val>	VARIABLE
%token <double_val>	NUMBER

%type <double_val>	number_expr;
%type <double_val>	num_expression;

%start grammer


%%

grammer : expressons;
expressons : | expressons base_expressionlist;

base_expressionlist : print_expression | assign_expression ;

number_expr :
				NUMBER			{ $$ = $1; }
			|	VARIABLE		{ $$ = vars[*$1]; }
			;

num_expression : 
	
		number_expr
	|	number_expr PLUS number_expr					{ $$ = $1 + $3; }
	|	number_expr MINUS number_expr					{ $$ = $1 - $3; }
	| 	number_expr ASTERISK number_expr				{ $$ = $1 * $3; }
	;
	
assign_expression : VARIABLE EQUALS num_expression SEMICOLON { vars[*$1] = $3; };
print_expression : PRINT num_expression SEMICOLON { printf("%f\n", $2); };

%%