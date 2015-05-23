%{
#include <stdio.h>
#include <string>
#include "ast.h"
#include "lang.tab.h"
void yyerror(char*);
int yyparse();
%}

%%

[//].*[\n]												;
[/*].*[*/]												;
[ \t\n]													;
"if"													return IF;
"else"													return ELSE;
[a-zA-Z][a-zA-z0-9]*									{ yylval.str_val = new std::string(yytext); return VARIABLE;}
[0-9][0-9]*(\.[0-9]+)?([eE][0-9][0-9]*)?				{ yylval.double_val = atof(yytext); return NUMBER;}
"="														return EQUALS;
"+"														return PLUS;
"-"														return MINUS;
"*"														return ASTERISK;
"/"														return FSLASH;
"("														return LPAREN;
")"														return RPAREN;
";"														return SEMICOLON;
"{"														return BLOCK_BEGIN;
"}"														return BLOCK_END;



%%

void yyerror(char* str) { printf("error: %s\n", str); }
int yywrap() { return 0; }