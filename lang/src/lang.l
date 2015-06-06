%option reentrant bison-bridge 

%{
#include <stdio.h>
#include <string>
#include "ast.h"
#include "lang.tab.h"

#include "lang.yystype.h"

void yyerror (yyscan_t yyscanner, char const *msg);
%}

%%

[ \t\n]													;
"if"													return IF;
"else"													return ELSE;
"while"													return WHILE;
[_a-zA-Z][_a-zA-z0-9]*									{ yylval->str_val = std::string(yytext); return IDENTIFIER;}
[0-9][0-9]*(\.[0-9]+)?([eE][0-9][0-9]*)?				{ yylval->float_val = atof(yytext); return NUM_FLOAT;}
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

int yywrap(yyscan_t yyscanner)
{
	return 1;
}
	//The function that knows how to parse the language.
bool LangParseExpression(const std::string& inp, Ast* ast)
{
	yyscan_t myscanner;
	yylex_init(&myscanner);
	struct yyguts_t * yyg = (struct yyguts_t*)myscanner;
	
	yy_delete_buffer(YY_CURRENT_BUFFER,myscanner);
	
	/*Copy string into new buffer and Switch buffers*/
	yy_scan_string(inp.c_str(), myscanner);
	
	bool nasi = yyparse(myscanner, ast);
	yylex_destroy(myscanner);
	return nasi;
}