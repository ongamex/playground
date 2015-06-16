#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <exception>

struct Ast;

struct ParseExcept : public std::exception {
	ParseExcept(const char* msg) :
		std::exception(msg)
	{}

	ParseExcept(const std::string& msg) :
		std::exception(msg.c_str())
	{}
};

enum OutputLanguage
{
	OL_HLSL,
	OL_GLSL
};

enum ShaderType
{
	ST_Vertex,
	ST_Pixel,
};

struct LangSettings
{
	OutputLanguage outputLanguage;
	ShaderType shaderType;
};

struct TypeDesc
{
	enum Type
	{
		Type_Undeduced,
		Type_NoType,

		Type_void,
		Type_int,
		Type_bool,
		Type_float,
		Type_vec2f,
		Type_vec3f,
		Type_vec4f,
		Type_mat4f,
		Type_Texture2D,

		Type_UserDefined,
	};

	TypeDesc(Type type = Type_Undeduced) : m_type(type) { }

	TypeDesc(std::string strType) : m_strType(strType)
	{
		if(strType == "void") m_type = Type_void;
		else if(strType == "int") m_type = Type_int;
		else if(strType == "bool") m_type = Type_bool;
		else if(strType == "float") m_type = Type_float;
		else if(strType == "vec2f") m_type = Type_vec2f;
		else if(strType == "vec3f") m_type = Type_vec3f;
		else if(strType == "vec4f") m_type = Type_vec4f;
		else if(strType == "mat4f") m_type = Type_mat4f;
		else if(strType == "Texture2D") m_type = Type_Texture2D;
		else { m_type = Type_UserDefined; }
	}

	bool operator==(const TypeDesc& other) const
	{
		if(m_type != Type_UserDefined) return m_type == other.m_type;
		return m_strType == other.m_strType;
	}

	bool operator!=(const TypeDesc& other) const
	{
		return !(*this == other);
	}

	static TypeDesc ResolveType(const TypeDesc& left, const TypeDesc& right)
	{
		//[TODO] This is sooo broken....
		auto isPairOf = [left, right](Type a, Type b) {
			return (left.GetBuiltInType() == a && right.GetBuiltInType() == b) ||
					(left.GetBuiltInType() == b && right.GetBuiltInType() == a);
		};

		if(isPairOf(Type_int, Type_float)) return TypeDesc(Type_float);
		else if(isPairOf(Type_float, Type_vec2f)) return TypeDesc(Type_vec2f);
		else if(isPairOf(Type_float, Type_vec3f)) return TypeDesc(Type_vec3f);
		else if(isPairOf(Type_float, Type_vec4f)) return TypeDesc(Type_vec4f);
		else if(isPairOf(Type_mat4f, Type_vec4f)) return TypeDesc(Type_vec4f);
		else if(left == right) return left;

		// Unknown expression cofiguration
		return TypeDesc(Type_NoType);
	}

	static TypeDesc GetMemberType(const TypeDesc& parent, const std::string& member)
	{
		//[TODO] This is sooo broken....
		const bool isFloatVectorType = 
			   (parent.GetBuiltInType() == Type_vec2f) 
			|| (parent.GetBuiltInType() == Type_vec3f) 
			|| (parent.GetBuiltInType() == Type_vec4f);

		if(isFloatVectorType)
		{
			if(member.size() <= 4)
			{
				for(auto ch : member) {
					if(ch != 'x' && ch != 'y' && ch != 'z' && ch != 'w') {
						throw ParseExcept("Trying to reference unexisting member: " + member);
					}
				}

				if(member.size() == 2) return TypeDesc(Type_vec2f);
				if(member.size() == 3) return TypeDesc(Type_vec3f);
				if(member.size() == 4) return TypeDesc(Type_vec4f);
			}
		}

		throw ParseExcept("Unknown member access: " + member);
	}

	std::string GetTypeAsString(const LangSettings& lang) const 
	{
		if(m_strType.empty()) return "<empty-str-type>";

		if(GetBuiltInType() == Type_void) return "void";
		else if(GetBuiltInType() == Type_int) return "int";
		else if(GetBuiltInType() == Type_float) return "float";
		else if(GetBuiltInType() == Type_bool) return "bool";
		else if(GetBuiltInType() == Type_vec2f) { if(lang.outputLanguage == OL_HLSL) return "float2"; else return "vec2"; }
		else if(GetBuiltInType() == Type_vec3f) { if(lang.outputLanguage == OL_HLSL) return "float3"; else return "vec3"; }
		else if(GetBuiltInType() == Type_vec4f) { if(lang.outputLanguage == OL_HLSL) return "float4"; else return "vec4"; }
		else if(GetBuiltInType() == Type_mat4f) { if(lang.outputLanguage == OL_HLSL) return "float4x4"; else return "mat4"; }
		else if(GetBuiltInType() == Type_Texture2D) { if(lang.outputLanguage == OL_HLSL) return "Texture2D"; else return "sampler2D"; } 
		else if(GetBuiltInType() == Type_UserDefined) return m_strType;

		return "<type-unknown>";
	}

