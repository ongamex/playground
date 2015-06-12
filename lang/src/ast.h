#pragma once

#include <iostream>
#include <vector>
#include <string>

struct LangSetting
{

};

template<class T>
std::string NodeGenerateCode(const LangSetting& lang, T& data) {
	return std::string();
}

std::string GenerateCode(const LangSetting& lang, const char* code);

#include "utils/variant.h"

enum NodeType
{
	NT_None,

	// expressions
	NT_ExprLiteral,
	NT_ExprBin,
	NT_Assign,

	NT_FuncCall,

	// Statements
	NT_If,
	NT_While,
	NT_For,

	NT_Identifier,
	NT_VarDecl,

	NT_StmtList,

	NT_Type,

	NT_FuncDecl,
	NT_FnDeclArgVarDecl,
	NT_FuncDeclArgs,

	NT_ProgramElem,

	
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

struct TypeDesc
{
	enum Type
	{
		Type_Undeduced,
		Type_NoType,
	
		Type_int,
		Type_float,
		Type_float2,
		Type_float3,
		Type_float4,

		Type_float4x4,
		Type_UserDefined,
	};

	TypeDesc(Type type = Type_Undeduced) : m_type(type) { }

	TypeDesc(std::string strType) : m_strType(strType)
	{
		if(strType == "int") m_type = Type_int;
		else if(strType == "float") m_type = Type_float;
		else if(strType == "float2") m_type = Type_float2;
		else if(strType == "float3") m_type = Type_float3;
		else if(strType == "float4") m_type = Type_float4;
		else if(strType == "float4x4") m_type = Type_float4x4;
	}

	bool operator==(TypeDesc& other) const
	{
		if(m_type != Type_UserDefined) return m_type == other.m_type;
		return m_strType == other.m_strType;
	}

	static TypeDesc ResolveType(const TypeDesc& left, const TypeDesc& right)
	{
		auto isPairOf = [left, right](Type a, Type b) {
			return (left.GetType() == a && right.GetType() == b) ||
					(left.GetType() == b && right.GetType() == a);
		};

		if(isPairOf(Type_int, Type_float)) return TypeDesc(Type_float);
		if(isPairOf(Type_float4x4, Type_float4)) return TypeDesc(Type_float4);

		// Unknown expression cofiguration
		return TypeDesc(Type_NoType);
	}

	Type GetType() const { return m_type; }

private : 

	Type m_type;
	std::string m_strType;
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

	std::string NodeGenerateCode(const LangSetting& lang) {

		if(type == NT_None) return std::string();
		
		std::string retval = data.NodeGenerateCode(lang);

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

	TypeDesc expressionType;
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

	void PrepassDecl()
	{
		
		std::vector<std::string> scope;

	};

	Node* program;
	std::vector<Node*> nodes;

	std::vector<VertexAttribs> vertexAttribs;
	std::vector<Varyings> varyings;
	std::vector<Uniforms> uniforms;
};


//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
struct Ident {
	enum { MyNodeType = NT_Identifier };
	std::string identifier;
};

//---------------------------------------------------------------------------------
// Expressions
//---------------------------------------------------------------------------------

// Binary expression of kind: a ? b
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
};

// Function calls in expressions.

struct FuncCall
{
	enum { MyNodeType = NT_FuncCall };

	std::string fnName;
	std::vector<Node*> args;
};

// Literal value
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
};

//---------------------------------------------------------------------------------
// Statements
//---------------------------------------------------------------------------------
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

struct StmtFor
{
	enum { MyNodeType = NT_For };

	Node* vardecl;
	Node* boolExpr;
	Node* postExpr;
	Node* stmt;
};

struct StmtList
{
	enum { MyNodeType = NT_StmtList };

	std::vector<Node*> nodes;
};

struct VarDecl
{
	enum { MyNodeType = NT_VarDecl };

	std::string type;
	std::vector<std::string> ident;
	std::vector<Node*> expr;
};

struct FnDeclArgVarDecl
{
	enum { MyNodeType = NT_FnDeclArgVarDecl };

	std::string type;
	std::string ident;
	Node* expr;
	FnCallArgType argType; //in/out/inout.

};

struct FuncDecl
{
	enum { MyNodeType = NT_FuncDecl };

	std::vector<Node*> args;
	std::string retType;
	std::string name;

	Node* stmt; // the body of the function.
};


struct ProgramElem
{
	enum { MyNodeType = NT_ProgramElem };

	std::vector<Node*> nodes;
};

template<>
std::string NodeGenerateCode<Ident>(const LangSetting& lang, Ident& data);
template<>
std::string NodeGenerateCode<ExprBin>(const LangSetting& lang, ExprBin& data);
template<>
std::string NodeGenerateCode<FuncCall>(const LangSetting& lang, FuncCall& data);
template<>
std::string NodeGenerateCode<ExprLiteral>(const LangSetting& lang, ExprLiteral& data);
template<>
std::string NodeGenerateCode<Assign>(const LangSetting& lang, Assign& data);
template<>
std::string NodeGenerateCode<StmtIf>(const LangSetting& lang, StmtIf& data);
template<>
std::string NodeGenerateCode<StmtWhile>(const LangSetting& lang, StmtWhile& data);
template<>
std::string NodeGenerateCode<StmtFor>(const LangSetting& lang, StmtFor& data);
template<>
std::string NodeGenerateCode<StmtList>(const LangSetting& lang, StmtList& data);
template<>
std::string NodeGenerateCode<VarDecl>(const LangSetting& lang, VarDecl& data);
template<>
std::string NodeGenerateCode<FnDeclArgVarDecl>(const LangSetting& lang, FnDeclArgVarDecl& data);
template<>
std::string NodeGenerateCode<FuncDecl>(const LangSetting& lang, FuncDecl& data);
template<>
std::string NodeGenerateCode<ProgramElem>(const LangSetting& lang, ProgramElem& data);
