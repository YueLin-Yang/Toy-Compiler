
%{

#define YYPARSER /* distinguishes Yacc output from other code files */

#ifndef _GLOBALS_H_
	#define _GLOBALS_H_
	#include "globals.h"
#endif

#include <stdlib.h>
#include "lex.yy.h"
#include "parse.h"
#include "util.h"

#define YYSTYPE TreeNode *

static char *savedName;      /* for use in assignments */
static int savedLineNo;      /* for use in assignments */
static TreeNode *savedTree;  /* stores syntax tree for later return */

int yyerror(char * message);
static int yylex(void);

%}

/*  下方此定義會在 yacc.tab.h(預設檔名) 產生訊息程式碼           */
/*  記得 biosn -d yacc.y 的 "-d" 參數，才會產生 yacc.tab.h       */
/*  ex. #define INTEGER 257                                      */
/*  註: 0-255 之間的標記值約定為字符值，為系統保留的後定義 token */
/*  越下方優先權越高，若有 left 或 right 表示左結合或右結合      */
%token MAIN WHILE IF ELSE
%token READ PRINT PRINTLN TRUE_TOKEN FALSE_TOKEN SEMICOLON COMMA
%token BOOL_DECLAR CHAR_DECLAR CONST_DECLAR STR_DECLAR INT_DECLAR 
%token ID NUMBER STRING_CONST CHAR_CONST ASSIGN ADD SUB MUL DIV MOD GR LS EQ NOT_EQ GR_EQ LS_EQ
%token L_BRACE R_BRACE L_PARENTH R_PARENTH                                                              


%%   /* Grammar for Vanilla-C */

PROGRAM				: 	prog_hdr prog_body
	                       	{
	                       		YYSTYPE t = $2;
	                       		if (t != NULL) {
	                       			$1->sibling = $2;
	                       			savedTree = $1;
	                       		}
	                       		else { savedTree = $1; }
	                       	}
                    ;

prog_hdr            : 	MAIN L_PARENTH R_PARENTH	
							{
								$$ = newStmtNode(MainK);
								$$->attr.name = copyString(tokenString);
							}
					;

prog_body           : 	L_BRACE dcl_list stmt_list R_BRACE
							{
								$$ = newStmtNode(PgbdK);
								$$->child[0] = $2;
								$$->child[1] = $3;
							}
					;


/*                     gnu.org bison mannul                                 */
/* Any kind of sequence can be defined using either left recursion or 
   right recursion, but you should always use left recursion, because 
   it can parse a sequence of any number of elements with bounded stack 
   space. Right recursion uses up space on the Bison stack in proportion 
   to the number of elements in the sequence, because all the elements 
   must be shifted onto the stack before the rule can be applied even once. */
/*
dcl_list            : 	dcl_list dcl_stmt                                              // 左 or 右結合的差異問題 
							{
								YYSTYPE t = $2;
								if (t != NULL) {
									while (t->sibling != NULL)
										t = t->sibling;
									t->sibling = $1;
									$$ = $2;
								}
								else { $$ = $1; }
							}
					| 	{ $$ = NULL; }                                                 // empty，可查 bison 的 ε 用法          
					;															       // 若有需要, $0 表示 dcl_list 的前一個 token 
*/

dcl_list            : 	dcl_list dcl_stmt                                              // 左 or 右結合的差異問題 
							{
								YYSTYPE t = $1;
								if (t != NULL) {
									while (t->sibling != NULL)
										t = t->sibling;
									t->sibling = $2;
									$$ = $1;
								}
								else { $$ = $2; }
							}
					| 	/* empty */ { $$ = NULL; }                                                        
					;										

dcl_stmt            : 	const_dcl  { $$ = $1; }
					| 	var_dcl    { $$ = $1; }
					;

const_dcl           : 	CONST_DECLAR const_list SEMICOLON                                /* Type 宣告型態起始 EX. CONST a, b, c, ... ; */
							{
								$$ = newStmtNode(Const_dclK);
								$$->attr.dcl = "const";
								$$->child[0] = $2;
							}
					;

const_list          : 	const_list COMMA const_stmt                                      /* 參考 TINY.Y  stmt_seq    : stmt_seq SEMI stmt */
							{                                                            
								YYSTYPE t = $1;                     
		                    	while (t->sibling != NULL)
		                        	t = t->sibling;
		                     	t->sibling = $3;
		                     	$$ = $1; 
							}
					| 	const_stmt { $$ = $1; }
					;


