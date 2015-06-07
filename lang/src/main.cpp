#include <iostream>
#include "ast.h"

bool LangParseExpression(const char* code, Ast* ast);

std::string GenerateGLSL(const Ast* ast)
{
	return ast->program->GenerateGLSL();
}

std::string FormatCode(const char* code)
{
	std::string retval;
	retval.reserve(strlen(code));

	while(*code)
	{
		const char ch = *code;

		if(ch == '{') {
			retval += " {\n"; 
		}
		else if(ch == '}')
		{
			retval += "}\n";
		}
		else if(ch == '\n') {
			retval += "\r\n";
		}
		else if(ch == ',') {
			retval += ", ";
		}
		else retval += ch;


		code++;
	}

	return retval;
}

int main()
{
	Ast ast;

char* code = R"(

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

	LangParseExpression(code, &ast);

	std::string formatted = FormatCode(code);

//	ast.nodes.back()->printMe(00);
	std::cout << formatted;
	std::cin.get();
	return 0;
}
