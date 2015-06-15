#include <iostream>
#include "ast.h"

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
			retval += " {\n"; tabs++;
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
		else if(ch == ';') {
			retval += ";\n"; addIdent();
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
mat4f getm() { x = 10; }
void f() {
	mat4f m;
	vec4f v;
	v = m * v.xx * (getm() * v);
}
)";
	LangSettings lang;
	lang.outputLanguage = OL_HLSL;

	std::string formatted = FormatCode(GenerateCode(lang, code).c_str());

	std::cout << formatted;
	std::cin.get();
	return 0;
}
