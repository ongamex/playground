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

	NT_FuncCall,
	NT_FuncCallArgs, // a sub node specially created for function call expresions

	// Statements
	NT_If,
	NT_While,
	NT_For,

	NT_Identifier,
	NT_VarDecl,

	NT_Type,

	NT_FuncDecl,
	NT_FnDeclArgVarDecl,
	NT_FuncDeclArgs,

	NT_ProgramElem,

	NT_NtList, // a list of nodes
};

enum ExprLiteralType
{ 
	EL_Unknown, 
	EL_Int, 
	EL_Float 
};

enum ExprBinType
{ 
	EBT_Add, 
	EBT_Sub,
	EBT_MatMul, // HLSL-style matrix multiplication
	EBT_Mul, 
	EBT_Div, 
	EBT_Greater, 
	EBT_GEquals, 
	EBT_Less, 
	EBT_LEquals, 
	EBT_Equals,
	EBT_NEquals,
	EBT_Or, 
	EBT_And,
};

enum FnCallArgType
{
	FNAT_In,
	FNAT_Out,
	FNAT_InOut,
};

struct VertexAttribs
{
	std::string type;
	std::string varName;
	std::string semantic;
};

struct Varyings
{
	std::string type;
	std::string varName;
};

struct Uniforms
{
	std::string type;
	std::string varName;
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

	template<typename T>
	T& As() { return data.As<T>(); }

	std::string GenerateGLSL() {

		if(type == NT_None) return std::string();
		
		std::string retval = data.GenerateGLSL();

		if(inParens) retval = '(' + retval +')';
		if(exprSign != '+') retval = exprSign + retval;
		if(hasSemicolon) retval += ";";
		if(inBlock) retval = "{" + retval + "}";

		return retval;
	}

	NodeType type = NT_None;
	Variant<100> data;

	char exprSign = '+'; // The sign of the expression. Used for -expr for example.
	bool inParens = false; // True if the expression is surrounded with parens.
	bool inBlock = false; // True if the statement is surrounded by { }
	bool hasSemicolon = false; // True if the statement is of kind <--->; 
};

struct Ast
{
	inline Node* add(Node* node) {
		nodes.push_back(node);
		return node;
	}

	template<typename T>
	inline Node* push(const T t = T()) {
		return add(new Node((NodeType)T::MyNodeType, t));
	}

	Node* program;
	std::vector<Node*> nodes;

	std::vector<VertexAttribs> vertexAttribs;
	std::vector<Varyings> varyings;
	std::vector<Uniforms> uniforms;
};


//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
struct EmptyNode
{
	enum { MyNodeType = NT_None };
};


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
		char buff[64] = {0};

		if(type == EL_Float)
		{
			
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
		else if(type == EL_Int)
		{
			sprintf(buff, "%d", int_val);
			return buff;
		}

		return "???";
	}
};

struct ExprBin
{
	enum { MyNodeType = NT_ExprBin };

	ExprBin() = default;

	ExprBin(ExprBinType type, Node* left, Node* right) :
		type(type), left(left), right(right)
	{}

	ExprBinType type;
	Node* left;
	Node* right;

	std::string GenerateGLSL() {
		switch(type) {
			case EBT_Add :      return left->GenerateGLSL() + (" + ") + right->GenerateGLSL();
			case EBT_Sub :      return left->GenerateGLSL() + (" - ") + right->GenerateGLSL();
			case EBT_MatMul :   return "mul(" + left->GenerateGLSL() + "," + right->GenerateGLSL() + ")"; 
			case EBT_Mul :      return left->GenerateGLSL() + (" * ") + right->GenerateGLSL();
			case EBT_Div :      return left->GenerateGLSL() + (" / ") + right->GenerateGLSL();
			case EBT_Greater :  return left->GenerateGLSL() + (" > ") + right->GenerateGLSL();
			case EBT_GEquals :  return left->GenerateGLSL() + (" >= ") + right->GenerateGLSL();
			case EBT_Less :     return left->GenerateGLSL() + (" < ") + right->GenerateGLSL();
			case EBT_LEquals :  return left->GenerateGLSL() + (" <= ") + right->GenerateGLSL();
			case EBT_Equals :   return left->GenerateGLSL() + (" == ") + right->GenerateGLSL();
			case EBT_NEquals :  return left->GenerateGLSL() + (" != ") + right->GenerateGLSL();
			case EBT_Or :       return left->GenerateGLSL() + (" || ") + right->GenerateGLSL();
			case EBT_And :      return left->GenerateGLSL() + (" && ") + right->GenerateGLSL();
			default :           return left->GenerateGLSL() + (" ??? ") + right->GenerateGLSL();
		}

		return "expr ??? expr";
	}
};

struct Assign
{
	enum { MyNodeType = NT_Assign };

	std::string ident;
	Node* expr;

	std::string GenerateGLSL() {
		return ident + " = " + expr->GenerateGLSL();
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
		if(falseStmt) retval += "else " + falseStmt->GenerateGLSL();
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

struct StmtFor
{
	enum { MyNodeType = NT_For };

	Node* vardecl;
	Node* boolExpr;
	Node* postExpr;
	Node* stmt;

	std::string GenerateGLSL() {
		std::string retval = "for(";
		if(vardecl) retval += vardecl->GenerateGLSL(); retval += ';';
		if(boolExpr) retval += boolExpr->GenerateGLSL(); retval += ';';
		if(postExpr) retval += postExpr->GenerateGLSL(); 
		retval += ')';

		retval += stmt->GenerateGLSL();

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
				retval += "=" + expr[t]->GenerateGLSL();
				if(t < ident.size() - 1) retval += ',';
			}
		}

		return retval;
	}
};

struct FnDeclArgVarDecl
{
	enum { MyNodeType = NT_FnDeclArgVarDecl };

	std::string type;
	std::string ident;
	Node* expr;
	FnCallArgType argType; //in/out/inout.

	std::string GenerateGLSL() {
		std::string retval;
		if(argType == FNAT_InOut) retval += "inout ";
		if(argType == FNAT_Out) retval += "out ";

		retval += type + " " + ident;
		if(expr) retval += "=" + expr->GenerateGLSL();
		return retval;
	}

};

struct FnDeclArgs
{
	enum { MyNodeType = NT_FuncDeclArgs };

	std::vector<Node*> args;

	std::string GenerateGLSL() {
		
		std::string retval;

		for(int t = 0; t < args.size(); ++t) {
			retval += args[t]->GenerateGLSL();
			if(t < args.size() - 1) retval += ',';
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
		retval += "){ " + stmt->GenerateGLSL() + "}";

		return retval;
	}
};

struct FuncCallArgs
{
	enum { MyNodeType = NT_FuncCallArgs };

	std::vector<Node*> args;

	std::string GenerateGLSL() {
		std::string retval;

		for(int t = 0; t < args.size(); ++t) {
			retval += args[t]->GenerateGLSL();
			if(t < args.size() - 1) retval += ",";
		}

		return retval;
	}
};

struct FuncCall
{
	enum { MyNodeType = NT_FuncCall };

	std::string fnName;
	Node* args;

	std::string GenerateGLSL() {
		std::string retval = fnName + '(';
		if(args) retval += args->GenerateGLSL();
		retval += ')';
		return retval;
	}
};

struct ProgramElem
{
	enum { MyNodeType = NT_ProgramElem };

	std::vector<Node*> nodes;

	std::string GenerateGLSL() {
		std::string retval;

		for(const auto& node : nodes) {
			retval += node->GenerateGLSL();
		}

		return retval;
	}
};