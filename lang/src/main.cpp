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

	int tabs = 0;

	auto addIdent = [&]() { for(int t = 0; t < tabs; ++t) retval += "  "; };

	while(*code)
	{
		const char ch = *code;

		if(ch == '{') {
			retval += "{\n"; tabs++;
			addIdent();
		}
		else if(ch == '}')
		{
			tabs--;
			retval += "\n";
			addIdent();
			retval += "}\n";
			addIdent();
		}
		else if(ch == '\n') {
			retval += '\n'; addIdent();
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

	std::string formatted = FormatCode(GenerateGLSL(&ast).c_str());

//	ast.nodes.back()->printMe(00);
	std::cout << formatted;
	std::cin.get();
	return 0;
}
