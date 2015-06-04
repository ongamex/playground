#include <iostream>
#include "ast.h"

bool LangParseExpression(const std::string& inp, Ast* ast);

int main()
{
	Ast ast;
	LangParseExpression("if(1)x=10;", &ast);
//	ast.nodes.back()->printMe(00);
	std::cin.get();
	return 0;
}