	Type GetBuiltInType() const { return m_type; }

private : 

	Type m_type;
	std::string m_strType;
};


template<class T>
std::string NodeGenerateCode(const LangSettings& lang, T& data) {
	return std::string();
}

template<class T> TypeDesc NodeDeduceType(T& data) {
	return TypeDesc(TypeDesc::Type_NoType);
}


template<class T>
void NodeDeclare(Ast* ast, T& data) {
}

std::string GenerateCode(const LangSettings& lang, const char* code);

#include "utils/variant.h"

enum ExprBinType
{ 
	EBT_Add, 
	EBT_Sub,
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
	TypeDesc type;
	std::string varName;
	std::string semantic;
};

struct Varyings
{
	TypeDesc type;
	std::string varName;
};

struct Uniforms
{
	TypeDesc type;
	std::string varName;
};

struct Node
{
	Node() {}

	template<typename T>
	Node(const T& t)
	{
		data.ConstructAs<T>();
		data.As<T>() = t;
	}

	template<typename T>
	T& As() { return data.As<T>(); }

	std::string NodeGenerateCode(const LangSettings& lang) {
		
		std::string retval = data.NodeGenerateCode(lang);

		if(inParens) retval = '(' + retval +')';
		if(exprSign != '+') retval = exprSign + retval;
		if(hasSemicolon) retval += ";";
		if(inBlock) retval = "{" + retval + "}";

		return retval;
	}

	void NodeDeclare(Ast* ast);

	TypeDesc NodeDeduceType() { return data.NodeDeduceType(); }

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
		return add(new Node(t));
	}
	
	void declPushScope() {
		static int scopeIndex;
		char srtScope[32];
		sprintf(srtScope, "scope_%d", scopeIndex);
		scopeIndex++;

		declPushScope(srtScope);
	}

	void declPushScope(const std::string& scopeName) {
		scope.push_back(scopeName);
	}

	void declPopScope() {
		scope.pop_back();
	}

	// Adds a node. to the deduction queue.
	void addDeduct(Node* expr)
	{
		deductionQueue.push_back(expr);
	}

	struct FullVariableDesc {
		std::string fullName;
		TypeDesc type;
	};

	struct FullFuncionDesc {
		std::string fullName;
		TypeDesc retType;
	};

	std::string GenerateGlobalUniforms(const LangSettings& lang);

	// Declares a variable at the current scope.
	FullVariableDesc declareVariable(const TypeDesc& td, const std::string& name);
	void declareFunction(const TypeDesc& returnType, const std::string& name);
	
	const FullVariableDesc& findVarInCurrentScope(const std::string& name);
	const FullFuncionDesc& findFuncDecl(const std::string& name);

	Node* program = nullptr;
	std::vector<Node*> nodes;

	std::vector<VertexAttribs> vertexAttribs;
	std::vector<Varyings> varyings;
	std::vector<Uniforms> uniforms;

	std::vector<std::string> scope;
	std::vector<FullVariableDesc> declaredVariables;
	std::vector<FullFuncionDesc> declaredFunctions;

	std::vector<Node*> deductionQueue;
};


//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
struct Ident
{
	std::string identifier;
	TypeDesc resolvedType;
};

template<> std::string NodeGenerateCode<Ident>(const LangSettings& lang, Ident& data);
template<> void NodeDeclare<Ident>(Ast* ast, Ident& data);
template<> TypeDesc NodeDeduceType<Ident>(Ident& data);

struct ExprMemberAccess
{
	ExprMemberAccess() = default;
	ExprMemberAccess(Node* expr, const std::string& member) :
		expr(expr), member(member)
	{}

	Node* expr;
	std::string member;

	TypeDesc resolvedType; 
};

template<> std::string NodeGenerateCode<ExprMemberAccess>(const LangSettings& lang, ExprMemberAccess& data);
template<> void NodeDeclare<ExprMemberAccess>(Ast* ast, ExprMemberAccess& data);
template<> TypeDesc NodeDeduceType<ExprMemberAccess>(ExprMemberAccess& data);

//---------------------------------------------------------------------------------
// Expressions
//---------------------------------------------------------------------------------

// Binary expression of kind: a ? b
struct ExprBin
{
	ExprBin() = default;
	ExprBin(ExprBinType type, Node* left, Node* right) :
		type(type), left(left), right(right)
	{}

	ExprBinType type;
	Node* left;
	Node* right;


	TypeDesc resolvedType;
};

template<> std::string NodeGenerateCode<ExprBin>(const LangSettings& lang, ExprBin& data);
template<> void NodeDeclare<ExprBin>(Ast* ast, ExprBin& data);
template<> TypeDesc NodeDeduceType<ExprBin>(ExprBin& data);

// Function calls in expressions.

