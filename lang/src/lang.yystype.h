#pragma once

#include "ast.h"

union LangYYSTYPE
{
	struct Node* node;
	std::string* str_val;
	double double_val;
	struct {} no_type;
};

#define YYSTYPE LangYYSTYPE