
#ifndef _GLOBALS_H_
	#define _GLOBALS_H_
	#include "globals.h"
#endif

#include "util.h"
#include "lex.yy.h"
#include "symtable.h"
#include "parse.h"
#include "analyze.h"
#include "code_gen.h"

/* set NO_PARSE to TRUE to get a scanner-only compiler */
#define NO_PARSE FALSE

#define ANALYZE TRUE

#define CODE_GEN TRUE

/*  allocate global variables  */
int lineno = 0;
/* 針對 while if esle 的行數計算用 */
int lineno_backtrack_stack[10];
int lineno_backtrack_stack_top = -1;

FILE *listing;
FILE *sourceCode;
FILE *symTableFile;
FILE *litTableFile;
FILE *syntaxTreeFile;
FILE *irCodeFile;

int flag_printToken      = TRUE;   /* 決定是否輸出 token scanner 運作結果 */
int flag_printSymTable   = TRUE;
int flag_printLitTable   = TRUE;
int flag_printSyntaxTree = TRUE;   /* 決定是否輸出 syntax Tree            */

int file_num;
int file_num_max;
char **files;

int error_signal = 0; /* 1: 表示有錯誤訊號,  0: 表示無錯誤訊號 */


int main ( int argc, char *argv[] ) {

	TreeNode *syntaxTree;

	listing = stdout; /*  send listing to screen  */
 	fprintf(listing, "COMPILATION INFORMATION: \n");

	file_num = 1;
	file_num_max = argc;
	files = argv;

 	#if NO_PARSE
 		if ( argc > 1 ) {
			if ( (sourceCode = fopen(argv[file_num], "r") ) == 0 ) {
				perror(argv[file_num]);
				exit(1);
			}
		}

 		while ( getToken() );

	#else
 		if ( argc > 1 ) {
			if ( (sourceCode = fopen(argv[file_num], "r") ) == 0 ) {
				perror(argv[file_num]);
				exit(1);
			}
		}

 		printf("Parse Start!!\n");

 		syntaxTree = parse();
		
 		if (flag_printSyntaxTree) {
 			syntaxTreeFile = fopen("Syntax Tree.txt", "w");
 			printSyntaxTree(syntaxTreeFile, syntaxTree);
 			fclose(syntaxTreeFile);
 		}

 		printf("Parse Ending!!\n");
 		
	#endif


 	#if ANALYZE
 		if (error_signal == 0) {
 			semantic(syntaxTree);
 		}
 		else
 			printf("Syntax Error!! \n");

 		printf("Semantic Analyze Ending!!\n");
 	#endif

 	if (flag_printSymTable) {
		symTableFile = fopen("Symbol Table.txt", "w");
		printSymTab(symTableFile);
		fclose(symTableFile);
	}
	printf("Print Symbol Table Ending!!\n");

	if (flag_printLitTable) {
		litTableFile = fopen("Literal Table.txt", "w");
		printLitTab(litTableFile);
		fclose(litTableFile);
	}
	printf("Print Literal Table Ending!!\n");

 	#if CODE_GEN
 		if (error_signal == 0) {
			irCodeFile = fopen("IR_Code.ll", "w");
			GenIR(syntaxTree, irCodeFile);
			fclose(irCodeFile);
			printf("Code Gen Ending!!\n");
		}
		else
			printf("Code Gen Error!! \n");
	#endif


	return 0;
}

