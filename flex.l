/* definition 段 */
%{
/* 複製到 .C 檔裡, 故語法同C */
#include <stdio.h>

#ifndef _GLOBALS_H_
#define _GLOBALS_H_
#include "globals.h"
#endif

#include "lex.yy.h"
#include "yacc.tab.h"
#include "symtable.h"

extern int file_num;
extern int file_num_max;
extern char **files;

void printTokenCodeName(int enable, char *codeName) {
	if (enable) {
		fprintf(yyout, "%12s : ", codeName);
	}
}

%}

/* %option noyywrap */

/* 下列宣告一些「rule的變數」，讓rule的寫法更簡潔 */

DIGIT           [0-9] 
LETTER          [a-zA-Z]
NUMBER          [0-9]+
WHITESPACE      [ \t\r]+

/* 同 identifier  [a-zA-Z][a-zA-Z0-9]*     */
ID              [a-zA-Z]([a-zA-Z]|[0-9])*

/* 注意: 此處並未處理 escape char 符號，待解決 */
STRING_CONST    \"([a-zA-Z]|[0-9]|[ \t\r]|\+|-|\*|\/|%|=|==|,|;|!=|>=|<=|!|\[|\]|@|#|$|^|&|_|\?|:|~|.)+\"
CHAR_CONST      \'([a-zA-Z]|[0-9]|[ \t\r]|\+|-|\*|\/|%|=|==|,|;|!=|>=|<=|!|\[|\]|@|#|$|^|&|_|\?|:|~|.)\'

/* rules段 注意前後分段符號 */
/* 下面並未處理註解部分     */
%%

bool              { printTokenCodeName(flag_printToken, "BOOL_DECLAR");   ECHO; return BOOL_DECLAR;  } 
char              { printTokenCodeName(flag_printToken, "CHAR_DECLAR");   ECHO; return CHAR_DECLAR;  } 
const             { printTokenCodeName(flag_printToken, "CONST_DECLAR");  ECHO; return CONST_DECLAR; } 
string            { printTokenCodeName(flag_printToken, "STR_DECLAR");    ECHO; return STR_DECLAR;   } 
int               { printTokenCodeName(flag_printToken, "INT_DECLAR");    ECHO; return INT_DECLAR;   }

if                { lineno_backtrack_stack[lineno_backtrack_stack_top + 1] = lineno;
					lineno_backtrack_stack_top += 1;
					printTokenCodeName(flag_printToken, "IF");            ECHO; return IF;           } 
else              { lineno_backtrack_stack[lineno_backtrack_stack_top + 1] = lineno;
					lineno_backtrack_stack_top += 1;
					printTokenCodeName(flag_printToken, "ELSE");          ECHO; return ELSE;         } 
while             { lineno_backtrack_stack[lineno_backtrack_stack_top + 1] = lineno;
					lineno_backtrack_stack_top += 1;
					printTokenCodeName(flag_printToken, "WHILE");         ECHO; return WHILE;        } 

read              { printTokenCodeName(flag_printToken, "READ");          ECHO; return READ;         } 
print             { printTokenCodeName(flag_printToken, "PRINT");         ECHO; return PRINT;        } 
println           { printTokenCodeName(flag_printToken, "PRINTLN");       ECHO; return PRINTLN;      } 
main              { printTokenCodeName(flag_printToken, "MAIN");          ECHO; return MAIN;         } 
TRUE              { printTokenCodeName(flag_printToken, "TRUE_TOKEN");    ECHO; return TRUE_TOKEN;   } 
FALSE             { printTokenCodeName(flag_printToken, "FALSE_TOKEN");   ECHO; return FALSE_TOKEN;  } 


{NUMBER}          { printTokenCodeName(flag_printToken, "NUMBER");        ECHO; return NUMBER;       } 
{ID}              { printTokenCodeName(flag_printToken, "ID");            ECHO; return ID;           } 


{WHITESPACE}      /* ignore */
{STRING_CONST}    { printTokenCodeName(flag_printToken, "STRING_CONST");  ECHO; return STRING_CONST; }   
{CHAR_CONST}      { printTokenCodeName(flag_printToken, "CHAR_CONST");    ECHO; return CHAR_CONST;   }    
\n                { lineno++; }


