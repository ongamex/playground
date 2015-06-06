#pragma once

#include <iostream>
#include <vector>

#include "utils/variant.h"

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

	NT_FuncDecl,

	NT_NtList, // a list of nodes
};

enum ExprLiteralType { EL_Unknown, EL_Int, EL_Float };

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

	std::string GenerateGLSL() {
		std::string retval = data.GenerateGLSL();

		if(inParens) retval = '(' + retval +')';
		if(exprSign != '+') retval = exprSign + retval;
		if(inBlock) retval = '{' + retval + '}';

		return retval;
	}

	NodeType type = NT_None;
	Variant<100> data;

	char exprSign = '+'; // The sign of the expression. Used for -expr for example.
	bool inParens = false; // True if the expression is surrounded with parens.
	bool inBlock = false; // True if the statement is surrounded by { }
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
struct Ident
{
	enum { MyNodeType = NT_Identifier };

	std::string identifier;

	std::string GenerateGLSL() {
		return identifier;
	}
};

struct ExprVar
{
	struct Node* identNode;

	std::string GenerateGLSL() {
		return identNode->As<Ident>().GenerateGLSL();
	}
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

	ExprLiteral() : type(EL_Unknown) {}
	ExprLiteral(float f) : type(EL_Float), float_val(f) {}
	ExprLiteral(int i) : type(EL_Int), int_val(i) {}

	std::string GenerateGLSL()
	{
		char buff[64];
		sprintf(buff, "%f", float_val);

		// kill the trailing zeroes.
		for(int t = strlen(buff);t > 1; --t){
			if(buff[t] == '0' && buff[t-1] == '0') {
				buff[t] = '\0';
			}
			if(buff[t] == '.') break;
		}

		return buff;
	}
};

struct ExprBin
{
	enum { MyNodeType = NT_ExprBin };

	char sign; // sign of the expression
	Node* left;
	Node* right;

	std::string GenerateGLSL() {
		return left->GenerateGLSL() + sign + right->GenerateGLSL();
	}
};

struct Assign
{
	enum { MyNodeType = NT_Assign };

	std::string ident;
	Node* expr;

	std::string GenerateGLSL() {
		return ident + " = " + expr->GenerateGLSL() + ";";
	}
};

struct StmtIf
{
	enum { MyNodeType = NT_If };

	StmtIf() = default;
	StmtIf(Node* expr, Node* trueStmt, Node* falseStmt) : expr(expr), trueStmt(trueStmt), falseStmt(falseStmt) {}

	Node* expr = nullptr;
	Node* trueStmt = nullptr;
	Node* falseStmt = nullptr; // optional

	std::string GenerateGLSL() {
		std::string retval = " if(" + expr->GenerateGLSL() + ")";
		if(trueStmt) retval += trueStmt->GenerateGLSL(); else retval += ';';
		if(falseStmt) retval += " else" + falseStmt->GenerateGLSL();
		return retval;
	}
};

struct StmtWhile
{
	enum { MyNodeType = NT_While };

	StmtWhile() = default;
	StmtWhile(Node* expr, Node* bodyStmt) : expr(expr), bodyStmt(bodyStmt) {}

	Node* expr = nullptr;
	Node* bodyStmt = nullptr;

	std::string GenerateGLSL() {
		std::string retval = " while(" + expr->GenerateGLSL() + ")";
		if(bodyStmt) retval += bodyStmt->GenerateGLSL(); else retval += ';';
		return retval;
	}
};

struct NodeList
{
	enum { MyNodeType = NT_NtList };

	std::vector<Node*> nodes;

	std::string GenerateGLSL()
	{
		std::string retval;
		for(auto& node : nodes) retval += node->GenerateGLSL();
		return retval;
	}
};

struct VarDecl
{
	enum { MyNodeType = NT_VarDecl };

	std::string type;
	std::vector<std::string> ident;
	std::vector<Node*> expr;

	std::string GenerateGLSL()
	{
		std::string retval = type + " ";

		for(int t = 0; t < ident.size(); ++t)
		{
			retval += ident[t];
			if(expr[t]) {
				retval += " = " + expr[t]->GenerateGLSL() + ",";
			}
		}

		return retval;
	}
};

struct FuncDecl
{
	enum { MyNodeType = NT_FuncDecl };

	std::string retType;
	std::string name;
	Node* args;
	Node* stmt;

	std::string GenerateGLSL() {

		std::string retval = retType + " " + name + "(";
		if(args) retval += args->GenerateGLSL();
		retval += ") { " + stmt->GenerateGLSL() + "} ";

		return retval;
	}
};