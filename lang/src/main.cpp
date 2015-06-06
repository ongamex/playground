#include <iostream>
#include "ast.h"

bool LangParseExpression(const std::string& inp, Ast* ast);

std::string GenerateGLSL(const Ast* ast)
{
	return ast->program->GenerateGLSL();
}

struct bla { int x; };

int main()
{
	Ast ast;

std::string code = R"(

void f(int x) {
	if(x + 5) {
		x = (10+3)*5;
	}
	
	if(x+1) {
		y=4+5;
	}
	while(5){x=10;}
	if (x) 5;

	x = foo(x+3,1,3*4*foo());
}

void f() {
	int x = 1.0;
}

)";
	auto f = bla {5};


	LangParseExpression(code, &ast);
//	ast.nodes.back()->printMe(00);
	std::cout << GenerateGLSL(&ast);
	std::cin.get();
	return 0;
}
