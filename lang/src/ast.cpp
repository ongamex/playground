#pragma once

#include <algorithm>

#include "ast.h"

namespace
{
	const std::string HLSL_ShaderResultStruct = "SGE_SHADER_RESULT";
	const std::string HLSL_ShaderResultVar = "sge_shader_result";
}

//-----------------------------------------------------------------------
//TypeDesc
//-----------------------------------------------------------------------
TypeDesc::TypeDesc(std::string strType)
{
	m_strType = strType;

	if(strType == "void") m_type = Type_void;
	else if(strType == "bool") m_type = Type_bool;
	else if(strType == "int") m_type = Type_int;
	else if(strType == "float") m_type = Type_float;
	else if(strType == "vec2f") m_type = Type_vec2f;
	else if(strType == "vec3f") m_type = Type_vec3f;
	else if(strType == "vec4f") m_type = Type_vec4f;
	else if(strType == "mat4f") m_type = Type_mat4f;
	else if(strType == "Texture2D") m_type = Type_Texture2D;
	else { m_type = Type_UserDefined; }
}

std::string TypeDesc::GetLangTypeName(const Type type)
{
	if(type == Type_void) return "void";
	if(type == Type_bool) return "bool";
	if(type == Type_int) return "int";
	if(type == Type_float) return "float";
	if(type == Type_vec2f) return "vec2f";
	if(type == Type_vec3f) return "vec3f";
	if(type == Type_vec4f) return "vec4f";
	if(type == Type_mat4f) return "mat4f";
	if(type == Type_Texture2D) return "Texture2D";

	throw ParseExcept("GetLangTypeName called with unknow argument");
}