/*     Bison only looks ahead 1 token to decide which production to apply.      */ 
/*     Your two productions for statement both have code blocks before the      */
/*     parser has read any tokens to know which production is going to apply.   */
/*     以下寫法會導致 reduce/reduce conflicts => waring: rule useless in        */
/*     parser due to conflicts                                                  */     
/*
const_stmt          : 	ID 	{	savedName = copyString(tokenString);                     
								savedLineNo = lineno; } 
						ASSIGN ID
							{
								$$ = newStmtNode(AssignK);

								$$->child[0] = newExpNode(IdK);
								$$->child[0]->attr.name = savedName;
								$$->child[0]->lineno = savedLineNo;

								$$->child[1] = newExpNode(IdK);
								$$->child[1]->attr.name = copyString(tokenString);	      
							}
					| 	ID 	{	savedName = copyString(tokenString);                      
								savedLineNo = lineno; }
						ASSIGN literal
							{
								$$ = newStmtNode(AssignK);

								$$->child[0] = newExpNode(IdK);
								$$->child[0]->attr.name = savedName;
								$$->child[0]->lineno = savedLineNo;

								$$->child[1] = $4;
							}
					;  
*/

const_stmt          : 	id_assign ID
							{
								$1->child[1] = newExpNode(IdK);
								$1->child[1]->attr.name = copyString(tokenString);
								$$ = $1;	      
							}
					| 	id_assign literal
							{
								$1->child[1] = $2;
								$$ = $1;
							}
					|	id_assign number
							{
								$1->child[1] = $2;
								$$ = $1;
							}
					;  

/*   在 parse下一個token前, 將當前token暫存       */
/*   $1=ID, $2={rule action}, $3=ASSIGN, $4=ID    */
id_assign 			:	ID 	{	savedName = copyString(tokenString);                     
								savedLineNo = lineno; } 
						ASSIGN 
							{
								$$ = newStmtNode(AssignK);
								$$->child[0] = newExpNode(IdK);
								$$->child[0]->attr.name = savedName;
								$$->child[0]->lineno = savedLineNo;

								/* 注意: 此處對宣告為 const 屬性的 ID 下標記 */  
								/* 改至 analyze.c 設定 (認為屬語意分析相關)  */ 
								/* $$->child[0]->const_attr_tag = 1;         */             
							}
					;

literal             : 	STRING_CONST
							{
								$$ = newExpNode(CharStr_constK);
								$$->attr.char_str_item = copyString(tokenString);
							}
					| 	CHAR_CONST
							{
								$$ = newExpNode(CharStr_constK);
								$$->attr.char_str_item = copyString(tokenString);
							}
					| 	TRUE_TOKEN                                                      /* BOOL_VAL => TRUE or FALSE */
							{
								$$ = newExpNode(BoolK);
								$$->attr.bool_Value = 1;
							}
					|	FALSE_TOKEN                                                     /* BOOL_VAL => TRUE or FALSE */
							{
								$$ = newExpNode(BoolK);
								$$->attr.bool_Value = 0;
							}
					;

var_dcl             : 	data_type id_list SEMICOLON
							{
								$1->child[0] = $2;
								$$ = $1;
							}
					;

data_type           : 	INT_DECLAR
							{
								$$ = newStmtNode(Type_dclK);
								$$->attr.dcl = copyString(tokenString);
							}
					| 	CHAR_DECLAR
							{
								$$ = newStmtNode(Type_dclK);
								$$->attr.dcl = copyString(tokenString);
							}
					| 	BOOL_DECLAR
							{
								$$ = newStmtNode(Type_dclK);
								$$->attr.dcl = copyString(tokenString);
							}
					| 	STR_DECLAR
							{
								$$ = newStmtNode(Type_dclK);
								$$->attr.dcl = copyString(tokenString);
							}
					;

id_list             : 	id_list COMMA ID
							{
								YYSTYPE t = $1;
		                    	while (t->sibling != NULL)
		                        	t = t->sibling;
		                     	t->sibling = newExpNode(IdK);
		                     	t->sibling->attr.name = copyString(tokenString);
		                     	$$ = $1; 
							}
					| 	ID
							{
								$$ = newExpNode(IdK);
	                   			$$->attr.name = copyString(tokenString);
							}
					;

stmt_list           : 	stmt_list stmt
							{
								YYSTYPE t = $1;
			                    if (t != NULL) { 
			                    	while (t->sibling != NULL)
			                    		t = t->sibling;
			                    	t->sibling = $2;
			                     	$$ = $1; 
			                    }
			                    else $$ = $2;
							} 
					| 	/* empty */ { $$ = NULL; }                                        
					;

stmt                : 	assignment_stmt { $$ = $1; }
					| 	compound_stmt   { $$ = $1; }
					| 	selection_stmt  { $$ = $1; }
					| 	iteration_stmt  { $$ = $1; }
					| 	io_stmt         { $$ = $1; }
					| 	null_stmt       { $$ = $1; }
					;


