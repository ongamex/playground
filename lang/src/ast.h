#pragma once

#include <iostream>
#include <vector>

#include "utils/variant.h"

#if 0
enum NodeType
{
	NT_None,

	NT_Num,
	NT_Var,

	// expressions
	NT_Add,
	NT_Sub,
	NT_Mul,
	NT_Div,
	NT_Assign,

	NT_If,
	NT_While,

	NT_Type,
	NT_Identifier,
	NT_VarInit,
	
	NT_VarDecl,

	NT_NtList, // a list of nodes
};

struct Node
{
	Node() : type(NT_None) {}

	Node(const NodeType type, float number = 0.f) : type(type) {

		fData = number;
	}

	Node(const NodeType type, const char str[]) : type(type), strData(str) {}

	Node(const NodeType type, std::initializer_list<Node*> nodes) : type(type), nodes(nodes) {}

	union {
		float fData;
		int iData;
	};

	std::string strData;

	NodeType type;
	std::vector<Node*> nodes;

	//-------------------------------------------------------------
	//
	//-------------------------------------------------------------
	void printDepth(int depth) const {
		while(depth--) std::cout << "  ";
	}

	void printMe(const int depth) const
	{
		std::cout << std::endl;
		printDepth(depth);
		if(type == NT_Num) std::cout << fData;
		else if(type == NT_Add){std::cout << "+";nodes[0]->printMe(depth+1); nodes[1]->printMe(depth+1);}
		else if(type == NT_Sub){std::cout << "-";nodes[0]->printMe(depth+1); nodes[1]->printMe(depth+1);}
		else if(type == NT_Mul){std::cout << "*";nodes[0]->printMe(depth+1); nodes[1]->printMe(depth+1);}
		else if(type == NT_Div){std::cout << "/";nodes[0]->printMe(depth+1); nodes[1]->printMe(depth+1);}
		else if(type == NT_Assign) { std::cout << "="; nodes[0]->printMe(depth+1); nodes[1]->printMe(depth+1);}
		else if(type == NT_If) {std::cout << "if (expr) stmt"; nodes[0]->printMe(depth+1); nodes[1]->printMe(depth+1);}
		else if(type == NT_While) {std::cout << "while (expr) stmt"; nodes[0]->printMe(depth+1); nodes[1]->printMe(depth+1);}
		else if(type == NT_Identifier) { std::cout << "ident " << strData.c_str(); }
		else if(type == NT_Type) { std::cout << "type " << strData.c_str(); }
		else if(type == NT_VarInit) { 
			
			if(nodes.size() > 0) { std::cout << "var " << strData.c_str() << " = expr"; nodes[0]->printMe(depth+1); }
			else std::cout << "var " << strData.c_str(); 
		}
		else if(type == NT_VarDecl) { std::cout << "vardecl "; nodes[0]->printMe(depth+1); nodes[1]->printMe(depth+1);}
		
		else if(type == NT_NtList)
		{
			std::cout << "node list:";
			for(const auto& node : nodes) node->printMe(depth+1);
		}
		else std::cout << "Found node type=" << type;
	}

};
#endif

enum NodeType
{
	NT_None,

	NT_NumFloat,
	NT_Var,

	// expressions
	NT_Add,
	NT_Sub,
	NT_Mul,
	NT_Div,
	NT_Assign,

	NT_If,
	NT_While,

	NT_Type,
	NT_Identifier,
	NT_VarInit,
	
	NT_VarDecl,

	NT_NtList, // a list of nodes
};

struct Node
{
	Node() {}

	template<typename T>
	Node(const NodeType& type, const T& t) :
		type(type)
	{
		data.ConstructAs<T>();
		data.As<T>() = t;
	}

	NodeType type = NT_None;
	Variant<100> data;
};

struct Ast
{
	inline Node* add(Node* node) {
		nodes.push_back(node);
		return node;
	}

	std::vector<Node*> nodes;
};

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
struct ExprCommon // aka expr (op) expr
{
	char op; // + - * / = ...
	struct Node *left, *right;
};

struct ExprVar
{
	struct Node* exrp;
};

struct Expr
{
	char sign = '+'; // sign of the expression +/-
	union {
		ExprCommon exprCommon;
		ExprVar exprVar;
	};
};

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
struct StmtIf
{
	Node* exrp = nullptr;
	Node* trueStmt = nullptr;
	Node* falseStmt = nullptr; // optional
};

struct StmtWhile
{
	Node* exrp = nullptr;
	Node* bodyStmt = nullptr;
};

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
struct Ident
{
	std::string ident;
};