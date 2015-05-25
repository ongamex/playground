%{
#include <stdio.h>
#include <string>
#include "ast.h"
#include "lang.tab.h"
void yyerror(char*);
int yyparse();
int kk_parse_cstring(const char* str) {
	YY_BUFFER_STATE my_string_buffer = yy_scan_string(str); 
	yy_switch_to_buffer( my_string_buffer ); // switch flex to the buffer we just created
	yyparse(); 
	yy_delete_buffer(my_string_buffer );
	return 5; // 3ds max style
}
%}

%%

[//].*[\n]												;
[/*].*[*/]												;
[ \t\n]													;
"if"													return IF;
"else"													return ELSE;
"while"													return WHILE;
"void"													return VOID;
"int"													return INT;
"float"													return FLOAT;
[_a-zA-Z][_a-zA-z0-9]*									{ yylval.str_val = new std::string(yytext); return IDENTIFIER;}
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
","														return COMMA;

%%

void yyerror(char* str) { printf("error: %s\n", str); }
int yywrap() { return 0; }