/* $1=ID, $2={rule action}, $3=ASSIGN, $4=simple_expr, $5=SEMICOLON */
/* 因加入 id_assign 規則，本段程式碼不使用，僅供參考
assignment_stmt     : 	ID 	{	savedName = copyString(tokenString);
								savedLineNo = lineno; }
						ASSIGN simple_expr SEMICOLON
							{
								$$ = newStmtNode(AssignK);
								$$->child[0] = newExpNode(IdK);
								$$->child[0]->attr.name = savedName;
								$$->child[0]->lineno = savedLineNo;
								$$->child[1] = $4;                            
							}
					;
*/ 

assignment_stmt     : 	id_assign simple_expr SEMICOLON
							{
								$1->child[1] = $2;
								$$ = $1;                            
							}
					;


/* 此 compound_stmt 與 Compound_opdK 欲表示的複合變數無關 */
compound_stmt       : 	L_BRACE stmt_list R_BRACE { $$ = $2; }
                    ;


/* 下列用法會導致 if part stmt 與 else part stmt 並列，造成後續的困擾
 * ( 如: print syntax tree 的判讀困難 )
 * 因此改用 else_stmt 取代 ELSE + stmt 的方案
selection_stmt      : 	IF L_PARENTH simple_expr R_PARENTH stmt
							{
								$$ = newStmtNode(IfK);
								$$->child[0] = $3;
								$$->child[1] = $5;
							}
					| 	IF L_PARENTH simple_expr R_PARENTH stmt ELSE stmt
							{
								$$ = newStmtNode(IfK);
								$$->child[0] = $3;
								$$->child[1] = $5;
								$$->child[2] = $7;
							}
					;
*/

selection_stmt      : 	IF L_PARENTH simple_expr R_PARENTH stmt
							{
								$$ = newStmtNode(IfK);
								$$->child[0] = $3;
								$$->child[1] = $5;
							}
					| 	IF L_PARENTH simple_expr R_PARENTH stmt else_stmt
							{
								$$ = newStmtNode(IfK);
								$$->child[0] = $3;
								$$->child[1] = $5;
								$$->child[2] = $6;
							}
					;

else_stmt			:	ELSE stmt
							{
								$$ = newStmtNode(ElseK);
								$$->child[0] = $2;
							}
					;

iteration_stmt      : 	WHILE L_PARENTH simple_expr R_PARENTH stmt
							{
								$$ = newStmtNode(WhileK);
								$$->child[0] = $3;
	                   			$$->child[1] = $5;
							}
					;

io_stmt             : 	READ L_PARENTH id_list R_PARENTH SEMICOLON
							{
								$$ = newStmtNode(ReadK);
								$$->child[0] = $3;
							}
					| 	PRINT L_PARENTH simple_expr R_PARENTH SEMICOLON
							{
								$$ = newStmtNode(PrintK);
								$$->child[0] = $3;
							}
					| 	PRINT L_PARENTH literal R_PARENTH SEMICOLON
							{
								$$ = newStmtNode(PrintK);
								$$->child[0] = $3;
							}
					|	PRINT L_PARENTH number R_PARENTH SEMICOLON                  /* 應對 number獨立於 literal的額外處理 */
							{
								$$ = newStmtNode(PrintK);
								$$->child[0] = $3;
							}
					| 	PRINTLN L_PARENTH simple_expr R_PARENTH SEMICOLON 
							{
								$$ = newStmtNode(PrintlnK);
								$$->child[0] = $3;
							}
					| 	PRINTLN L_PARENTH literal R_PARENTH SEMICOLON
							{
								$$ = newStmtNode(PrintlnK);
								$$->child[0] = $3;
							}
					|	PRINTLN L_PARENTH number R_PARENTH SEMICOLON                /* 應對 number獨立於 literal的額外處理 */
							{
								$$ = newStmtNode(PrintlnK);
								$$->child[0] = $3;
							}
					;

null_stmt			: 	SEMICOLON { $$ = NULL; }
					;

simple_expr			: 	additive_expr LS_EQ additive_expr
							{
								$$ = newExpNode(OpK);
	                   			$$->child[0] = $1;
	                   			$$->child[1] = $3;
	                   			$$->attr.op = LS_EQ;
							}
					| 	additive_expr LS additive_expr
							{
								$$ = newExpNode(OpK);
	                   			$$->child[0] = $1;
	                   			$$->child[1] = $3;
	                   			$$->attr.op = LS;
							}
					| 	additive_expr GR additive_expr
							{
								$$ = newExpNode(OpK);
	                   			$$->child[0] = $1;
	                   			$$->child[1] = $3;
	                   			$$->attr.op = GR;
							}
					| 	additive_expr GR_EQ additive_expr
							{
								$$ = newExpNode(OpK);
	                   			$$->child[0] = $1;
	                   			$$->child[1] = $3;
	                   			$$->attr.op = GR_EQ;
							}
					| 	additive_expr EQ additive_expr
							{
								$$ = newExpNode(OpK);
	                   			$$->child[0] = $1;
	                   			$$->child[1] = $3;
	                   			$$->attr.op = EQ;
							}
					| 	additive_expr NOT_EQ additive_expr
							{
								$$ = newExpNode(OpK);
	                   			$$->child[0] = $1;
	                   			$$->child[1] = $3;
	                   			$$->attr.op = NOT_EQ;
							}
					| 	additive_expr { $$ = $1; }
					;

