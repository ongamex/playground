%{
#include <stdio.h>
#include <string>
#include "example1.tab.h"
void yyerror(char*);
int yyparse();
%}

%%

[//].*[\n]									;
[/*].*[*/]									;
[ \t\n]										;
[a-zA-Z][a-zA-z0-9]*						{ yylval.str_val = new std::string(yytext); return VARIABLE;}
[0-9][0-9]*(\.[0-9]+)?([eE][0-9][0-9]*)?	{ yylval.double_val = atof(yytext); return NUMBER;}
"="											return EQUALS;
"+"											return PLUS;
"-"											return MINUS;
"*"											return ASTERISK;
"/"											return FSLASH;
"("											return LPAREN;
")"											return RPAREN;
";"											return SEMICOLON;
"?"											return QMARK;
":"											return COLON;


%%

void yyerror(char* str) { printf("error: %s\n", str); }
int yywrap() { return 0; }

int main() {
	printf("%s %s\n", __DATE__, __TIME__);
	yyparse();
}