#include <iostream>

#include "ast.h"
#include "lang.tab.h"

Ast g_ast;



int main()
{
	yyparse();

	g_ast.nodes.back()->printMe(00);

	std::cin.get();

	return 0;
}