"="               { printTokenCodeName(flag_printToken, "ASSIGN");        ECHO; return ASSIGN;       } 
"+"               { printTokenCodeName(flag_printToken, "ADD");           ECHO; return ADD;          } 
"-"               { printTokenCodeName(flag_printToken, "SUB");           ECHO; return SUB;          } 
"*"               { printTokenCodeName(flag_printToken, "MUL");           ECHO; return MUL;          } 
"/"               { printTokenCodeName(flag_printToken, "DIV");           ECHO; return DIV;          } 
"%"               { printTokenCodeName(flag_printToken, "MOD");           ECHO; return MOD;          } 
">"               { printTokenCodeName(flag_printToken, "GR");            ECHO; return GR;           } 
"<"               { printTokenCodeName(flag_printToken, "LS");            ECHO; return LS;           }  /* 考慮 lex 只執行對當前輸入的最長可能作匹配 */
"=="              { printTokenCodeName(flag_printToken, "EQ");            ECHO; return EQ;           } 
"!="              { printTokenCodeName(flag_printToken, "NOT_EQ");        ECHO; return NOT_EQ;       } 
">="              { printTokenCodeName(flag_printToken, "GR_EQ");         ECHO; return GR_EQ;        } 
"<="              { printTokenCodeName(flag_printToken, "LS_EQ");         ECHO; return LS_EQ;        } 

","               { printTokenCodeName(flag_printToken, "COMMA");         ECHO; return COMMA;        }  
";"               { printTokenCodeName(flag_printToken, "SEMICOLON");     ECHO; return SEMICOLON;    } 
"\{"              { printTokenCodeName(flag_printToken, "L_BRACE");       ECHO; return L_BRACE;      }  
"\}"              { printTokenCodeName(flag_printToken, "R_BRACE");       ECHO; return R_BRACE;      } 
"\("              { printTokenCodeName(flag_printToken, "L_PARENTH");     ECHO; return L_PARENTH;    }                                                                                                 
"\)"              { printTokenCodeName(flag_printToken, "R_PARENTH");     ECHO; return R_PARENTH;    } 

"/*"              { 	int c1 = 0, c2 = input();
						for(;;) {
							if(c2 == EOF)
								break;
							if(c1 == '*' && c2 == '/') {
								
								break;
							}
							if(c2 == '\n') {
								lineno++;
							}
							c1 = c2;
							c2 = input();
						}
				  }
"//"			  {		int c1 = 0, c2 = input();
						for(;;) {
							if(c2 == EOF)
								break;
							if(c2 == '\n') {
								lineno++;
								break;
							}
							c1 = c2;
							c2 = input();
						}
				  }

%%

TokenType getToken(void) {
	static int firstTime = TRUE;
  	TokenType currentToken;

  	if (firstTime) {
  		firstTime = FALSE;
  		lineno++;
  		yyin = sourceCode;
  		if (flag_printToken)
  			yyout = fopen("yyout.txt", "w"); /* 設定輸出、儲存 token 的檔案 */
  		fprintf(yyout, "    Type     |    content            \n");
  		fprintf(yyout, "-------------+-----------------------\n");
  	}
  	
  	currentToken = yylex();
  	strncpy(tokenString, yytext, MAXTOKENLEN);

  	/* 輸出當下 scan 辨識的 token */
  	if (flag_printToken) {
    	fprintf(yyout, "\n");
  	}

  	if (currentToken == ID) {
  		symtab_Mgmt(tokenString);
  	}
  	else if (currentToken == CHAR_CONST) {
  		littab_Mgmt(tokenString, Character);
  	}
  	else if (currentToken == STRING_CONST) {
  		littab_Mgmt(tokenString, String);
  	}

  	printf("%s\n", tokenString);
  	if (currentToken == 0) {
  		fclose(yyout);
  		printf("Scan => EOF!!\n");
  	}
  	return currentToken;
}

int yywrap() {
	fclose(yyin);
	if ( ++file_num < file_num_max ) {
		if ( (sourceCode = fopen(files[file_num],"r")) == 0 ) {
			perror(files[file_num]);
			exit(1);
		}
		return 0;
	} 
	else {
		return 1;
	}
}

/*
int main(int argc, char *argv[]) {
	file_num = 1;
	file_num_max = argc;
	files = argv;
	if ( argc > 1 ) {
		if ( (yyin = fopen(argv[file_num], "r")) == 0 ) {
			perror(argv[file_num]);
			exit(1);
		}
	}
	yyout = fopen("yyout.txt","w"); // 自行加入 
	while( yylex() );
	return 0;
}
*/