TypeDesc TypeDesc::GetMemberType(const TypeDesc& parent, const std::string& member)
{
	//[TODO] This is sooo broken....
	const bool isFloatVectorType = 
			(parent.GetBuiltInType() == Type_vec2f) 
		|| (parent.GetBuiltInType() == Type_vec3f) 
		|| (parent.GetBuiltInType() == Type_vec4f);

	if(isFloatVectorType)
	{
		// Check if this is a swizzle.
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

std::string TypeDesc::GetTypeAsString(const LangSettings& lang) const 
{
	if(GetBuiltInType() == Type_void) return "void";
	else if(GetBuiltInType() == Type_int) return "int";
	else if(GetBuiltInType() == Type_float) return "float";
	else if(GetBuiltInType() == Type_bool) return "bool";
	else if(GetBuiltInType() == Type_vec2f) { if(lang.outputLanguage == OL_HLSL) return "float2"; else return "vec2"; }
	else if(GetBuiltInType() == Type_vec3f) { if(lang.outputLanguage == OL_HLSL) return "float3"; else return "vec3"; }
	else if(GetBuiltInType() == Type_vec4f) { if(lang.outputLanguage == OL_HLSL) return "float4"; else return "vec4"; }
	else if(GetBuiltInType() == Type_mat4f) { if(lang.outputLanguage == OL_HLSL) return "float4x4"; else return "mat4"; }
	else if(GetBuiltInType() == Type_Texture2D) { if(lang.outputLanguage == OL_HLSL) return "Texture2D"; else return "sampler2D"; } 
	else if(GetBuiltInType() == Type_UserDefined) {
		if(m_strType.empty()) return "<empty-str-type>";
		return m_strType;
	}

	return "<type-unknown>";
}

//-----------------------------------------------------------------------
// Ast
//-----------------------------------------------------------------------
Ast::FullVariableDesc Ast::declareVariable(const TypeDesc& td, const std::string& name, FullVariableDesc::Trait trait)
{
	FullVariableDesc fvd;

	for(auto s : scope) fvd.fullName += s + "::";

	fvd.fullName += name;
	fvd.type = td;
	fvd.trait = trait;

	std::find_if(begin(declaredVariables), end(declaredVariables), [&fvd, &name](FullVariableDesc v) {
		const bool equal = fvd.fullName == v.fullName;

		if(equal) {
			throw ParseExcept("Variable with name '" + name + "' is already defined!");
		}

		return equal;
	});

	declaredVariables.push_back(fvd);

	return fvd;
}

const Ast::FullVariableDesc& Ast::findVarInCurrentScope(const std::string& name)
{
	int depth = scope.size();
	std::string fullName;

	while(depth >= 0)
	{
		fullName.clear();
		for(int t = 0; t < depth; ++t) fullName+= scope[t] + "::";
		fullName += name;

		for(auto& v : declaredVariables)
		{
			if(v.fullName == fullName) return v;
		}

		depth--;
	}

	throw ParseExcept("Referenced an undefined variable: " + name);
}

const Ast::FullFuncionDesc& Ast::findFuncDecl(const std::string& name)
{
	for(auto& f : declaredFunctions)
	{
		if(f.fullName == name) return f;
	}

	throw ParseExcept("Referenced an undefined funcion: " + name);
}

void Ast::declareFunction(const TypeDesc& returnType, const std::string& name)
{
	declaredFunctions.push_back({name, returnType});
}

//-----------------------------------------------------------------------
// Node
//-----------------------------------------------------------------------
void Node::Declare(Ast* ast)
{
	if(inBlock) ast->declPushScope();
	Internal_Declare(ast);
	if(inBlock) ast->declPopScope();
}


//-----------------------------------------------------------------------
//
//-----------------------------------------------------------------------
std::string Ident::Internal_GenerateCode(Ast* ast)
{
	const bool hlsl = ast->OutLangIs(OL_HLSL);
	const bool glsl = ast->OutLangIs(OL_GLSL);

	if(hlsl && resolvedFvd.trait == Ast::FullVariableDesc::Trait_StageOutVarying)
	{
		return HLSL_ShaderResultVar + "." + identifier;
	}

	if(glsl && resolvedFvd.trait == Ast::FullVariableDesc::Trait_StageOutVarying)
	{
		if(identifier == "vertex_output") { return "gl_Position"; }
	}

	// Vertex attribute. For GLSL use the semantic name instead of the actual variable name.
	if(glsl && resolvedFvd.trait == Ast::FullVariableDesc::Trait_VertexAttribute)
	{
		for(const auto& attr : ast->vertexAttribs) {
			if(attr.varName == identifier) return attr.semantic;
		}

		throw ParseExcept("Attribute '" + identifier + "\' not found!");
	}

	// Just a regular variable I suppose.
	return identifier;
	
}

void Ident::Internal_Declare(Ast* ast)
{
	// Deduce the type during the declaration. This is esier becase we already know the current scope.
	// The correct solution would be to cache the current scope and deduce the type into the "type deduction" pass.
	resolvedFvd = ast->findVarInCurrentScope(identifier);
}

TypeDesc Ident::Internal_DeduceType(Ast* ast)
{
	return resolvedFvd.type;
}

//-----------------------------------------------------------------------
//
//-----------------------------------------------------------------------
std::string ExprMemberAccess::Internal_GenerateCode(Ast* ast)
{
	return expr->GenerateCode(ast) + "." + member;
}

void ExprMemberAccess::Internal_Declare(Ast* ast)
{
	expr->Declare(ast);
}

TypeDesc ExprMemberAccess::Internal_DeduceType(Ast* ast)
{
	if(resolvedType == TypeDesc())
	resolvedType = TypeDesc::GetMemberType(expr->DeduceType(ast), member);
	return resolvedType;

}

//-----------------------------------------------------------------------
//
//-----------------------------------------------------------------------
std::string ExprBin::Internal_GenerateCode(Ast* ast)
{
	switch(type) {
		case EBT_Add : return left->GenerateCode(ast) + (" + ") + right->GenerateCode(ast);
		case EBT_Sub : return left->GenerateCode(ast) + (" - ") + right->GenerateCode(ast);
		case EBT_Mul :
		{
			// in HLSL matrix multiplication is a bit odd. mathematical multiplication with matrices is
			// done with mul(m,?) while component whise matrix multiplication is done with *.
			const Type lt = left->DeduceType(ast).GetBuiltInType();
			const Type rt = right->DeduceType(ast).GetBuiltInType();

			const bool hasMatrix = (lt == Type_mat4f  || rt == Type_mat4f);
			const bool hasScalar = (lt == Type_float  || rt == Type_float) || (lt == Type_int  || rt == Type_int);

			const bool isAtLeastOneAscalar = 
				left->DeduceType(ast).GetBuiltInType() == Type_float 
				|| right->DeduceType(ast).GetBuiltInType() == Type_float;

			if(ast->lang.outputLanguage == OL_HLSL && hasMatrix && !hasScalar)
			{
				return "mul(" + left->GenerateCode(ast) + "," + right->GenerateCode(ast) + ")";
			}
			else 
			{
				return left->GenerateCode(ast) + (" * ") + right->GenerateCode(ast);
			}
		}
		case EBT_Div :      return left->GenerateCode(ast) + (" / ") + right->GenerateCode(ast);
		case EBT_Greater :  return left->GenerateCode(ast) + (" > ") + right->GenerateCode(ast);
		case EBT_GEquals :  return left->GenerateCode(ast) + (" >= ") + right->GenerateCode(ast);
		case EBT_Less :     return left->GenerateCode(ast) + (" < ") + right->GenerateCode(ast);
		case EBT_LEquals :  return left->GenerateCode(ast) + (" <= ") + right->GenerateCode(ast);
		case EBT_Equals :   return left->GenerateCode(ast) + (" == ") + right->GenerateCode(ast);
		case EBT_NEquals :  return left->GenerateCode(ast) + (" != ") + right->GenerateCode(ast);
		case EBT_Or :       return left->GenerateCode(ast) + (" || ") + right->GenerateCode(ast);
		case EBT_And :      return left->GenerateCode(ast) + (" && ") + right->GenerateCode(ast);
		default :           return left->GenerateCode(ast) + (" <unknown-bin-op> ") + right->GenerateCode(ast);
	}

	return "expr ??? expr";
}

void ExprBin::Internal_Declare(Ast* ast)
{
	left->Declare(ast);
	right->Declare(ast);
}

TypeDesc ExprBin::Internal_DeduceType(Ast* ast)
{
	// Check if the type has been already resolved
	if(resolvedType != Type_Undeduced) return resolvedType;

	// Resolve the arguments type.
	const auto lt = left->DeduceType(ast);
	const auto rt = right->DeduceType(ast);

	// Just a helper function...
	auto isPairOf = [lt, rt](Type a, Type b) {
	return (lt.GetBuiltInType() == a && rt.GetBuiltInType() == b) ||
			(lt.GetBuiltInType() == b && rt.GetBuiltInType() == a);
	};

	// Deduce the type.
	switch(type)
	{
		case EBT_Add : 
		case EBT_Sub :
		{
			if(lt != rt) 
				throw ParseExcept("+/- operator called with mixed types: " + TypeDesc::GetLangTypeName(lt.GetBuiltInType()) + " " + TypeDesc::GetLangTypeName(rt.GetBuiltInType()));
		
			resolvedType = lt;
			break;
		}

		case EBT_Mul : 
		{
			if(lt == rt) resolvedType = lt;
			else if(isPairOf(Type_int, Type_float)) resolvedType = TypeDesc(Type_float);
			else if(isPairOf(Type_float, Type_vec2f)) resolvedType = TypeDesc(Type_vec2f);
			else if(isPairOf(Type_float, Type_vec3f)) resolvedType = TypeDesc(Type_vec3f);
			else if(isPairOf(Type_float, Type_vec4f)) resolvedType = TypeDesc(Type_vec4f);
			else if(isPairOf(Type_mat4f, Type_vec4f)) resolvedType = TypeDesc(Type_vec4f);
			else if(isPairOf(Type_mat4f, Type_float)) resolvedType = TypeDesc(Type_mat4f);
			else if(isPairOf(Type_mat4f, Type_int)) resolvedType = TypeDesc(Type_mat4f);
			
			// The type should be deduced by now, if not this is an error.
			if(resolvedType == Type_Undeduced)
				throw ParseExcept("* operator called with incompatible types: " + TypeDesc::GetLangTypeName(lt.GetBuiltInType()) + " " + TypeDesc::GetLangTypeName(rt.GetBuiltInType()));
		
			break;
		}
		
		case EBT_Div :
		{
			if(isPairOf(Type_float, Type_float)) resolvedType = TypeDesc(Type_float);
			else if(isPairOf(Type_int, Type_int)) resolvedType = TypeDesc(Type_int);

			// The type should be deduced by now, if not this is an error.
			if(resolvedType == Type_Undeduced)
				throw ParseExcept("/ operator called with incompatible types: " + TypeDesc::GetLangTypeName(lt.GetBuiltInType()) + " " + TypeDesc::GetLangTypeName(rt.GetBuiltInType()));
			break;
		}
		
		// Logical operators. Just ignore the arg types and return a boolean.
		case EBT_Greater :
		case EBT_GEquals : 
		case EBT_Less :
		case EBT_LEquals :
		case EBT_Equals :
		case EBT_NEquals :
		case EBT_Or :
		case EBT_And :
		{
			resolvedType = TypeDesc(Type_bool);
			break;
		}
		default :
			throw ParseExcept("Unknown binary expression type!");
	}

	if(resolvedType == Type_Undeduced) throw("ExprBin type deduction failed");

	return resolvedType;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
std::string FuncCall::Internal_GenerateCode(Ast* ast)
{
	// Check if this is a special function.

	std::string callFnName; // Stores the actual function name that will be called.

	// Check if this is a type constructor.
	for(int t = Type_BuiltInTypeBegin + 1; t < Type_BuiltInTypeEnd; ++t)
	{
		const std::string typeName = TypeDesc::GetLangTypeName((Type)t);
		
		if(fnName == typeName) 
		{
			TypeDesc type((Type)t);
			callFnName = type.GetTypeAsString(ast->lang);
			break;
		}
	}

	// Both hlsl and glsl lerp/mix functions are supported.
	if(ast->OutLangIs(OL_GLSL) && fnName == "lerp") callFnName = "mix";
	if(ast->OutLangIs(OL_HLSL) && fnName == "mix") callFnName = "lerp";
	
	// If this is just a regular fn call.
	if(callFnName.empty()) {
		callFnName = fnName;
	}

	std::string retval = callFnName + '(';
	
	for(int t = 0; t < args.size(); ++t) {
		retval += args[t]->GenerateCode(ast);
		if(t < args.size() - 1) retval += ",";
	}

	retval += ')';
	
	return retval;
}

void FuncCall::Internal_Declare(Ast* ast)
{
	for(auto& arg : args) arg->Declare(ast);
}

TypeDesc FuncCall::Internal_DeduceType(Ast* ast)
{
	if(resolvedType != Type_Undeduced) return resolvedType;

	//[HARDCODED]
	// Function calls type deduction has special behavior for some specific functions that is hardcoded here.
	// The right thing to do is to support multiple function declaration(based on the argument types),
	// but currently these functions are the only real cases(or at least known to me).
	if(	fnName == "lerp" || fnName == "mix" // linear interpolation support both hlsl "lerp" and glsl "mix".
		|| fnName == "clamp")
	{
		if(args.size() != 3) throw ParseExcept("lerp called with wrong arg count(should be 3: x a,b)");

		if(args[0]->DeduceType(ast) != Type_float) throw ParseExcept("lerp interpolation coeff isn't  a float!"); // the interpolation coeff must be a float.
		if(args[1]->DeduceType(ast) != args[2]->DeduceType(ast)) throw ParseExcept("lerp mixed arguments type");

		resolvedType = args[1]->DeduceType(ast);
	}

	// Check if this is a type constructor.
	if(resolvedType == Type_Undeduced)
	for(int t = Type_BuiltInTypeBegin + 1; t < Type_BuiltInTypeEnd; ++t)
	{
		const std::string typeName = TypeDesc::GetLangTypeName((Type)t);
		
		if(fnName == typeName) 
		{
			resolvedType = TypeDesc((Type)t);
			break;
		}
	}

	// Just a regualr function call.
	if(resolvedType == Type_Undeduced)
	{	
		resolvedType = ast->findFuncDecl(fnName).retType;
	}

	return resolvedType;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
std::string ExprLiteral::Internal_GenerateCode(Ast* ast)
{
	char buff[64] = {0};
	if(type.GetBuiltInType() == Type_float)
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
	else if(type.GetBuiltInType() == Type_int)
	{
		sprintf(buff, "%d", int_val);
		return buff;
	}

	return "???";
}

TypeDesc ExprLiteral::Internal_DeduceType(Ast* ast) 
{
	return type;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
std::string Assign::Internal_GenerateCode(Ast* ast)
{
	return lval->GenerateCode(ast) + " = " + expr->GenerateCode(ast);
}

void Assign::Internal_Declare(Ast* ast)
{
	lval->Declare(ast);
	expr->Declare(ast);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
std::string StmtNativeCode::Internal_GenerateCode(Ast* ast)
{
	return code;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
std::string StmtIf::Internal_GenerateCode(Ast* ast)
{
	std::string retval = "if(" + expr->GenerateCode(ast) + ")";
	if(trueStmt) retval += trueStmt->GenerateCode(ast); else retval += ';';
	if(falseStmt) retval += "else " + falseStmt->GenerateCode(ast);
	return retval;
}

void StmtIf::Internal_Declare(Ast* ast)
{
	if(trueStmt)
	{
		ast->declPushScope();
		trueStmt->Declare(ast);
		ast->declPopScope();
	}

	if(falseStmt)
	{
		ast->declPushScope();
		falseStmt->Declare(ast);
		ast->declPopScope();
	}
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
std::string StmtWhile::Internal_GenerateCode(Ast* ast)
{
	std::string retval = "while(" + expr->GenerateCode(ast) + ")";
	if(bodyStmt) retval += bodyStmt->GenerateCode(ast); 
	else retval += ';';
	return retval;
}

void StmtWhile::Internal_Declare(Ast* ast)
{
	if(bodyStmt)
	{
		ast->declPushScope();
		bodyStmt->Declare(ast);
		ast->declPopScope();
	}
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
std::string StmtFor::Internal_GenerateCode(Ast* ast)
{
	std::string retval = "for(";
	if(vardecl) retval +=  vardecl->GenerateCode(ast); retval += ';';
	if(boolExpr) retval += boolExpr->GenerateCode(ast); retval += ';';
	if(postExpr) retval += postExpr->GenerateCode(ast); 
	retval += ')';
	retval += stmt->GenerateCode(ast);

	return retval;
}

void StmtFor::Internal_Declare(Ast* ast)
{
	if(vardecl)
	{
		ast->declPushScope();
		vardecl->Declare(ast);
		ast->declPopScope();
	}

	if(stmt) 
	{
		ast->declPushScope();
		stmt->Declare(ast);
		ast->declPopScope();
	}
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
std::string StmtReturn::Internal_GenerateCode(Ast* ast)
{
	if(expr != nullptr)
	{
		return std::string("return ") + expr->GenerateCode(ast) + ";";
	}

	return "return;";
}

void StmtReturn::Internal_Declare(Ast* ast)
{
	if(expr) expr->Declare(ast);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
std::string StmtList::Internal_GenerateCode(Ast* ast)
{
	std::string retval;
	for(auto& node : nodes) retval += node->GenerateCode(ast);
	return retval;
}

void StmtList::Internal_Declare(Ast* ast)
{
	for(auto& node : nodes) {
		node->Declare(ast);
	}
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
std::string VarDecl::Internal_GenerateCode(Ast* ast)
{
	std::string retval = type.GetTypeAsString(ast->lang) + " ";

	for(int t = 0; t < ident.size(); ++t)
	{
		retval += ident[t];
		if(expr[t]) retval += "=" + expr[t]->GenerateCode(ast);
		if(t < ident.size() - 1) retval += ',';
	}

	return retval;
}

void VarDecl::Internal_Declare(Ast* ast)
{
	for(int t = 0; t < ident.size(); ++t)
	{
		ast->declareVariable(type, ident[t]);
	}
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
std::string FnDeclArgVarDecl::Internal_GenerateCode(Ast* ast)
{
	std::string retval;
	if(argType == FNAT_InOut) retval += "inout ";
	if(argType == FNAT_Out) retval += "out ";

	retval += type.GetTypeAsString(ast->lang) + " " + ident;
	if(expr) retval += "=" + expr->GenerateCode(ast);
	return retval;
}

void FnDeclArgVarDecl::Internal_Declare(Ast* ast)
{
	ast->declareVariable(type, ident);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
std::string FuncDecl::Internal_GenerateCode(Ast* ast)
{
	std::string retval;

	// Check if this is a special function, that needs special attention.
	// For GLSL the main function is just a regular function.
	if(ast->OutLangIs(OL_HLSL) && name == "main")
	{
		retval += GenerateMainFuncHLSL(ast);
	}
	else
	{
		// Just a regular function.
		retval = retType.GetTypeAsString(ast->lang) + " " + name + "(";

		for(int t = 0; t < args.size(); ++t) {
			retval += args[t]->GenerateCode(ast);
			if(t < args.size() - 1) retval += ',';
		}

		retval += "){" + stmt->GenerateCode(ast) + "}";
	}

	return retval;
}

std::string FuncDecl::GenerateMainFuncHLSL(Ast* ast)
{
	std::string retval;

	// 1st output the definition of the result strcture for the main function. 
	// Usually this is just output varyings + stage specific output.
	{
		retval += "struct " + HLSL_ShaderResultStruct + " {";
		for(const auto& var : ast->stageOutputVaryings) {
			retval += var.type.GetTypeAsString(ast->lang) + " " + var.varName + " : " + var.varName + ";";
		}

		// Add the stage specific output.
		if(ast->lang.shaderType == ST_Vertex) {
			retval += "float3 vertex_output : SV_Position;";
		}

		retval += "};";
	}

	//The function arguments, usually vertex attributes or input varyings.
	{
		retval += HLSL_ShaderResultStruct + " main(";

		// Vertex attributes.
		for(auto& attrib : ast->vertexAttribs) {
			retval += attrib.type.GetTypeAsString(ast->lang) + " " + attrib.varName + " : " + attrib.semantic + ",";
		}

		// Input varyings.
		for(auto& var : ast->stageInputVaryings) {
			retval += var.type.GetTypeAsString(ast->lang) + " " + var.varName + " : " + var.varName + ",";
		}

		// Pop the last comma.
		if(retval.back() == ',') retval.pop_back(); 

		retval += ")";
	}

	// Fianlly generate the function body itself.
	// Also add at the begining and and at the ending 
	// the shader program result(varyings, vertex, fargment data ect.)
	{
		retval += '{';
		retval += HLSL_ShaderResultStruct + " " + HLSL_ShaderResultVar + ";";
		retval += stmt->GenerateCode(ast);
		retval += "return " + HLSL_ShaderResultVar + ";";
		retval += '}';
	}

	return retval;
}


void FuncDecl::Internal_Declare(Ast* ast)
{
	ast->declPushScope(name);

	ast->declareFunction(retType, name);

	// Declare the local variables
	for(auto& var : args) var->Declare(ast);
	stmt->Declare(ast);

	ast->declPopScope();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
std::string ProgramElem::Internal_GenerateCode(Ast* ast)
{
	std::string retval;

	for(const auto& node : nodes) {
		retval += node->GenerateCode(ast);
	}

	return retval;
}

void ProgramElem::Internal_Declare(Ast* ast)
{
	for(auto& node : nodes) {
		node->Declare(ast);
	}
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------

// Declared in lang.y
bool LangParseExpression(const char* code, Ast* ast);

std::string GenerateCode(const LangSettings& lang, const char* pCode)
{
	try 
	{
		Ast ast;
		ast.lang = lang;
		LangParseExpression(pCode, &ast); // Build the AST tree.
		std::string code;

		if(!ast.program) {
			throw ParseExcept("Failed while compiling program!");
		}

		// Declare the predefined functions for the language.
		// JUST A REMINDIER: 
		// DOUBLE CHECK THE ORDER OF THE ARGUMENTS OF THE NATIVE FUNCTIONS.
		{
			// [TODO] find a way to implement lerp.clamp ect. they depend on the input type.
			//// Declare lerp.
			//// Keep in mind that we are defining the functions below with float return type. But actually they heve a spec for almost every type.
			//// For now we are safe becase we only care if the expression type is a matrix or not.
			//ast.declareFunction(Type_float, "lerp"); // Lerp is called mix in GLSL. This case is handled in FuncCall.
			//ast.declareFunction(Type_float, "clamp");

			// For hlsl trigonometrix functions have vector type specializations, but for now lets pretend
			// that there isn't.
			ast.declareFunction(Type_float, "sin");
			ast.declareFunction(Type_float, "cos");
			ast.declareFunction(Type_float, "tan");
			ast.declareFunction(Type_float, "tan2");

			ast.declareFunction(Type_float, "asin");
			ast.declareFunction(Type_float, "acos");
			ast.declareFunction(Type_float, "atan");

			ast.declareFunction(Type_float, "sincos");

			ast.declareFunction(Type_float, "sqrt");
			ast.declareFunction(Type_float, "rsqrt");

		}

		// Declare the vertex attributes, io varyings, and uniforms
		{
			// Vertex Attributes.
			// [TODO] Reconcider to declare these values as local variable in main.
			for(const auto& var : ast.vertexAttribs) {
				ast.declareVariable(var.type, var.varName, Ast::FullVariableDesc::Trait_VertexAttribute);
			}

			// Input varyings. 
			// [TODO] Reconcider to declare these values as local variable in main.
			for(const auto& var : ast.stageInputVaryings)
			{
				ast.declareVariable(var.type, var.varName, Ast::FullVariableDesc::Trait_StageInVarying);
			}

			// Output varyings.
			// [TODO] Reconcider to declare these values as local variable in main.
			for(const auto& var : ast.stageOutputVaryings)
			{
				ast.declareVariable(var.type, var.varName, Ast::FullVariableDesc::Trait_StageOutVarying);
			}

			// Declare the output varying of the HLSL.
			ast.declareVariable(TypeDesc(Type_vec4f), "vertex_output", Ast::FullVariableDesc::Trait_StageOutVarying);
		

			// Declare the global unifroms
			for(const auto& unif : ast.uniforms)
			{
				ast.declareVariable(unif.type, unif.varName);
			}
		}

		// GENERATE the declaration code for the attrib varyings for GLSL
		if(ast.OutLangIs(OL_GLSL))
		{
			// GLSL vertex attributes input and output varyings...

			// Keep in mind that in GLSL there are no sematics. So for vertex attributes
			// we are going to output the semantic rater than the variable name.
			for(const auto& var : ast.vertexAttribs)
			{
				code += "attribute " + var.type.GetTypeAsString(lang) + " " + var.semantic + ";";
			}

			for(const auto& var : ast.stageInputVaryings)
			{
				// [TODO] for older versions of GLSL this should be "vaying" instead of in
				code += "in " + var.type.GetTypeAsString(lang) + " " + var.varName + ";";
			}

			for(const auto& var : ast.stageOutputVaryings)
			{
				// [TODO] for older versions of GLSL this should be "vaying" instead of out
				code += "out " + var.type.GetTypeAsString(lang) + " " + var.varName + ";";
			}
		}

		// GENERATE the declaration code for uniforms for both GLSL and HLSL
		for(const auto& unif : ast.uniforms)
		{
			code += "uniform " + unif.type.GetTypeAsString(lang) + " " + unif.varName + ";";

			// Texture for HLSL need a sampler. Define 1 sampler for every texture.
			if(lang.outputLanguage == OL_HLSL)
			{
				//[TODO] Arrays...
				if(unif.type.GetBuiltInType() == Type_Texture2D) {
					code += "uniform sampler " + unif.varName  + "_sgeSS;";
				}
			}
		}

		// Declare everything else.
		ast.program->Declare(&ast);
		
		// Deduce a type for every expression that was matched by bison.
		for(auto n : ast.deductionQueue) n->DeduceType(&ast);

		// Finally genrate the code form the AST treee.
		code += ast.program->GenerateCode(&ast);
		return code;
	}
	catch(const std::exception& e) {
		printf(e.what());
	}

	return std::string();
}