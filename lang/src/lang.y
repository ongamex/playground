%define api.pure full
%lex-param {yyscan_t scanner}
%parse-param {yyscan_t scanner}
%parse-param {Ast* ast}

%{

#include <string>
#include <cstring>
#include <math.h>
#include <map>
#include "ast.h"
#include "lang.yystype.h"

typedef void* yyscan_t;
void yyerror (yyscan_t yyscanner, char const *msg);
void yyerror (yyscan_t yyscanner, Ast* ast, char const *msg);
int yylex(YYSTYPE *yylval_param, yyscan_t yyscanner);
bool parseExpression(const std::string& inp);

%}

// Token declaration.
%token <no_type>		AND OR LE GE EQUALS NOTEQUALS
%token <no_type>		IF ELSE WHILE FOR IN OUT INOUT
%token <str_val>		IDENT CODE_STRING RETURN
%token <float_val>		NUM_FLOAT
%token <int_val>		NUM_INT
%token <no_type>		ATTRIBUTE VARYING UNIFORM NATIVE_CODE

// Token precedence.

%left AND OR
%left EQUALS NOTEQUALS
%left LE '<' GE '>'
%left '+' '-'
%left '*' '/'
%left '.'

// Grammar expression types (from yystype).
%type <node>	fncall_args expr_fncall fndecl_vardecl_var fndecl_vardecl
%type <node>	expr_base expr stmt
%type <node>	vardecl_var_list vardecl assign_stmt
%type <node>	stmt_list function_decl shader_globals
%type <node>	program grammar_elem grammar_list

// The root.
%start program

%%

program : grammar_list { ast->program = $1; $$ = $1; }

grammar_elem :
		function_decl 	{ $$ = $1; }
	|	shader_globals	{ $$ = nullptr; } // This is not a node, it just modifies the AST. 
	;

grammar_list : 

		grammar_elem  				
		{ 
			// Create a list of program elements(only functions so far).
			$$ = ast->push<ProgramElem>(); 
			
			// A program element is not necessary a node. 
			// For example vertexAttribs/varyings/uniforms they just do a add themselves
			// to a container containing all the declarations.
			if($1 != nullptr) $$->As<ProgramElem>().nodes.push_back($1); 
		}
	|	
		grammar_list grammar_elem	
		{ 
			if ($2 != nullptr) $1->As<ProgramElem>().nodes.push_back($2); 
			$$ = $1;
		}
	;
	
		
shader_globals : 
		// These aren't real nodes...
		ATTRIBUTE IDENT IDENT ':' IDENT ';'		{ $$ = nullptr; ast->vertexAttribs.push_back({TypeDesc($2), $3, $5}); }
	|	VARYING	IDENT IDENT	';'					{ $$ = nullptr; ast->varyings.push_back({TypeDesc($2), $3}); }
	|	UNIFORM	IDENT IDENT	';'					{ $$ = nullptr; ast->uniforms.push_back({TypeDesc($2), $3}); }
	;
	
	//-------------------------------------------------
	// Function Declaration.
	//-------------------------------------------------
	
	// A single variable form the function declaration.
fndecl_vardecl_var : 
		IDENT IDENT 				{ $$ = ast->push<FnDeclArgVarDecl>(TypeDesc($1), $2, nullptr, FNAT_In   ); }
	|	IDENT IDENT '=' expr		{ $$ = ast->push<FnDeclArgVarDecl>(TypeDesc($1), $2, $4     , FNAT_In   ); }
	|	IN IDENT IDENT 				{ $$ = ast->push<FnDeclArgVarDecl>(TypeDesc($2), $3, nullptr, FNAT_In	); }
	|	IN IDENT IDENT '=' expr		{ $$ = ast->push<FnDeclArgVarDecl>(TypeDesc($2), $3, $5     , FNAT_In	); }
	|	OUT IDENT IDENT 			{ $$ = ast->push<FnDeclArgVarDecl>(TypeDesc($2), $3, nullptr, FNAT_Out  ); }
	|	OUT IDENT IDENT '=' expr	{ $$ = ast->push<FnDeclArgVarDecl>(TypeDesc($2), $3, $5     , FNAT_Out  ); }
	|	INOUT IDENT IDENT 			{ $$ = ast->push<FnDeclArgVarDecl>(TypeDesc($2), $3, nullptr, FNAT_InOut); }
	|	INOUT IDENT IDENT '=' expr	{ $$ = ast->push<FnDeclArgVarDecl>(TypeDesc($2), $3, $5     , FNAT_InOut); }
	;
	
	// A list of variables for the function declaration.
	// This must be used only for function declaration variables.
	// Basically this create the function declaration node.
	// the node is later finished by function_decl rule.
