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

	// expressions
	NT_ExprLiteral,
	NT_ExprBin,
	NT_Assign,

	// Statements
	NT_If,
	NT_While,

	NT_Identifier,
	NT_VarDecl,

	NT_Type,

	NT_NtList, // a list of nodes
};

enum ExprLiteralType { EL_Int, EL_Float };

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

	template<typename T>
	T& As() { return data.As<T>(); }

	NodeType type = NT_None;
	Variant<100> data;
};

struct Ast
{
	inline Node* add(Node* node) {
		nodes.push_back(node);
		return node;
	}

	template<typename T>
	inline Node* push(const T& t) {
		return add(new Node((NodeType)T::MyNodeType, t));
	}

	std::vector<Node*> nodes;
};


//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
struct ExprVar
{
	struct Node* identNode;
};

struct ExprLiteral
{
	enum { MyNodeType = NT_ExprLiteral };

	ExprLiteralType type; 

	union
	{
		int int_val;
		float float_val;
	};
};

struct ExprBin
{
	enum { MyNodeType = NT_ExprBin };

	char ch; // sign of the expression
	Node* left;
	Node* right;
};

struct Assign
{
	enum { MyNodeType = NT_Assign };

	std::string ident;
	Node* expr;
};

struct StmtIf
{
	enum { MyNodeType = NT_If };

	StmtIf() = default;
	StmtIf(Node* expr, Node* trueStmt, Node* falseStmt) : expr(expr), trueStmt(trueStmt), falseStmt(falseStmt) {}

	Node* expr = nullptr;
	Node* trueStmt = nullptr;
	Node* falseStmt = nullptr; // optional
};

struct StmtWhile
{
	enum { MyNodeType = NT_While };

	StmtWhile() = default;
	StmtWhile(Node* expr, Node* bodyStmt) : expr(expr), bodyStmt(bodyStmt) {}

	Node* expr = nullptr;
	Node* bodyStmt = nullptr;
};

struct Ident
{
	enum { MyNodeType = NT_Identifier };

	std::string identifier;
};

struct NodeList
{
	enum { MyNodeType = NT_NtList };

	std::vector<Node*> nodes;
};

struct VarDecl
{
	enum { MyNodeType = NT_VarDecl };

	std::string type;
	std::vector<Node*> ident;
	std::vector<Node*> expr;
};
