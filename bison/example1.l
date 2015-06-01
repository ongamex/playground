%{
  #include "parser.h"
%}

%option warn nodefault 
%option reentrant noyywrap never-interactive nounistd
%option bison-bridge

%%

"(" { return (LPAREN); }
")" { return (RPAREN); }

[ \f\r\t\v\n]+ /* eat whitespace */

%%

/* don't use lexer.l for code, organize it logically elsewhere */