fndecl_vardecl : 
												{ $$ = ast->push<FuncDecl>(); }
	|	fndecl_vardecl_var						{ $$ = ast->push<FuncDecl>(); ((FuncDecl*)$$)->args.push_back($1); }
	|	fndecl_vardecl ',' fndecl_vardecl_var	{ $1->As<FuncDecl>().args.push_back($3); $$ = $1; }

	
	// The function delectation itself.
	// fndecl_vardecl create the function call node, 
	// we need to just add the return type name and statement.
function_decl : 
	IDENT IDENT '(' fndecl_vardecl ')' '{' stmt_list '}'	{ 
		auto& funcDecl = $4->As<FuncDecl>();
		funcDecl.retType = TypeDesc($1);
		funcDecl.name = $2;
		funcDecl.stmt = $7;
		$$ = $4;
	}
	;
	
	//-------------------------------------------------
	// Variable declaration statement.
	//-------------------------------------------------
	
	// A single variable(or a variable list followed by a single variable) and the optional assigment expression
	// type var, var = expr;
vardecl_var_list : 
		IDENT 								{ $$ = ast->push<VarDecl>(TypeDesc(), $1, nullptr); }
	|	IDENT '=' expr 						{ $$ = ast->push<VarDecl>(TypeDesc(), $1, $3); }
	|	vardecl_var_list ',' IDENT 			{ 
			$1->As<VarDecl>().ident.push_back($3);
			$1->As<VarDecl>().expr.push_back(nullptr);
			$$ = $1;
		}
	|	vardecl_var_list ',' IDENT '=' expr	{ 
			$$ = $1; 
			$$->As<VarDecl>().ident.push_back($3);
			$$->As<VarDecl>().expr.push_back($5);
		}
	
	// The actual variable declaration
vardecl :
		IDENT vardecl_var_list	{ $2->As<VarDecl>().type = TypeDesc($1); $$ = $2; }
	;
	
	//-------------------------------------------------
	// Statements.
	//-------------------------------------------------
	
stmt : 
		vardecl ';'									{ $1->hasSemicolon = true; ; $$ = $1; }
	|	expr ';' 									{ $1->hasSemicolon = true; $$ = $1; }
	|	assign_stmt ';' 							{ $1->hasSemicolon = true; $$ = $1; }
	|	FOR '(' vardecl ';' expr ';' expr ')' stmt	{ $$ = ast->push<StmtFor>($3, $5, $7, $9); }
	|	WHILE '(' expr ')' stmt 					{ $$ = ast->push<StmtWhile>($3, $5); }
	|	IF '(' expr ')' stmt 						{ $$ = ast->push<StmtIf>($3, $5, nullptr); }
	|	IF '(' expr ')' stmt ELSE stmt				{ $$ = ast->push<StmtIf>($3, $5, $7); } //[SHIFT-REDUCE]
	|	'{' stmt_list '}' 							{ $2->inBlock = true; $$ = $2; }
	|	NATIVE_CODE '('  CODE_STRING  ')' ';'		{ $$ = ast->push<StmtNativeCode>($3); }
	|	RETURN expr ';'								{ $$ = ast->push<StmtReturn>($2); }
	|	RETURN ';'									{ $$ = ast->push<StmtReturn>(); }
	;

		//[TODO] This should become something like expr = expr at least because of array indexing.
