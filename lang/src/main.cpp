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

// OLD CODE:
//
//	int foo() {5;}
//void f(inout int x, out int y, in void z) {
//	if(x + 5 == 10) {
//		x = (10+3)*5;
//	}
//
//	while(5 < x) {
//		x=10;
//		if (x >= 10) x = 5;
//	}
//	
//	y = 3;
//	x = foo(x+3,1,3*4*foo()) * 3+4;
//	foo(5);
//}
//
//void fo() {
//	float a,b,c=1,d;
//	int x = 1.0;
//	for(int t = 0; t < 10; 1+t) {
//		foo(x);
//	}
//}


char* code = R"(

attribute vec3f a_pos : POSITION;

uniform Texture2D diffuseTex;

out vec2f uv;
in mat4f world;

mat4f getm() { int x = 10; }

void main() {
	mat4f m;
	vec4f v = vec4f(5);
	int x;
	uv = 2;
	if(x>0)
		v = -(world * -v.xx * +(getm() * v));
	else if(x<0) x = 10;
	vertex_output = v;
}

)";
	LangSettings lang;
	lang.outputLanguage = OL_HLSL;
	lang.shaderType = ST_Vertex;

	std::string formatted = FormatCode(GenerateCode(lang, code).c_str());

	std::cout << formatted;
	std::cin.get();
	return 0;
}
