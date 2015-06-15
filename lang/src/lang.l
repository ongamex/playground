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
"for"													return FOR;
"if"													return IF;
"else"													return ELSE;
"while"													return WHILE;
"in"													return IN;
"out"													return OUT;
"inout"													return INOUT;
"attribute"												return ATTRIBUTE;
"varying"												return VARYING;
"uniform"												return UNIFORM;
[_a-zA-Z][_a-zA-z0-9]*									{ yylval->str_val = std::string(yytext); return IDENT; }
[0-9][0-9]*(\.[0-9]+)([eE][0-9][0-9]*)?					{ yylval->float_val = atof(yytext); return NUM_FLOAT; }
[0-9][0-9]*												{ yylval->int_val = atoi(yytext); return NUM_INT; }
"&&"													return AND;
"||"													return OR;
"<="													return LE;
">="													return GE;
"=="													return EQUALS;
"!="													return NOTEQUALS;
[-()<>=+*/;{},.] 										return *yytext;
%%

int yywrap(yyscan_t yyscanner)
{
	return 1;
}
	//The function that knows how to parse the language.
bool LangParseExpression(const char* code, Ast* ast)
{
	yyscan_t myscanner;
	yylex_init(&myscanner);
	struct yyguts_t * yyg = (struct yyguts_t*)myscanner;
	
	yy_delete_buffer(YY_CURRENT_BUFFER,myscanner);
	
	/*Copy string into new buffer and Switch buffers*/
	yy_scan_string(code, myscanner);
	
	bool nasi = yyparse(myscanner, ast);
	yylex_destroy(myscanner);
	return nasi;
}