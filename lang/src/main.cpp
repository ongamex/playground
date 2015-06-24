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

attribute vec3f a_pos : POSITION;

uniform Texture2D diffuseTex;

out vec2f uv;
in mat4f world;

mat4f getm() { return; }

void main() {

	vec3f[10] yyyy, uyuyu;

	mat4f m; //
	vec4f v = vec4f(5);
	int x = lerp(0.3, 0.0, 1.0);
	uv = 2.0 + yyyy[5].y*3.0;
	if(x>0){
		v = normalize(v*0.5);
		v = -(world * -v.xxxy * +(getm() * v));
		vec3f a_pos = v;
		v = a_pos;
		uv = 2;
	}
	else if(x<0) x = 10;
	cs_VertexOut = v;
	v = takeSample(diffuseTex, uv) * world;
	cs_PixelNDC = 5;
	a_pos = m * lerp(0.3, 5.0, 10.0) * vec4f(0.0);
	m * mix(0.3, vec4f(0), vec4f(1.0));

	vec3f a,b;
	v = cross(a, b);
	dot(a,a);
}

)";
	{
		LangSettings lang;
		lang.outputLanguage = OL_HLSL;
		lang.shaderType = ST_Vertex;

		std::string formatted = FormatCode(GenerateCode(lang, code).c_str());
		std::cout << formatted;
	}
	std::cout << "\n\n=========================================\n\n";
	{
		LangSettings lang;
		lang.outputLanguage = OL_GLSL;
		lang.shaderType = ST_Vertex;

		std::string formatted = FormatCode(GenerateCode(lang, code).c_str());
		std::cout << formatted;
	}

	std::cin.get();
	return 0;
}
