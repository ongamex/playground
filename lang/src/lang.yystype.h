#pragma once

#include "ast.h"

struct LangYYSTYPE
{
	std::string str_val;

	union 
	{
		struct Node* node;
		float float_val;
		int int_val;
		struct {} no_type;
	};
};

#define YYSTYPE LangYYSTYPE