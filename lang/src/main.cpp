#include <iostream>
#include "ast.h"

bool LangParseExpression(const char* code, Ast* ast);

std::string GenerateGLSL(const Ast* ast)
{
	return ast->program->GenerateGLSL();
}

struct bla { int x; };

int main()
{
	Ast ast;

char * code = R"(

void f(inout int x, out int y, in void z, int x) {
	if(x + 5 == 10) {
		x = (10+3)*5;
	}

	while(5 < x) {
		x=10;
		if (x >= 10) x = 5;
	}
	

	x = foo(x+3,1,3*4*foo());
}

void f() {
	int x = 1.0;
	for(int t = 0; t < 10; 1+t) {
		printf(bla);
	}
}

)";
	auto f = bla {5};


	LangParseExpression(code, &ast);
//	ast.nodes.back()->printMe(00);
	std::cout << GenerateGLSL(&ast);
	std::cin.get();
	return 0;
}
