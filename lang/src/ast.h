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

std::string GenerateCode(const LangSettings& lang, const char* code);

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
public : 

	Node() {}
	virtual ~Node() = default;

	template<typename T> T& As() { return *(T*)this; }

	std::string GenerateCode(Ast* ast) {
		
		std::string retval = Internal_GenerateCode(ast);

		if(inParens) retval = '(' + retval +')';
		if(exprSign < 0) retval = '-' + retval;
		if(hasSemicolon) retval += ";";
		if(inBlock) retval = "{" + retval + "}";

		return retval;
	}
	
	void Declare(Ast* ast);

	TypeDesc DeduceType(Ast* ast) { return Internal_DeduceType(ast); }

private :

	virtual std::string Internal_GenerateCode(Ast* ast) { return std::string(); }
	virtual void Internal_Declare(Ast* ast) { }
	virtual TypeDesc Internal_DeduceType(Ast* ast) { return TypeDesc(); }

public :

	int exprSign = 1; // The sign of the expression. Used for -expr for example.
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
	inline T* add() {
		nodes.push_back(new T);
		return (T*)nodes.back();
	}
	
	template<typename T, typename... Args>
	T* push(Args... args) {
		T* node = new T(args...);
		add(node);
		return node;
	}

	void declPushScope() {
		static int scopeIndex;
		char srtScope[32];
		sprintf(srtScope, "@scp_%d", scopeIndex);
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

		enum Trait
		{
			Trait_Regular, // Just a regual variable.
			Trait_Varying, // A varying variable.
		};


		std::string fullName;
		TypeDesc type;
		Trait trait;
	};

	struct FullFuncionDesc {
		std::string fullName;
		TypeDesc retType;
	};

	std::string GenerateGlobalUniforms(const LangSettings& lang);

	// Declares a variable at the current scope.
	FullVariableDesc declareVariable(const TypeDesc& td, const std::string& name,  FullVariableDesc::Trait trait = FullVariableDesc::Trait_Regular);
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

	LangSettings lang;
};

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
struct Ident : public Node
{
	Ident() = default;
	Ident(const std::string& identifier) :
		identifier(identifier)
	{}

	std::string Internal_GenerateCode(Ast* ast) override;
	void Internal_Declare(Ast* ast) override;
	TypeDesc Internal_DeduceType(Ast* ast) override;

	std::string identifier;
	Ast::FullVariableDesc resolvedFvd;
};

struct ExprMemberAccess : public Node
{
	ExprMemberAccess() = default;
	ExprMemberAccess(Node* expr, const std::string& member) :
		expr(expr), member(member)
	{}

	std::string Internal_GenerateCode(Ast* ast) override;
	void Internal_Declare(Ast* ast) override;
	TypeDesc Internal_DeduceType(Ast* ast) override;

	Node* expr;
	std::string member;

	TypeDesc resolvedType; 
};


//---------------------------------------------------------------------------------
// Expressions
//---------------------------------------------------------------------------------

// Binary expression of kind: a ? b
struct ExprBin : public Node
{
	ExprBin() = default;
	ExprBin(ExprBinType type, Node* left, Node* right) :
		type(type), left(left), right(right)
	{}

	std::string Internal_GenerateCode(Ast* ast) override;
	void Internal_Declare(Ast* ast) override;
	TypeDesc Internal_DeduceType(Ast* ast) override;

	ExprBinType type;
	Node* left;
	Node* right;

	TypeDesc resolvedType;
};


struct FuncCall : public Node
{
	std::string fnName;
	std::vector<Node*> args;

	std::string Internal_GenerateCode(Ast* ast) override;
	void Internal_Declare(Ast* ast) override;
	TypeDesc Internal_DeduceType(Ast* ast) override;

	TypeDesc resolvedType;
};

// Literal value
struct ExprLiteral : public Node
{
	union
	{
		int int_val;
		float float_val;
	};

	ExprLiteral() : type() {}
	ExprLiteral(float f) : type("float"), float_val(f) {}
	ExprLiteral(int i) : type("int"), int_val(i) {}