struct FuncCall
{
	std::string fnName;
	std::vector<Node*> args;

	TypeDesc resolvedType;
};

template<> std::string NodeGenerateCode<FuncCall>(const LangSettings& lang, FuncCall& data);
template<> void NodeDeclare<FuncCall>(Ast* ast, FuncCall& data);
template<> TypeDesc NodeDeduceType<FuncCall>(FuncCall& data);

// Literal value
struct ExprLiteral
{
	union
	{
		int int_val;
		float float_val;
	};

	ExprLiteral() : type() {}
	ExprLiteral(float f) : type("float"), float_val(f) {}
	ExprLiteral(int i) : type("int"), int_val(i) {}

	TypeDesc type;
};

template<> std::string NodeGenerateCode<ExprLiteral>(const LangSettings& lang, ExprLiteral& data);
template<> TypeDesc NodeDeduceType<ExprLiteral>(ExprLiteral& data);

//---------------------------------------------------------------------------------
// Statements
//---------------------------------------------------------------------------------
struct Assign
{
	std::string ident;
	Node* expr;
};

template<> std::string NodeGenerateCode<Assign>(const LangSettings& lang, Assign& data);
template<> void NodeDeclare<Assign>(Ast* ast, Assign& data);

struct StmtNativeCode
{
	StmtNativeCode() = default;
	StmtNativeCode(const std::string& code) : code(code) {}

	std::string code;
};

template<> std::string NodeGenerateCode<StmtNativeCode>(const LangSettings& lang, StmtNativeCode& data);

struct StmtIf
{
	StmtIf() = default;
	StmtIf(Node* expr, Node* trueStmt, Node* falseStmt) : expr(expr), trueStmt(trueStmt), falseStmt(falseStmt) {}

	Node* expr = nullptr;
	Node* trueStmt = nullptr;
	Node* falseStmt = nullptr; // optional
};

template<> std::string NodeGenerateCode<StmtIf>(const LangSettings& lang, StmtIf& data);
template<> void NodeDeclare<StmtIf>(Ast* ast, StmtIf& data);


struct StmtWhile
{
	StmtWhile() = default;
	StmtWhile(Node* expr, Node* bodyStmt) : expr(expr), bodyStmt(bodyStmt) {}

	Node* expr = nullptr;
	Node* bodyStmt = nullptr;
};

template<> std::string NodeGenerateCode<StmtWhile>(const LangSettings& lang, StmtWhile& data);
template<> void NodeDeclare<StmtWhile>(Ast* ast, StmtWhile& data);

struct StmtFor
{
	Node* vardecl;
	Node* boolExpr;
	Node* postExpr;
	Node* stmt;
};

template<> std::string NodeGenerateCode<StmtFor>(const LangSettings& lang, StmtFor& data);
template<> void NodeDeclare<StmtFor>(Ast* ast, StmtFor& data);

struct StmtList
{
	std::vector<Node*> nodes;
};

template<> std::string NodeGenerateCode<StmtList>(const LangSettings& lang, StmtList& data);
template<> void NodeDeclare<StmtList>(Ast* ast, StmtList& data);

struct VarDecl
{
	VarDecl() = default;

	VarDecl(TypeDesc type, std::string firstIdent, Node* firstExpr) : 
		type(type)
	{
		ident.push_back(firstIdent);
		expr.push_back(firstExpr);
	}

	TypeDesc type;//std::string type;
	std::vector<std::string> ident;
	std::vector<Node*> expr;
};

template<> std::string NodeGenerateCode<VarDecl>(const LangSettings& lang, VarDecl& data);
template<> void NodeDeclare<VarDecl>(Ast* ast, VarDecl& data);

struct FnDeclArgVarDecl
{
	FnDeclArgVarDecl() = default;

	FnDeclArgVarDecl(TypeDesc type, const std::string& ident, Node* const expr, FnCallArgType argType) :
		type(type), ident(ident), expr(expr), argType(argType)
	{}

	TypeDesc type;//std::string type;
	std::string ident; // The name of the variable.
	Node* expr;
	FnCallArgType argType; //in/out/inout.

};

template<> std::string NodeGenerateCode<FnDeclArgVarDecl>(const LangSettings& lang, FnDeclArgVarDecl& data);
template<> void NodeDeclare(Ast* ast, FnDeclArgVarDecl& data);

struct FuncDecl
{
	std::vector<Node*> args;
	TypeDesc retType;//std::string retType;
	std::string name;

	Node* stmt; // the body of the function.
};

template<> std::string NodeGenerateCode<FuncDecl>(const LangSettings& lang, FuncDecl& data);
template<> void NodeDeclare<FuncDecl>(Ast* ast, FuncDecl& data);

struct ProgramElem
{
	std::vector<Node*> nodes;
};

template<> std::string NodeGenerateCode<ProgramElem>(const LangSettings& lang, ProgramElem& data);
template<> void NodeDeclare<ProgramElem>(Ast* ast, ProgramElem& data);
