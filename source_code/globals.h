#ifndef GLOBALS_H
#define GLOBALS_H
#endif

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#ifndef FALSE
	#define FALSE 0
#endif

#ifndef TRUE
	#define TRUE 1
#endif

/*  MAXTOKENLEN is the maximum size of a token  */
#define MAXTOKENLEN 60
#define MAXCHILDREN 3


extern FILE *listing;        /*  listing output text file           */
extern FILE *sourceCode;     /*  source code text file              */
//extern FILE *scanOutput;   /*  yyout output token list file       */
//extern FILE *code;         

extern int error_signal;  

extern int lineno;           /*  source line number for listing     */
/*  to put source line number for backtracking WhileK/IfK/ElseK     */
extern int lineno_backtrack_stack[10];        
extern int lineno_backtrack_stack_top;

extern int flag_printToken;  /* 決定是否輸出 token scanner 運作結果 */

extern char tokenString[MAXTOKENLEN+1];

typedef int TokenType;

/*
typedef enum{ 	TEOF, UNKNOWN, NUMBER, NORMAL_CHAR, ESCAPE_CHAR, STRING, ID, TRUE_TOKEN, FALSE_TOKEN,
				ASSIGN, ADD, SUB, MUL, DIV, MOD, EQ, GR, LS, NOT_EQ, GR_EQ, LS_EQ,
				ADD_ASSIGN, SUB_ASSIGN, MUL_ASSIGN, DIV_ASSIGN, MOD_ASSIGN, 
				L_PARENTH, R_PARENTH, L_BRACE, R_BRACE, COMMA, SEMICOLON, NEG, WHITE_SPACE,
				MAIN, IF, ELSE, WHILE, READ, PRINT, PRINTLN,
				BOOL_DECLAR, CHAR_DECLAR, CONST_DECLAR, STR_DECLAR, INT_DECLAR,
				CHAR_CONST, STRING_CONST
			} TokenType;*/

/* 請搜尋 compiler statements 與 expressions 的分別  */
/* 了解為何如此定義                                  */
typedef enum {StmtK, ExpK} NodeKind;                                    
typedef enum {IfK, ElseK, WhileK, AssignK, ReadK, PrintK, PrintlnK, Type_dclK, Const_dclK, MainK, PgbdK} StmtKind;
/* Type_dclK, Const_dclK, MainK, PgbdK 是ㄧ種語句，本身不帶值，個人設計為屬於stmt，
 * compoundK 改成 compound_opdK，避免跟compound_stmt 類型搞混，opd 表示 operand    
 */    
typedef enum {OpK, NumK, IdK, CharStr_constK, Compound_opdK, BoolK} ExpKind;
/* 因為老師在 literal 句法規則定義中的描述為 STRING_CONST、CHAR_CONST  */
/* 因此，命名為 CharStr_constK ，原本想設定為 CharK、StrK 應該也可行   */

/*  ExpType is used for type checking  */
typedef enum {Void, Boolean, Character, String, Integer} ExpType;


typedef struct treeNode {

	struct treeNode *child[MAXCHILDREN];
	struct treeNode *sibling;
	int lineno;
	NodeKind nodekind;

	union
	{
		StmtKind stmt;
		ExpKind exp;
	} kind;
	union
	{
		TokenType op;                                
		int val;
		int bool_Value;
		char *name;
		char *dcl;
		char *char_str_item;  
	} attr;
	ExpType type;    /*  for type checking of exps     */

	/*  for const attribute checking  */
	/*  1 = const, 0 = non-const      */
	int const_attr_tag;  

} TreeNode;


