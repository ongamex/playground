#include <iostream>

#include "ast.h"
#include "lang.tab.h"

Ast g_ast;

int kk_parse_cstring(const char* str);

int main()
{
	yyparse();

	//kk_parse_cstring("if(1) { 5; }\n\0\0");

	g_ast.nodes.back()->printMe(00);

	std::cin.get();

	return 0;
}