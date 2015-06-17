#pragma once

#include <algorithm>

#include "ast.h"

void Node::Declare(Ast* ast)
{
	if(inBlock) ast->declPushScope();
	Internal_Declare(ast);
	if(inBlock) ast->declPopScope();
}

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

Ast::FullVariableDesc Ast::declareVariable(const TypeDesc& td, const std::string& name)
{
	FullVariableDesc fvd;

	for(auto s : scope) fvd.fullName += s + "::";

	fvd.fullName += name;
	fvd.type = td;

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

	while(depth > 0)
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
//
//-----------------------------------------------------------------------
std::string Ident::Internal_GenerateCode(Ast* ast)
{
	return identifier;
}

void Ident::Internal_Declare(Ast* ast)
{
	// Deduce the type during the declaration. This is esier becase we already know the current scope.
	// The correct solution would be to cache the current scope and deduce the type into the "type deduction" pass.
	auto var = ast->findVarInCurrentScope(identifier);
	resolvedType = var.type;
}

TypeDesc Ident::Internal_DeduceType(Ast* ast)
{
	return resolvedType;
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
	std::string retval = fnName + '(';
	
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
	return ident + " = " + expr->GenerateCode(ast);
}

void Assign::Internal_Declare(Ast* ast)
{
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
	std::string retval = retType.GetTypeAsString(ast->lang) + " " + name + "(";

	for(int t = 0; t < args.size(); ++t) {
		retval += args[t]->GenerateCode(ast);
		if(t < args.size() - 1) retval += ',';
	}

	retval += "){ " + stmt->GenerateCode(ast) + "}";

	return retval;
}

void FuncDecl::Internal_Declare(Ast* ast)
{
	ast->declPushScope(name);

	ast->declareFunction(retType, name);

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
		LangParseExpression(code, &ast);


		if(!ast.program)
		{
			throw ParseExcept("Failed while compiling program!");
		}

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