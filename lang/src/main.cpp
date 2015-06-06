#include <iostream>
#include "ast.h"

bool LangParseExpression(const std::string& inp, Ast* ast);



std::string GenerateGLSL(const Ast* ast)
{
	return ast->nodes.back()->GenerateGLSL();
}

int main()
{
	Ast ast;

std::string code = R"(

void f(int x) {
	if(x + 5) {
		x = (10+3)*5;
	}
	else if(x+1) {
		y=4+5;
	}
	while(5){x=10;}
	if (x) 5;

	x = foo(x+3,1,3*4*foo());
}

)";


	LangParseExpression(code, &ast);
//	ast.nodes.back()->printMe(00);
	std::cout << GenerateGLSL(&ast);
	std::cin.get();
	return 0;
}

void f(int x) { 

}












