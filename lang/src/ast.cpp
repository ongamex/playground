#pragma once

#include "ast.h"

void Node::NodeDeclare(Ast* ast) {
	if(inBlock) ast->declPushScope();
	data.NodeDelcare(ast);
	if(inBlock) ast->declPopScope();
}

Ast::FullVariableDesc Ast::declareVariable(const TypeDesc& td, std::string name)
{
	FullVariableDesc fvd;
	fvd.type = td;

	for(auto s : scope) {
		fvd.fullName += s + '.';
		fvd.depth++;
	}

	fvd.fullName += name;

	declaredVariables.push_back(fvd);

	return fvd;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
template<>
std::string NodeGenerateCode<Ident>(const LangSetting& lang, Ident& data)
{
	return data.identifier;
}

//-----------------------------------------------------------------------
//
//-----------------------------------------------------------------------
template<>
std::string NodeGenerateCode<ExprBin>(const LangSetting& lang, ExprBin& data)
{
	Node* left = data.left;
	Node* right = data.right;

	switch(data.type) {
		case EBT_Add :      return left->NodeGenerateCode(lang) + (" + ") + right->NodeGenerateCode(lang);
		case EBT_Sub :      return left->NodeGenerateCode(lang) + (" - ") + right->NodeGenerateCode(lang);
		case EBT_MatMul :   return "mul(" + left->NodeGenerateCode(lang) + "," + right->NodeGenerateCode(lang) + ")"; 
		case EBT_Mul :      return left->NodeGenerateCode(lang) + (" * ") + right->NodeGenerateCode(lang);
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

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
template<>
std::string NodeGenerateCode<FuncCall>(const LangSetting& lang, FuncCall& data)
{
	std::string retval = data.fnName + '(';
	
	for(int t = 0; t < data.args.size(); ++t) {
		retval += data.args[t]->NodeGenerateCode(lang);
		if(t < data.args.size() - 1) retval += ",";
	}

	retval += ')';
	
	return retval;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
template<>
std::string NodeGenerateCode<ExprLiteral>(const LangSetting& lang, ExprLiteral& data)
{
	char buff[64] = {0};
	if(data.type == EL_Float)
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
	else if(data.type == EL_Int)
	{
		sprintf(buff, "%d", data.int_val);
		return buff;
	}

	return "???";
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
template<>
std::string NodeGenerateCode<Assign>(const LangSetting& lang, Assign& data)
{
	return data.ident + " = " + data.expr->NodeGenerateCode(lang);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
template<>
std::string NodeGenerateCode<StmtIf>(const LangSetting& lang, StmtIf& data)
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
std::string NodeGenerateCode<StmtWhile>(const LangSetting& lang, StmtWhile& data)
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
std::string NodeGenerateCode<StmtFor>(const LangSetting& lang, StmtFor& data)
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
std::string NodeGenerateCode<StmtList>(const LangSetting& lang, StmtList& data)
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
std::string NodeGenerateCode<VarDecl>(const LangSetting& lang, VarDecl& data)
{
	std::string retval = data.type.GetTypeAsString() + " ";

	for(int t = 0; t < data.ident.size(); ++t)
	{
		retval += data.ident[t];
		if(data.expr[t]) {
			retval += "=" + data.expr[t]->NodeGenerateCode(lang);
			if(t < data.ident.size() - 1) retval += ',';
		}
	}

	return retval;
}

template<> void NodeDeclare<VarDecl>(Ast* ast, VarDecl& data)
{
	for(int t = 0; t < data.ident.size(); ++t) {
		ast->declareVariable(data.type, data.ident[t]);
	}
}


//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
template<>
std::string NodeGenerateCode<FnDeclArgVarDecl>(const LangSetting& lang, FnDeclArgVarDecl& data)
{
	std::string retval;
	if(data.argType == FNAT_InOut) retval += "inout ";
	if(data.argType == FNAT_Out) retval += "out ";

	retval += data.type.GetTypeAsString() + " " + data.ident;
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
std::string NodeGenerateCode<FuncDecl>(const LangSetting& lang, FuncDecl& data)
{
	std::string retval = data.retType.GetTypeAsString() + " " + data.name + "(";

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

	for(auto& var : data.args) var->NodeDeclare(ast);
	data.stmt->NodeDeclare(ast);

	ast->declPopScope();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
template<>
std::string NodeGenerateCode<ProgramElem>(const LangSetting& lang, ProgramElem& data)
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

std::string GenerateCode(const LangSetting& lang, const char* code)
{
	Ast ast;
	LangParseExpression(code, &ast);
	ast.program->NodeDeclare(&ast);
	return ast.program->NodeGenerateCode(lang);
}