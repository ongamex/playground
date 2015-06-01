
%define api.pure
%lex-param   { yyscan_t scanner }
%parse-param { yyscan_t scanner }
%parse-param { void *scanner }

%code requires {
 
#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
typedef void* yyscan_t;
#endif
#include "lexer.h"
}

%union {
  int value; // or whatever else here
}

%token LPAREN
%token RPAREN

%%

document
    : exprs

exprs
    : 
    | expr exprs

expr
    : parens

parens
    : LPAREN exprs RPAREN


%%

int
yyerror(YYLTYPE *locp, char *msg) {
  if (locp) {
    fprintf(stderr, "parse error: %s (:%d.%d -> :%d.%d)\n",
                    msg,
                    locp->first_line, locp->first_column,
                    locp->last_line,  locp->last_column
    );
    /* todo: add some fancy ^^^^^ error handling here */
  } else {
    fprintf(stderr, "parse error: %s\n", msg);
  }
  return (0);
}