	std::string Internal_GenerateCode(Ast* ast) override;
	TypeDesc Internal_DeduceType(Ast* ast) override;

	TypeDesc type;
};

//---------------------------------------------------------------------------------
// Statements
//---------------------------------------------------------------------------------
struct Assign : public Node
{
	Assign(const std::string& ident, Node* expr) :
		ident(ident), expr(expr)
	{}

	std::string ident;
	Node* expr;

	std::string Internal_GenerateCode(Ast* ast) override;
	void Internal_Declare(Ast* ast) override;
};

struct StmtNativeCode : public Node
{
	StmtNativeCode() = default;
	StmtNativeCode(const std::string& code) : code(code) {}

	std::string Internal_GenerateCode(Ast* ast) override;

	std::string code;
};

struct StmtIf : public Node
{
	StmtIf() = default;
	StmtIf(Node* expr, Node* trueStmt, Node* falseStmt) : expr(expr), trueStmt(trueStmt), falseStmt(falseStmt) {}

	std::string Internal_GenerateCode(Ast* ast) override;
	void Internal_Declare(Ast* ast) override;

	Node* expr = nullptr;
	Node* trueStmt = nullptr;
	Node* falseStmt = nullptr; // optional
};

struct StmtWhile : public Node
{
	StmtWhile() = default;
	StmtWhile(Node* expr, Node* bodyStmt) : expr(expr), bodyStmt(bodyStmt) {}

	std::string Internal_GenerateCode(Ast* ast) override;
	void Internal_Declare(Ast* ast) override;

	Node* expr = nullptr;
	Node* bodyStmt = nullptr;
};

struct StmtFor : public Node
{
	StmtFor(Node* vardecl, Node* boolExpr, Node* postExpr, Node* stmt) :
		vardecl(vardecl), boolExpr(boolExpr), postExpr(postExpr), stmt(stmt)
	{}

	std::string Internal_GenerateCode(Ast* ast) override;
	void Internal_Declare(Ast* ast) override;

	Node* vardecl = nullptr;
	Node* boolExpr = nullptr;
	Node* postExpr = nullptr;
	Node* stmt = nullptr;
};

struct StmtReturn : public Node
{
	StmtReturn() = default;
	StmtReturn(Node* expr) : expr(expr) {}

	std::string Internal_GenerateCode(Ast* ast) override;
	void Internal_Declare(Ast* ast) override;

	Node* expr = nullptr;
};

struct StmtList : public Node
{
	std::string Internal_GenerateCode(Ast* ast) override;
	void Internal_Declare(Ast* ast) override;

	std::vector<Node*> nodes;
};

struct VarDecl : public Node
{
	VarDecl() = default;

	VarDecl(TypeDesc type, std::string firstIdent, Node* firstExpr) : 
		type(type)
	{
		ident.push_back(firstIdent);
		expr.push_back(firstExpr);
	}

	std::string Internal_GenerateCode(Ast* ast) override;
	void Internal_Declare(Ast* ast) override;

	TypeDesc type;//std::string type;
	std::vector<std::string> ident;
	std::vector<Node*> expr;
};

struct FnDeclArgVarDecl : public Node
{
	FnDeclArgVarDecl() = default;

	FnDeclArgVarDecl(TypeDesc type, const std::string& ident, Node* const expr, FnCallArgType argType) :
		type(type), ident(ident), expr(expr), argType(argType)
	{}

	std::string Internal_GenerateCode(Ast* ast) override;
	void Internal_Declare(Ast* ast) override;

	TypeDesc type;//std::string type;
	std::string ident; // The name of the variable.
	Node* expr;
	FnCallArgType argType; //in/out/inout.

};

struct FuncDecl : public Node
{
	std::vector<Node*> args;
	TypeDesc retType;//std::string retType;
	std::string name;

	std::string Internal_GenerateCode(Ast* ast) override;
	void Internal_Declare(Ast* ast) override;

	Node* stmt; // the body of the function.
};

struct ProgramElem : public Node
{
	std::string Internal_GenerateCode(Ast* ast) override;
	void Internal_Declare(Ast* ast) override;

	std::vector<Node*> nodes;
};