assign_stmt : 
		IDENT '=' expr				{ $$ = ast->push<Assign>($1.c_str(), $3); }
	;
	
	// A list of statements.
stmt_list : 
		stmt 				{ $$ = ast->push<StmtList>(); $$->As<StmtList>().nodes.push_back($1); }
	|	stmt_list stmt 		{ 
			$$ = $1;
			$1->As<StmtList>().nodes.push_back( {$2} );
		}
	;
	
	//-------------------------------------------------
	// Expressions (like +-*/ function calls, literals ect.).
	//-------------------------------------------------

expr : expr_base { $$ = $1; ast->addDeduct($1); }
	
expr_base :
		'(' expr_base ')'			    	{ $2->inParens = true; $$ = $2; }
	|	expr_base '.' IDENT					{ $$ = ast->push<ExprMemberAccess>($1, $3); }
	|	IDENT					        	{ $$ = ast->push<Ident>($1); }
	|	expr_base OR expr_base			    { $$ = ast->push<ExprBin>(EBT_Or, $1, $3); }
	|	expr_base AND expr_base			    { $$ = ast->push<ExprBin>(EBT_And, $1, $3); }
	|	expr_base NOTEQUALS expr_base		{ $$ = ast->push<ExprBin>(EBT_NEquals, $1, $3); }
	|	expr_base EQUALS expr_base			{ $$ = ast->push<ExprBin>(EBT_Equals, $1, $3); }
	|	expr_base LE expr_base				{ $$ = ast->push<ExprBin>(EBT_LEquals, $1, $3); }
	|	expr_base '<' expr_base				{ $$ = ast->push<ExprBin>(EBT_Less, $1, $3); }
	|	expr_base GE expr_base				{ $$ = ast->push<ExprBin>(EBT_GEquals, $1, $3); }
	|	expr_base '>' expr_base				{ $$ = ast->push<ExprBin>(EBT_Greater, $1, $3); }
	|	expr_base '+' expr_base				{ $$ = ast->push<ExprBin>(EBT_Add, $1, $3); } 
	|	expr_base '-' expr_base				{ $$ = ast->push<ExprBin>(EBT_Sub, $1, $3); } 	
	|	expr_base '*' expr_base				{ $$ = ast->push<ExprBin>(EBT_Mul, $1, $3); } 
	|	expr_base '/' expr_base				{ $$ = ast->push<ExprBin>(EBT_Div, $1, $3); }
	|	NUM_FLOAT					        { $$ = ast->push<ExprLiteral>($1); }
	|	NUM_INT						        { $$ = ast->push<ExprLiteral>($1); }
	|	expr_fncall					        { $$ = $1; }	
	|	'-' expr_base						{ $2->exprSign *= -1; $$ = $2; }
	;

	
	// Function arguments as a list.
fncall_args :
			{ $$ = ast->push<FuncCall>(); }
		| 	expr_base
			{ 
				Node* fnCall = ast->push<FuncCall>();
				fnCall->As<FuncCall>().args.push_back($1); 
				$$ = fnCall;
			}
		
	|	fncall_args ',' expr_base 	{ $1->As<FuncCall>().args.push_back($3); $$ = $1; }
	
	// The function call expression itself.
expr_fncall :
		IDENT '(' fncall_args ')'	{ 
			$3->As<FuncCall>().fnName = $1;
			$$ = $3; 
		}
	;
	//--------------------------------------------
	//
	//--------------------------------------------

%%

void yyerror (yyscan_t yyscanner, char const *msg){
    fprintf(stderr, "%s\n", msg);
}

void yyerror (yyscan_t yyscanner, Ast* ast, char const *msg) {
	yyerror(yyscanner, msg);
}
