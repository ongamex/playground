#pragma once

#include <algorithm>

#include "ast.h"

namespace
{
	const std::string HLSL_ShaderResultStruct = "SGE_SHADER_RESULT";
	const std::string HLSL_ShaderResultVar = "sge_shader_result";
}

//-----------------------------------------------------------------------
// Ast
//-----------------------------------------------------------------------
std::string Ast::GenerateGlobalUniforms(const LangSettings& lang)
{
	std::string result;

	for(const auto& unif : uniforms)
	{
		result += "uniform " + unif.type.GetTypeAsString(lang) + " " + unif.varName + ";";

		if(lang.outputLanguage == OL_HLSL)
		{
			//[TODO] Arrays...
			if(unif.type.GetBuiltInType() == TypeDesc::Type_Texture2D) {
				result += "uniform sampler " + unif.varName  + "_sgeSS;";
			}
		}
	}

	return result;
}

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
	if(resolvedFvd.trait == Ast::FullVariableDesc::Trait_StageOutVarying)
	{
		return HLSL_ShaderResultVar + "." + identifier;
	}
	else
	{
		return identifier;
	}
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
			const bool isMatrixExpr = left->DeduceType(ast).GetBuiltInType() == TypeDesc::Type_mat4f 
				|| right->DeduceType(ast).GetBuiltInType() == TypeDesc::Type_mat4f;

			if(ast->lang.outputLanguage == OL_HLSL && isMatrixExpr)
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
		default :           return left->GenerateCode(ast) + (" ??? ") + right->GenerateCode(ast);
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
	if(resolvedType != TypeDesc()) return resolvedType;

	switch(type)
	{
		case EBT_Add : 
		case EBT_Sub :
		case EBT_Mul : 
		case EBT_Div : 
			if(resolvedType == TypeDesc()) resolvedType = TypeDesc::ResolveType(left->DeduceType(ast), right->DeduceType(ast));
			break;
		case EBT_Greater :
		case EBT_GEquals : 
		case EBT_Less :
		case EBT_LEquals :
		case EBT_Equals :
		case EBT_NEquals :
		case EBT_Or :
		case EBT_And :
			resolvedType = TypeDesc(TypeDesc::Type_bool);
			break;
		default :
			throw ParseExcept("Unknown type");
	}

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
	for(int t = TypeDesc::Type_BuiltInTypeBegin + 1; t < TypeDesc::Type_BuiltInTypeEnd; ++t)
	{
		const std::string typeName = TypeDesc::GetLangTypeName((TypeDesc::Type)t);
		
		if(fnName == typeName) 
		{
			TypeDesc type((TypeDesc::Type)t);
			callFnName = type.GetTypeAsString(ast->lang);
			break;
		}
	}
	
	// If this isn't a special function just call 
	if(callFnName.empty())
	{
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
	resolvedType = ast->findFuncDecl(fnName).retType;
	for(auto& arg : args) arg->Declare(ast);
}

TypeDesc FuncCall::Internal_DeduceType(Ast* ast)
{
	return resolvedType;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
std::string ExprLiteral::Internal_GenerateCode(Ast* ast)
{
	char buff[64] = {0};
	if(type.GetBuiltInType() == TypeDesc::Type_float)
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
	else if(type.GetBuiltInType() == TypeDesc::Type_int)
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

	return expr->GenerateCode(ast) + ";";
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
	if(name == "main")
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

std::string GenerateCode(const LangSettings& lang, const char* code)
{
	try 
	{
		Ast ast;
		ast.lang = lang;
		LangParseExpression(code, &ast);

		if(!ast.program)
		{
			throw ParseExcept("Failed while compiling program!");
		}

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

		// Declare the output varying of the HLSL vertex shader.
		if(lang.outputLanguage == OL_HLSL && lang.shaderType == ST_Vertex)
		{
			ast.declareVariable(TypeDesc(TypeDesc::Type_vec4f), "vertex_output", Ast::FullVariableDesc::Trait_StageOutVarying);
		}

		// Declare the global unifroms
		for(const auto& unif : ast.uniforms)
		{
			ast.declareVariable(unif.type, unif.varName);
		}

		// Declare everything else.
		ast.program->Declare(&ast);
		
		for(auto n : ast.deductionQueue) n->DeduceType(&ast);

		std::string code;
		code = ast.GenerateGlobalUniforms(lang) + ast.program->GenerateCode(&ast);
		return code;
	}
	catch(const std::exception& e) {
		printf(e.what());
	}

	return std::string();
}