additive_expr		: 	additive_expr ADD term
							{
								$$ = newExpNode(OpK);
								$$->child[0] = $1;
	                   			$$->child[1] = $3;
	                   			$$->attr.op = ADD;
							}
					| 	additive_expr SUB term
							{
								$$ = newExpNode(OpK);
								$$->child[0] = $1;
	                   			$$->child[1] = $3;
	                   			$$->attr.op = SUB;
							}
					| 	term { $$ = $1; }
					;

term				: 	term MUL factor
							{
								$$ = newExpNode(OpK);
	                   			$$->child[0] = $1;
	                   			$$->child[1] = $3;
	                   			$$->attr.op = MUL;
							}
					| 	term DIV factor
							{
								$$ = newExpNode(OpK);
	                   			$$->child[0] = $1;
	                   			$$->child[1] = $3;
	                   			$$->attr.op = DIV;
							}
					| 	term MOD factor 
							{
								$$ = newExpNode(OpK);
	                   			$$->child[0] = $1;
	                   			$$->child[1] = $3;
	                   			$$->attr.op = MOD;
							}
					| 	factor { $$ = $1; }
					;


/*        為解決 reduce/reduce conflict               */
/*        老師講義原定義之 factor -> (+|-|ε)NUMBER    */
/*        修改成 NUMBER = (+|-|ε)NUM_VAL              */
/*        FACTOR 定義一次 ( + | - | ε ) NUMBER        */
/*        LITERAL 又重複定義 ( + | - | ε ) NUMBER     */  

factor				: 	L_PARENTH simple_expr R_PARENTH { $$ = $2; }
					| 	ADD ID 
							{
								$$ = newExpNode(Compound_opdK);

								$$->child[0] = newExpNode(OpK);
								$$->child[0]->attr.op = ADD;

								$$->child[1] = newExpNode(IdK);
								$$->child[1]->attr.name = copyString(tokenString); 
							}
					| 	SUB ID
							{
								
								$$ = newExpNode(Compound_opdK);

								$$->child[0] = newExpNode(OpK);
								$$->child[0]->attr.op = SUB;

								$$->child[1] = newExpNode(IdK);
								$$->child[1]->attr.name = copyString(tokenString); 
							
							}
					| 	/* empty */ ID    
							{
								$$ = newExpNode(IdK);
	                   			$$->attr.name = copyString(tokenString);                 /* 注意 tokenString 傳遞 */
							} 
					|	number { $$ = $1; }                                                                            
					;

/*        為解決 reduce/reduce conflict               */
/*        老師講義原定義之 factor -> (+|-|ε)NUMBER    */
/*        修改成 NUMBER = (+|-|ε)NUM_VAL              */
/*        並將之從 literal & factor 獨立出來          */ 
number 				:	ADD NUMBER
							{
								$$ = newExpNode(Compound_opdK);

								$$->child[0] = newExpNode(OpK);
								$$->child[0]->attr.op = ADD;

								$$->child[1] = newExpNode(NumK);
								$$->child[1]->attr.val = atoi(tokenString);
							}
					| 	SUB NUMBER
							{
								$$ = newExpNode(Compound_opdK);

								$$->child[0] = newExpNode(OpK);
								$$->child[0]->attr.op = SUB;

								$$->child[1] = newExpNode(NumK);
								$$->child[1]->attr.val = atoi(tokenString);
							}
					| 	/* empty */ NUMBER
							{
								$$ = newExpNode(NumK);
								$$->attr.val = atoi(tokenString);                     /* 注意 tokenString 傳遞 */
							}
					;

%%


/* Reference COMPILER CONSTRUCTION 	Principles and Practice - Kenneth C. Louden */
int yyerror(char * message)
{ 
	fprintf(listing, "Syntax error at line %d: %s\n", lineno, message);
  	fprintf(listing, "Current token: ");
  	/* printToken(yychar, tokenString); 代處理 */ 
  	error_signal = 1;
  	printf("Yacc - Syntax error at line %d: %s\n", lineno, message);                           
  	return 0;
}


/* yylex calls getToken to make Yacc/Bison output
 * compatible with ealier versions of the TINY scanner
 */
static int yylex(void)
{ 
	printf("Yacc - Parsing to line : %d \n", lineno);
	return getToken(); 
}                                                   


TreeNode *parse(void)
{ 
	yyparse();
  	return savedTree;
}

