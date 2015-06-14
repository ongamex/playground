#pragma once

#include <algorithm>

#include "ast.h"

void Node::NodeDeclare(Ast* ast)
{
	if(inBlock) ast->declPushScope();
	data.NodeDelcare(ast);
	if(inBlock) ast->declPopScope();
}

Ast::FullVariableDesc Ast::declareVariable(const TypeDesc& td, const std::string& name)
{
	FullVariableDesc fvd;

	for(auto s : scope) fvd.fullName += s + "::";

	fvd.fullName += name;
	fvd.type = td;

	std::find_if(begin(declaredVariables), end(declaredVariables), [&fvd, &name](FullVariableDesc v) {
		const bool equal = fvd.fullName == v.fullName;
		if(equal) throw ParseExcept("Variable with name '" + name + "' is already defined!");
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

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
template<>
std::string NodeGenerateCode<Ident>(const LangSettings& lang, Ident& data)
{
	return data.identifier;
}

template<> void NodeDeclare<Ident>(Ast* ast, Ident& data)
{
	auto var = ast->findVarInCurrentScope(data.identifier);
	data.resolvedType = var.type;
}

template<> TypeDesc NodeDeduceType<Ident>(Ident& data)
{
	return data.resolvedType;
}

//-----------------------------------------------------------------------
//
//-----------------------------------------------------------------------
template<>
std::string NodeGenerateCode<ExprBin>(const LangSettings& lang, ExprBin& data)
{
	Node* left = data.left;
	Node* right = data.right;

	switch(data.type) {
		case EBT_Add :      return left->NodeGenerateCode(lang) + (" + ") + right->NodeGenerateCode(lang);
		case EBT_Sub :      return left->NodeGenerateCode(lang) + (" - ") + right->NodeGenerateCode(lang);
		case EBT_Mul :
		{
			const bool isMatrixExpr = left->NodeDeduceType().GetBuiltInType() == TypeDesc::Type_mat4f || right->NodeDeduceType().GetBuiltInType() == TypeDesc::Type_mat4f;

			if(lang.outputLanguage == OL_HLSL && isMatrixExpr)
			{
				return "mul(" + left->NodeGenerateCode(lang) + "," + right->NodeGenerateCode(lang) + ")";
			}
			else 
			{
				return left->NodeGenerateCode(lang) + (" * ") + right->NodeGenerateCode(lang);
			}
		}
		case EBT_Div :      return left->NodeGenerateCode(lang) + (" / ") + right->NodeGenerateCode(lang);
		case EBT_Greater :  return left->NodeGenerateCode(lang) + (" > ") + right->NodeGenerateCode(lang);
		case EBT_GEquals :  return left->NodeGenerateCode(lang) + (" >= ") + right->NodeGenerateCode(lang);
		case EBT_Less :     return left->NodeGenerateCode(lang) + (" < ") + right->NodeGenerateCode(lang);
		case EBT_LEquals :  return left->NodeGenerateCode(lang) + (" <= ") + right->NodeGenerateCode(lang);
		case EBT_Equals :   return left->NodeGenerateCode(lang) + (" == ") + right->NodeGenerateCode(lang);
		case EBT_NEquals :  return left->NodeGenerateCode(lang) + (" != ") + right->NodeGenerateCode(lang);
		case EBT_Or :       return left->NodeGenerateCode(lang) + (" || ") + right->NodeGenerateCode(lang);
		case EBT_And :      return left->NodeGenerateCode(lang) + (" && ") + right->NodeGenerateCode(lang);
		default :           return left->NodeGenerateCode(lang) + (" ??? ") + right->NodeGenerateCode(lang);
	}

	return "expr ??? expr";
}

template<> void NodeDeclare<ExprBin>(Ast* ast, ExprBin& data)
{
	data.left->NodeDeclare(ast);
	data.right->NodeDeclare(ast);
}

template<> TypeDesc NodeDeduceType<ExprBin>(ExprBin& data)
{
	if(data.resolvedType == TypeDesc()) data.resolvedType = TypeDesc::ResolveType(data.left->NodeDeduceType(), data.right->NodeDeduceType());
	return data.resolvedType;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
template<> std::string NodeGenerateCode<FuncCall>(const LangSettings& lang, FuncCall& data)
{
	std::string retval = data.fnName + '(';
	
	for(int t = 0; t < data.args.size(); ++t) {
		retval += data.args[t]->NodeGenerateCode(lang);
		if(t < data.args.size() - 1) retval += ",";
	}

	retval += ')';
	
	return retval;
}

template<> void NodeDeclare<FuncCall>(Ast* ast, FuncCall& data)
{
	data.resolvedType = ast->findFuncDecl(data.fnName).retType;
	for(auto& arg : data.args) arg->NodeDeclare(ast);
}

template<> TypeDesc NodeDeduceType(FuncCall& data)
{
	return data.resolvedType;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
template<>
std::string NodeGenerateCode<ExprLiteral>(const LangSettings& lang, ExprLiteral& data)
{
	char buff[64] = {0};
	if(data.type.GetBuiltInType() == TypeDesc::Type_float)
	{
		sprintf(buff, "%f", data.float_val);

		// kill the trailing zeroes.
		for(int t = strlen(buff);t > 1; --t){
			if(buff[t] == '0' && buff[t-1] == '0') {
				buff[t] = '\0';
			}
			if(buff[t] == '.') break;
		}

		return buff;
	}
	else if(data.type.GetBuiltInType() == TypeDesc::Type_int)
	{
		sprintf(buff, "%d", data.int_val);
		return buff;
	}

	return "???";
}

template<> TypeDesc NodeDeduceType(ExprLiteral& data) {
	return data.type;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
template<>
std::string NodeGenerateCode<Assign>(const LangSettings& lang, Assign& data)
{
	return data.ident + " = " + data.expr->NodeGenerateCode(lang);
}

template<> void NodeDeclare<Assign>(Ast* ast, Assign& data)
{
	data.expr->NodeDeclare(ast);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
template<>
std::string NodeGenerateCode<StmtIf>(const LangSettings& lang, StmtIf& data)
{
	std::string retval = "if(" + data.expr->NodeGenerateCode(lang) + ")";
	if(data.trueStmt) retval += data.trueStmt->NodeGenerateCode(lang); else retval += ';';
	if(data.falseStmt) retval += "else " + data.falseStmt->NodeGenerateCode(lang);
	return retval;
}

template<> void NodeDeclare<StmtIf>(Ast* ast, StmtIf& data)
{
	if(data.trueStmt)
	{
		ast->declPushScope();
		data.trueStmt->NodeDeclare(ast);
		ast->declPopScope();
	}

	if(data.falseStmt)
	{
		ast->declPushScope();
		data.falseStmt->NodeDeclare(ast);
		ast->declPopScope();
	}
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
template<>
std::string NodeGenerateCode<StmtWhile>(const LangSettings& lang, StmtWhile& data)
{
	std::string retval = "while(" + data.expr->NodeGenerateCode(lang) + ")";
	if(data.bodyStmt) retval += data.bodyStmt->NodeGenerateCode(lang); 
	else retval += ';';
	return retval;
}

template<> void NodeDeclare<StmtWhile>(Ast* ast, StmtWhile& data)
{
	if(data.bodyStmt)
	{
		ast->declPushScope();
		data.bodyStmt->NodeDeclare(ast);
		ast->declPopScope();
	}
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
template<>
std::string NodeGenerateCode<StmtFor>(const LangSettings& lang, StmtFor& data)
{
	std::string retval = "for(";
	if(data.vardecl) retval +=  data.vardecl->NodeGenerateCode(lang); retval += ';';
	if(data.boolExpr) retval += data.boolExpr->NodeGenerateCode(lang); retval += ';';
	if(data.postExpr) retval += data.postExpr->NodeGenerateCode(lang); 
	retval += ')';
	retval += data.stmt->NodeGenerateCode(lang);

	return retval;
}

template<> void NodeDeclare<StmtFor>(Ast* ast, StmtFor& data)
{
	if(data.vardecl)
	{
		ast->declPushScope();
		data.vardecl->NodeDeclare(ast);
		ast->declPopScope();
	}

	if(data.stmt) 
	{
		ast->declPushScope();
		data.stmt->NodeDeclare(ast);
		ast->declPopScope();
	}
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
template<>
std::string NodeGenerateCode<StmtList>(const LangSettings& lang, StmtList& data)
{
	std::string retval;
	for(auto& node : data.nodes) retval += node->NodeGenerateCode(lang);
	return retval;
}

template<> void NodeDeclare<StmtList>(Ast* ast, StmtList& data)
{
	for(auto& node : data.nodes) node->NodeDeclare(ast);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
template<>
std::string NodeGenerateCode<VarDecl>(const LangSettings& lang, VarDecl& data)
{
	std::string retval = data.type.GetTypeAsString(lang) + " ";

	for(int t = 0; t < data.ident.size(); ++t)
	{
		retval += data.ident[t];
		if(data.expr[t]) {
			retval += "=" + data.expr[t]->NodeGenerateCode(lang);
		}

		if(t < data.ident.size() - 1) retval += ',';
	}

	return retval;
}

template<> void NodeDeclare<VarDecl>(Ast* ast, VarDecl& data)
{
	for(int t = 0; t < data.ident.size(); ++t)
	{
		ast->declareVariable(data.type, data.ident[t]);
	}
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
template<>
std::string NodeGenerateCode<FnDeclArgVarDecl>(const LangSettings& lang, FnDeclArgVarDecl& data)
{
	std::string retval;
	if(data.argType == FNAT_InOut) retval += "inout ";
	if(data.argType == FNAT_Out) retval += "out ";

	retval += data.type.GetTypeAsString(lang) + " " + data.ident;
	if(data.expr) retval += "=" + data.expr->NodeGenerateCode(lang);
	return retval;
}

template<>
void NodeDeclare(Ast* ast, FnDeclArgVarDecl& data) {
	ast->declareVariable(data.type, data.ident);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
template<>
std::string NodeGenerateCode<FuncDecl>(const LangSettings& lang, FuncDecl& data)
{
	std::string retval = data.retType.GetTypeAsString(lang) + " " + data.name + "(";

	for(int t = 0; t < data.args.size(); ++t) {
		
		retval += data.args[t]->NodeGenerateCode(lang);

		if(t < data.args.size() - 1) retval += ',';
	}

	retval += "){ " + data.stmt->NodeGenerateCode(lang) + "}";

	return retval;
}

template<>
void NodeDeclare<FuncDecl>(Ast* ast, FuncDecl& data)
{
	ast->declPushScope(data.name);

	ast->declareFunction(data.retType, data.name);

	for(auto& var : data.args) var->NodeDeclare(ast);
	data.stmt->NodeDeclare(ast);

	ast->declPopScope();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
template<>
std::string NodeGenerateCode<ProgramElem>(const LangSettings& lang, ProgramElem& data)
{
	std::string retval;

	for(const auto& node : data.nodes) {
		retval += node->NodeGenerateCode(lang);
	}

	return retval;
}

template<>
void NodeDeclare<ProgramElem>(Ast* ast, ProgramElem& data)
{
	for(auto& node : data.nodes) {
		node->NodeDeclare(ast);
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
		ast.program->NodeDeclare(&ast);
		
		for(auto n : ast.deductionQueue) n->NodeDeduceType();

		return ast.program->NodeGenerateCode(lang);
	}
	catch(const std::exception& e) {
		printf(e.what());
	}

	return std::string();
}