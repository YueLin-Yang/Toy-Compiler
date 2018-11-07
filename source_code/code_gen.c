#include "code_gen.h"
#include "symtable.h"
#include "util.h"
#include "yacc.tab.h"

FILE *printFile;

LitTabList *save_LitTab_collection; // 初始化在 printGlobVar_of_LitData(){...}

static char *instr_Indent = "\t";

static int reg_no;
static int ret_reg;    // 儲存要返回的 SSA reg 變數
static int ret_NumK;   // 返回 NumK 節點的數字值
static char *ret_bool_val; // 返回 BoolK 節點的布林值

int isNumK_flag;    // flag = 1 表示為數值，用於 CompooundK
int sign_neg_flag;  // flag = 1 表示，用於 CompoundK 
int leftChild_flag; //對左子節點操作 flag = 1

int const_dcl_flag; // 1: 表示為宣告狀態中,  0: 不在宣告狀態, 以 syntaxTree 來看，狀態中意思為 dclK 子節點
int type_dcl_flag;  // 非 0: 表示為宣告狀態中,  0: 不在宣告狀態, 以 syntaxTree 來看，狀態中意思為 dclK 子節點
int sign_opt_flag;  // 1: 表示作[正/負]符號,  0: 表示作[ADD/SUB]符號, 由 CompoundK 去設定 

int assign_L_opd_flag; // 搭配 ret_IdK_name 用
static char *ret_IdK_name; // AssignK 需要 IdK 的名字，來將右側存放至 %id_name 變數，而非 SSA reg 編號變數

int isCharStr_constK_flag;
static int ret_CharStr_length;
/*	存 CharStr_constK 的配對全域常數變數編號
	Example:
		若  ret_CharStr_varNo = 5
		則  char/String 的 literal 全域變數應為  @.literal.5
 */
static int ret_CharStr_varNo; 

static void cGen(TreeNode *tree);

static void genStmt(TreeNode *t)
{
	TreeNode *p0, *p1, *p2;

	switch (t->kind.stmt)
	{
		case IfK: {
			int cond;
			p0 = t->child[0]; /* test exp  */
			p1 = t->child[1]; /* if stmt   */
			p2 = t->child[2]; /* else stmt */
	    
			/* test expression */
			cGen(p0);
			cond = ret_reg;
			// br i1 <cond>, label <iftrue>, label <iffalse>
			// br i1 %cond, label %true_then, label %false_else
			if (p2 != NULL) { // 有 else
				fprintf(printFile, "%sbr i1 %c%d, label %cif.then.%d, label %cif.else.%d \n", instr_Indent, '%', cond, '%', cond, '%', cond);
				fprintf(printFile, "\n");
			}
			else { // 只有 if stmt，沒有 else stmt
				fprintf(printFile, "%sbr i1 %c%d, label %cif.then.%d, label %cif.end.%d \n", instr_Indent, '%', cond, '%', cond, '%', cond);
				fprintf(printFile, "\n");
			}

			/* if body */
			fprintf(printFile, "if.then.%d: \n", cond); // then label
			cGen(p1);
			fprintf(printFile, "%sbr label %cif.end.%d \n", instr_Indent, '%', cond);
			fprintf(printFile, "\n");

			if (p2 != NULL) {
				/* ElseK */
				fprintf(printFile, "if.else.%d: \n", cond); // else label
				cGen(p2);
				fprintf(printFile, "%sbr label %cif.end.%d \n", instr_Indent, '%', cond);
				fprintf(printFile, "\n");
			}

			/* end if */
			fprintf(printFile, "if.end.%d: \n", cond); // end if label
			break;
		}

		case ElseK:
			p0 = t->child[0]; /* else body */
			cGen(p0);
			break;

		case WhileK: {
			int record, test_ret; 
			record = ret_reg; // 記錄當前 SSA reg 的編號
			p0 = t->child[0]; /* test exp     */
			p1 = t->child[1]; /* while body   */

			fprintf(printFile, "%sbr label %cwhile.test%d \n", instr_Indent, '%', record); 
			fprintf(printFile, "\n");

			/* test expression */
			fprintf(printFile, "while.test%d: \n", record); // test label
			cGen(p0);
			test_ret = ret_reg;
			// br i1 %cond, label %true_in_body, label %flase_out_body
			fprintf(printFile, "%sbr i1 %c%d, label %cwhile.body%d, label %cwhile.out%d \n", instr_Indent, '%', test_ret, '%', record, '%', record);
			fprintf(printFile, "\n");

			/* while body */
			fprintf(printFile, "while.body%d: \n", record); // body label
			cGen(p1);
			// back to test expression
			fprintf(printFile, "%sbr label %cwhile.test%d \n", instr_Indent, '%', record);
			fprintf(printFile, "\n");

			/* while out */
			fprintf(printFile, "while.out%d: \n", record); // while out label
			break;
		}

		case AssignK: {
			char *target_id;
			int save_right_reg_no;
			
			p0 = t->child[0];
			p1 = t->child[1]; /* assign 右側運算可遞迴下去 */
			
			/* left opd */
			assign_L_opd_flag = 1;
			cGen(p0); // Assign 符號左邊一定是 ID 
			target_id = ret_IdK_name;

			/* right opd */
			cGen(p1);
			if (const_dcl_flag == 1) {
				switch (p1->type)
				{
					// CONST_STMT -> ID = LITERAL ; LITERAL -> ( + | - | ε ) NUMBER 
					case Integer:
						{
							// %a = alloca i32, align 4
							fprintf(printFile, "%s%c%s = alloca i32, align 4 \n", instr_Indent, '%', target_id);
							// number, ex. const x = 2 
							if (p1->kind.exp == NumK) { // NumK
								// store i32 number_value, i32* %be_assigned_id, align 4
								fprintf(printFile, "%sstore i32 %d, i32* %c%s, align 4 \n", instr_Indent, ret_NumK, '%', target_id);
								isNumK_flag = 0;
							}
							// CompoundK number, ex. const x = -2 
							else if ( (p1->kind.exp == Compound_opdK) && (p1->child[1]->kind.exp == NumK) ) { 
								fprintf(printFile, "%sstore i32 %c%d, i32* %c%s, align 4 \n", instr_Indent, '%', ret_reg, '%', target_id);
							}
							// CONST_STMT -> ID = ID, 其中右側 ID type 為 Integer
							else if (p1->kind.exp == IdK) {
								// store i32 %7, i32* %k, align 4
								fprintf(printFile, "%sstore i32 %c%d, i32* %c%s, align 4 \n", instr_Indent, '%', ret_reg, '%', target_id);
							}
						}
						break;
					// CONST_STMT -> ID = LITERAL ; LITERAL -> BOOL_VAL
					case Boolean:
						{
							if (p1->kind.exp == BoolK) {  // ex. const x = TRUE;
								// store i1 true, i1* %reg_name, align 1
								fprintf(printFile, "%s%c%s = alloca i1, align 1 \n", instr_Indent, '%', target_id);
								fprintf(printFile, "%sstore i1 %s, i1* %c%s, align 1 \n", instr_Indent, ret_bool_val, '%', target_id);
							}
							else if (p1->kind.exp == IdK) { // ex. const y = x;
								fprintf(printFile, "%s%c%s = alloca i1, align 1 \n", instr_Indent, '%', target_id);
								fprintf(printFile, "%sstore i1 %c%d, i1* %c%s, align 1 \n", instr_Indent, '%', ret_reg, '%', target_id);
							}
						}
						break;
					// CONST_STMT -> ID = LITERAL ; LITERAL -> STRING_CONST | CHAR_CONST
					case Character:
					case String:
						{
							if (p1->kind.exp == CharStr_constK) {
								// %test_id = alloca i8*, align 8
								fprintf(printFile, "%s%c%s = alloca i8*, align 8 \n", instr_Indent, '%', target_id);
								// store i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str, i32 0, i32 0), i8** %test_id, align 8
								// 其中 ret_CharStr_length 要 -1，因為要扣掉兩個上引號，再加上空字元(\00)的空間，才是真實大小
								fprintf(printFile, "%sstore i8* getelementptr inbounds ([%d x i8], [%d x i8]* @.literal.%d, i32 0, i32 0), i8** %c%s, align 8 \n", 
													instr_Indent, ret_CharStr_length - 1, ret_CharStr_length - 1, ret_CharStr_varNo, '%', target_id);
							}
							// CONST_STMT -> ID = ID, 其中右側 ID type 為 Char or String
							else if (p1->kind.exp == IdK) {
								// const y = x;
								// y = target_id( = ret_IdK_name )
								// ====================================
								// %y = alloca i8*, align 8 ; 打印
								// ... 
								// %3 = load i8*, i8** %x, align 8 ; 交給 IdK 處理
								// store i8* %3, i8** %y, align 8  ; 打印
			  					// %4 = load i8*, i8** %y, align 8 ; 之後可再拿 Y 出來用
								fprintf(printFile, "%s%c%s = alloca i8*, align 8 \n", instr_Indent, '%', target_id);
								fprintf(printFile, "%sstore i8* %c%d, i8** %c%s, align 8 \n", instr_Indent, '%', ret_reg, '%', target_id);
							}
						}
						break;
					default:
						break;
				}
			}
			// 非 const dcl 狀態的一般 assign 動作
			else if (const_dcl_flag == 0) {
				switch (p1->type)
				{
					case Integer:
						{
							if (p1->kind.exp == NumK) {
								// store i32 number_value, i32* %be_assigned_id, align 4
								fprintf(printFile, "%sstore i32 %d, i32* %c%s, align 4 \n", instr_Indent, ret_NumK, '%', target_id);
								isNumK_flag = 0; // 需要修正 isNumK_flag 的值
							}
							// ASSIGNMENT_STMT -> ID = SIMPLE_EXPR ; ID: SSA_reg_var 
							// SIMPLE_EXPR -> SIMPLE_EXPR ; ret_reg 返回各種運算
							// 這也包含 CompoundK Number
							// SIMPLE_EXPR -> ( + | - | ε ) NUMBER ; ret_reg 返回 CompoundK number
							else {
								// store i32 %ret_reg_var, i32* %be_assigned_id, align 4
								fprintf(printFile, "%sstore i32 %c%d, i32* %c%s, align 4 \n", instr_Indent, '%', ret_reg, '%', target_id);
							}
						}
						break;
					case Boolean:
						{
							fprintf(printFile, "%sstore i1 %c%d, i1* %c%s, align 1 \n", instr_Indent, '%', ret_reg, '%', target_id);
						}
						break;
					default:
						break;
				}
			}
			break; // case AssignK:
		}

		case ReadK:
			// 這邊 read 只實作到可以讀 Integer 功能
			p0 = t->child[0];

			if (p0->kind.exp == IdK && p0->type == Integer) {
				// %reg_no = call i32 (i8*, ...) @__isoc99_scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str, i32 0, i32 0), i32* %i)
				fprintf(printFile, "%s%c%d = call i32 (i8*, ...) @__isoc99_scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str, i32 0, i32 0), i32* %c%s)\n"
					, instr_Indent, '%', reg_no, '%', p0->attr.name);
				reg_no++;
			}
			else {
				printf("非 Integer ID 讀取功能尚未實作 \n");
			}
			break;

		case PrintK:
			p0 = t->child[0];
			
			// println(SIMPLE_EXPR); 
			if (p0->kind.exp == OpK) {
				cGen(p0);
				// %5 = sub nsw i32 %left_reg, %right_reg
				// %6 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.1, i32 0, i32 0), i32 %5)
				fprintf(printFile, "%s%c%d = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.1, i32 0, i32 0), i32 %c%d) \n"
									, instr_Indent, '%', reg_no, '%', ret_reg);
				reg_no++;
			}
			// print ( ID ); ID = SIMPLE_EXPR | Integer;
			if (p0->kind.exp == IdK && p0->type == Integer) {
				// %5 = load i32, i32* %n, align 4
				// %6 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.1, i32 0, i32 0), i32 %5)
				fprintf(printFile, "%s%c%d = load i32, i32* %c%s, align 4 \n", instr_Indent, '%', reg_no, '%', p0->attr.name);
				reg_no++;
				ret_reg = reg_no - 1;
				fprintf(printFile, "%s%c%d = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.1, i32 0, i32 0), i32 %c%d) \n"
									, instr_Indent, '%', reg_no, '%', ret_reg);
				reg_no++;
			}
			// print (ID); ID = "string" | ID = 'c'
			else if ( p0->kind.exp == IdK && (p0->type == String || p0->type == Character) ) {
				// y = x;
				// printf("%s\n", y);
				// =============================================
				// @.str.1 = private unnamed_addr constant [12 x i8] c"%s\00", align 1
				// ...
				// %4 = load i8*, i8** %y, align 8
  				// %5 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.1, i32 0, i32 0), i8* %4)
				fprintf(printFile, "%s%c%d = load i8*, i8** %c%s, align 8 \n", instr_Indent, '%', reg_no, '%', p0->attr.name);
				reg_no++;
				ret_reg = reg_no - 1;
				fprintf(printFile, "%s%c%d = call i32 (i8*, ...) @printf(i8* getelementptr inbounds([3 x i8], [3 x i8]* @.str.2, i32 0, i32 0), i8* %c%d); \n"
					                , instr_Indent, '%', reg_no, '%', ret_reg);
				reg_no++;
			}
			// print (LITERAL); LITERAL -> STRING_CONST | CHAR_CONST
			else if (p0->kind.exp == CharStr_constK) {
				cGen(p0); // 寫在這避免影響上面 print ( ID ); 可能印出雙重 load 指令
				// @printf 範例: 
				// %12 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.7, i32 0, i32 0), 
				//                                   i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.8, i32 0, i32 0))
				// 其中 @.str.7 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
				fprintf(printFile, "%s%c%d = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([%d x i8], [%d x i8]* @.literal.%d, i32 0, i32 0)) \n"
					                , instr_Indent, '%', reg_no, ret_CharStr_length - 1, ret_CharStr_length - 1, ret_CharStr_varNo);
				reg_no++;
			}
			break;

		case PrintlnK: // 相比 PrintK 多了換行動作
			p0 = t->child[0];
			
			// println(SIMPLE_EXPR); 
			if (p0->kind.exp == OpK) {
				cGen(p0);
				// %5 = sub nsw i32 %left_reg, %right_reg
				// %6 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.3, i32 0, i32 0), i32 %5)
				fprintf(printFile, "%s%c%d = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.3, i32 0, i32 0), i32 %c%d) \n"
									, instr_Indent, '%', reg_no, '%', ret_reg);
				reg_no++;
			}
			// println ( ID ); ID = SIMPLE_EXPR;
			if (p0->kind.exp == IdK && p0->type == Integer) {
				// %5 = load i32, i32* %n, align 4
				// %6 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.3, i32 0, i32 0), i32 %5)
				fprintf(printFile, "%s%c%d = load i32, i32* %c%s, align 4 \n", instr_Indent, '%', reg_no, '%', p0->attr.name);
				reg_no++;
				ret_reg = reg_no - 1;
				fprintf(printFile, "%s%c%d = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.3, i32 0, i32 0), i32 %c%d) \n"
									, instr_Indent, '%', reg_no, '%', ret_reg);
				reg_no++;
			}
			// println (ID); ID = "string" | ID = 'c'
			else if ( p0->kind.exp == IdK && (p0->type == String || p0->type == Character) ) {
				// y = x;
				// printf("%s\n", y);
				// =============================================
				// @.str.1 = private unnamed_addr constant [12 x i8] c"%s\0A\00", align 1
				// ...
				// %4 = load i8*, i8** %y, align 8
  				// %5 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.1, i32 0, i32 0), i8* %4)
				fprintf(printFile, "%s%c%d = load i8*, i8** %c%s, align 8 \n", instr_Indent, '%', reg_no, '%', p0->attr.name);
				reg_no++;
				ret_reg = reg_no - 1;
				fprintf(printFile, "%s%c%d = call i32 (i8*, ...) @printf(i8* getelementptr inbounds([4 x i8], [4 x i8]* @.str.4, i32 0, i32 0), i8* %c%d); \n"
					                , instr_Indent, '%', reg_no, '%', ret_reg);
				reg_no++;
			}
			// println (LITERAL); LITERAL -> STRING_CONST | CHAR_CONST
			else if (p0->kind.exp == CharStr_constK) {
				cGen(p0); // 寫在這避免影響上面 print ( ID ); 可能印出雙重 load 指令
				// %12 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.7, i32 0, i32 0), 
				//                                   i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.8, i32 0, i32 0))
				fprintf(printFile, "%s%c%d = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.4, i32 0, i32 0), i8* getelementptr inbounds ([%d x i8], [%d x i8]* @.literal.%d, i32 0, i32 0)) \n"
					                , instr_Indent, '%', reg_no, ret_CharStr_length - 1, ret_CharStr_length - 1, ret_CharStr_varNo);
				reg_no++;
			}
			break;

		case Type_dclK: {
			// type_dcl_flag 若為非 0，表示處在 dcl 宣告狀態
			// 不同值表示不同型別
			// 基於方便 char 與 string 我都當同樣標地處理，意即 char 為 string 的特例 
			if (strcmp(t->attr.dcl, "int") == 0) // "int"
				type_dcl_flag = 1;
			else if (strcmp(t->attr.dcl, "bool") == 0) // "bool"
				type_dcl_flag = 2;
			else if (strcmp(t->attr.dcl, "char") == 0) // "char"
				type_dcl_flag = 3;
			else // "string"
				type_dcl_flag = 3;
			//type_dcl_flag = 1;
			p0 = t->child[0]; /* id_list of var_dcl */
			cGen(p0);
			// 結束 dcl 宣告狀態
			type_dcl_flag = 0;
			break;
		}

		case Const_dclK:
			const_dcl_flag = 1;
			p0 = t->child[0]; /* const_list of const_dcl */
			cGen(p0);
			const_dcl_flag = 0;
			break;

		case MainK:
			/* 目前 Vanilla-c 尚未定義功用 */
			fprintf(printFile, "define i32 @main() ");
			break;

		case PgbdK:
			fprintf(printFile, "{ \n");
			// %1 = alloca i32, align 4
			fprintf(printFile, "%s%c%d = alloca i32, align 4 \n", instr_Indent, '%', reg_no);
			reg_no++;
			// store i32 0, i32* %1, align 4
			fprintf(printFile, "%sstore i32 0, i32* %c1, align 4 \n", instr_Indent, '%');

			p0 = t->child[0]; /* dcl_list  */
			p1 = t->child[1]; /* stmt_list */

			cGen(p0);
			cGen(p1);

			fprintf(printFile, "%sret i32 0 \n", instr_Indent);
			fprintf(printFile, "} \n");
			fprintf(printFile, "\n");
			break;

		default:
			break;
	}
}


static void genExp(TreeNode * t)
{
	TreeNode *p0, *p1;

	switch (t->kind.exp)
	{
		case OpK: {
			int L_opd_reg_no, R_opd_reg_no;
			char L_opd[50];
			char R_opd[50];
			p0 = t->child[0];
			p1 = t->child[1];

			/* left opd */
			cGen(p0);
			if (isNumK_flag == 1) {
				// p0_ret = ret_NumK;
				sprintf(L_opd, "%d", ret_NumK); // 設為數字字串
				isNumK_flag = 0;
			}
			else {
				// L_opd_reg_no = ret_reg;
				sprintf(L_opd, "%c%d", '%', ret_reg); // 設為 SSA 變數字串
			}
			
			/* right opd */
			cGen(p1);
			if (isNumK_flag == 1) {
				//R_opd_reg_no = ret_NumK;
				sprintf(R_opd, "%d", ret_NumK); // 設為數字字串
				isNumK_flag = 0;
			}
			else {
				//R_opd_reg_no = ret_reg;
				sprintf(R_opd, "%c%d", '%', ret_reg); // 設為 SSA 變數字串
			}

			switch (t->attr.op)
			{
				case ADD: // "+";  
					if (sign_opt_flag == 1) { // CompounK 正/負號 設定
						// 正號為 0
						sign_neg_flag = 0;
					}
					else {
						// %reg_no = add nsw i32 %left_reg, %right_reg
						fprintf(printFile, "%s%c%d = add nsw i32 %s, %s \n", instr_Indent, '%', reg_no, L_opd, R_opd);
						reg_no++;
						ret_reg = reg_no - 1;
					}
					break;

				case SUB: // "-";  
					if (sign_opt_flag == 1) { // CompounK 正/負號 設定
						// 負號為 1
						sign_neg_flag = 1;
					}
					else {
						// %reg_no = sub nsw i32 %left_reg, %right_reg
						fprintf(printFile, "%s%c%d = sub nsw i32 %s, %s \n", instr_Indent, '%', reg_no, L_opd, R_opd);
						reg_no++;
						ret_reg = reg_no - 1;
					}
					break;

				case MUL: // "*";  
					// %reg_no = mul nsw i32 %left_reg, %right_reg
					fprintf(printFile, "%s%c%d = mul nsw i32 %s, %s \n", instr_Indent, '%', reg_no, L_opd, R_opd);
					reg_no++;
					ret_reg = reg_no - 1;
					break;

				case DIV: // "/";  
					// %reg_no = sdiv i32 %dividends, %divisor
					fprintf(printFile, "%s%c%d = sdiv i32 %s, %s \n", instr_Indent, '%', reg_no, L_opd, R_opd);
					reg_no++;
					ret_reg = reg_no - 1;
					break;

				case MOD: // "%";
					// %reg_no = srem i32 %dividends, %divisor  
					fprintf(printFile, "%s%c%d = srem i32 %s, %s \n", instr_Indent, '%', reg_no, L_opd, R_opd);
					reg_no++;
					ret_reg = reg_no - 1;
					break;

				// <result> = icmp <cond> <ty> <op1>, <op2>   ; yields i1 or <N x i1>:result
				// Example :  %4 = icmp sle i32 %3, 5  ; i <= 5
				/*	<cond> :
							eq: equal
							ne: not equal
							ugt: unsigned greater than
							uge: unsigned greater or equal
							ult: unsigned less than
							ule: unsigned less or equal
							sgt: signed greater than
							sge: signed greater or equal
							slt: signed less than
							sle: signed less or equal
				*/
				case GR: // ">";  
					fprintf(printFile, "%s%c%d = icmp sgt i32 %s, %s \n", instr_Indent, '%', reg_no, L_opd, R_opd);
					reg_no++;
					ret_reg = reg_no - 1;
					break;
				case LS: // "<"; 
					fprintf(printFile, "%s%c%d = icmp slt i32 %s, %s \n", instr_Indent, '%', reg_no, L_opd, R_opd);
					reg_no++;
					ret_reg = reg_no - 1;
					break;
				case EQ: // "=="; 
					fprintf(printFile, "%s%c%d = icmp eq i32 %s, %s \n", instr_Indent, '%', reg_no, L_opd, R_opd);
					reg_no++;
					ret_reg = reg_no - 1;
					break;
				case NOT_EQ: // "!=";
					fprintf(printFile, "%s%c%d = icmp ne i32 %s, %s \n", instr_Indent, '%', reg_no, L_opd, R_opd);
					reg_no++; 
					ret_reg = reg_no - 1;
					break;
				case GR_EQ: // ">=";
					fprintf(printFile, "%s%c%d = icmp sge i32 %s, %s \n", instr_Indent, '%', reg_no, L_opd, R_opd);
					reg_no++; 
					ret_reg = reg_no - 1;
					break;
				case LS_EQ: // "<="; 
					fprintf(printFile, "%s%c%d = icmp sle i32 %s, %s \n", instr_Indent, '%', reg_no, L_opd, R_opd);
					reg_no++;
					ret_reg = reg_no - 1;
					break;

				default:
					break;
			}
			break;
		}

		case NumK:
			isNumK_flag = 1; // traverse 到此 NumK 點，設此 flag，用於 CompoundK 區分子節點為 NumK or IdK
			// 直接回傳數值
			ret_NumK = t->attr.val;
			break;

		case IdK: {
			// Type_dclK 子點
			// 宣告的 IdK 跟 其他操作的 IdK 不同，故執行指令不同，還要考慮宣告 list 的 sibling 問題
			// 又依照 type_dcl_flag 不同數值決定其 alloca type (如: i32 或 i8*)
			if (type_dcl_flag == 1) { // int dcl
				fprintf(printFile, "%s%c%s = alloca i32, align 4 \n", instr_Indent, '%', t->attr.name);
			}
			else if (type_dcl_flag == 2) { //bool dcl
				// Example: 
				// 		%reg_var = alloca i1, align 1
				fprintf(printFile, "%s%c%s = alloca i1, align 1 \n", instr_Indent, '%', t->attr.name);
			}
			else if (type_dcl_flag == 3) { // char & string dcl
				// Example: 
				//		%test = alloca i8*, align 8
				fprintf(printFile, "%s%c%s = alloca i8*, align 8 \n", instr_Indent, '%', t->attr.name);
			}
			// AssignK 左子點
			// 一般的 assign 左側 ID，故只要知道其 ID 名即可
			else if (assign_L_opd_flag == 1) { 
				ret_IdK_name = t->attr.name;
				assign_L_opd_flag = 0;
			}
			// AssignK 右子點或 Exp 中的某個 ID 
			else if (assign_L_opd_flag == 0) {
				// 此前宣告時，一定已被 alloca 過，因此執行 load 到 SSA 變數存放 
				if (t->type == String || t->type == Character) { // string or char type
					// %reg_no = load i8*, i8** %str_id, align 8
					fprintf(printFile, "%s%c%d = load i8*, i8** %c%s, align 8 \n", instr_Indent, '%', reg_no, '%', t->attr.name);
					reg_no++;
				}
				else if (t->type == Boolean) { // bool type
					fprintf(printFile, "%s%c%d = load i1, i1* %c%s, align 1 \n", instr_Indent, '%', reg_no, '%', t->attr.name);
					reg_no++;
				}
				else if (t->type == Integer) { // int type
					// %reg_no = load i32, i32* %Id, align 4
					fprintf(printFile, "%s%c%d = load i32, i32* %c%s, align 4 \n", instr_Indent, '%', reg_no, '%', t->attr.name);
					reg_no++;
				}
				// 儲存 load 指令 result 的 SSA 暫存器變數
				ret_reg = reg_no - 1;
			}
			break;
		}

		case CharStr_constK: {
			int keepFinding_flag = 1, strcmp_test, count = 0;
			LitTabList *tmp_list; 
			tmp_list = save_LitTab_collection;
			
			while ( tmp_list != NULL && keepFinding_flag == 1 ) // 查找 save_LitTab_collection 比對找出其 literal 全域變數
			{
				strcmp_test = strcmp(tmp_list->ret_item, t->attr.char_str_item);
				if (strcmp_test == 0) { // node 所存之值一樣，表示找到
					ret_CharStr_varNo = count;
					ret_CharStr_length = strlen(tmp_list->ret_item);
					keepFinding_flag = 0;
				}
				else {
					tmp_list = tmp_list->next;
					count++;
				}
			}
			break;
		}

		case Compound_opdK:
			{
				p0 = t->child[0]; // sign
				p1 = t->child[1]; // NumK or IdK

				sign_opt_flag = 1;

				cGen(p0); // sign
				cGen(p1); // NumK or IdK

				leftChild_flag = 0; // yacc 寫法中，NumK 一律在右邊，此 flag 用作左子點 +/- OpK 判斷

				// CompoundK: 
				// left_child 為 sign 符號
				// right_child 為 Num or Id 
				if (isNumK_flag == 1) { // NumK
					if (sign_neg_flag == 1) { // -Num 
						// 0 減去 Num，亦即對 Num 做"變號"
						// %reg_no = sub nsw i32 0, %ret_reg
						// %ret_reg 為"CompoundK"反還的子節點
						fprintf(printFile, "%s%c%d = sub nsw i32 0, %d \n", instr_Indent, '%', reg_no, ret_NumK);
						reg_no++;
						ret_reg = reg_no - 1;
					}
					else { // +Num
						// 不必變號
						fprintf(printFile, "%s%c%d = add nsw i32 0, %d \n", instr_Indent, '%', reg_no, ret_NumK);
						reg_no++;
						ret_reg = reg_no - 1;
					}
					isNumK_flag = 0;
				}
				else { // IdK
					if (sign_neg_flag == 1) { // -Id
						fprintf(printFile, "%s%c%d = sub nsw i32 0, %c%d \n", instr_Indent, '%', reg_no, '%', ret_reg);
						reg_no++;
						ret_reg = reg_no - 1;
					}
					else { // +Id
						// reg_no++; // 配合 ret_reg = reg_no - 1; 用
						// 不必變號
					}
				}
				sign_opt_flag = 0;
			}
			break;

		case BoolK:
			// True
			if (t->attr.bool_Value == 1) {
				ret_bool_val = "true";
			}
			// False
			else {
				ret_bool_val = "false";
			}
			break;

		default:
			break;
	}
}


/* Procedure cGen recursively generates code by
 * tree traversal
 */
static void cGen(TreeNode *tree)
{
	if (tree != NULL)
	{
		switch (tree->nodekind)
		{
			case StmtK:
				genStmt(tree);
				break;
			case ExpK:
				genExp(tree);
				break;
			default:
				break;
		}
		cGen(tree->sibling);
	}
}


/* 在 .ll 的 module Structure 「全域變數宣告區」中打印 literal constant data 和其變數 */
/* Example: 
    ; Declare the string constant as a global constant.
	@.str = private unnamed_addr constant [13 x i8] c"hello world\0A\00" */
static void printGlobVar_of_LitData(void)
{
	int count = 0, strlen_value;
	char tmp_char, *tmp_str;
	LitTabList *LitTab_collection;
	LitTab_collection = get_LitTab_collection();
	save_LitTab_collection = LitTab_collection; // 保存供之後查詢使用

	while (LitTab_collection != NULL)
	{
		if ( justChar_notString(LitTab_collection->ret_item) ) // if true = 字元
		{
			//  將 literal table 儲存的格式做調整，去掉上單引號，只取真正的 char
			//  Example : 
			//      'c' 變成 c
			tmp_char = *((LitTab_collection->ret_item) + 1);
			// Example : 
			// 		@.str.1 = private unnamed_addr constant [9 x i8] c"test string \0A\00", align 1
			fprintf(printFile, "@.literal.%d = private unnamed_addr constant [%d x i8] c\"%c\\00\", align 1 \n", count, 2, tmp_char);
		}
		else { // else = 字串
			tmp_str = (LitTab_collection->ret_item) + 1;  // 去頭，將前面的上引號去掉
			// 去掉尾部上引號，並記得要處理空字元 '\0' 的位置
			strlen_value = strlen(tmp_str);
			char tmp_arr[strlen_value];
			int i = 0;
			while (i <= strlen_value) 
			{
				tmp_arr[i] = *(tmp_str + i);
				if ( i == (strlen_value - 1) ) {
					tmp_arr[i] = '\0';
				}
				i++;
			}
			// Example : 
			// 		@.str.1 = private unnamed_addr constant [9 x i8] c"test string \0A\00", align 1
			fprintf(printFile, "@.literal.%d = private unnamed_addr constant [%d x i8] c\"%s\\00\", align 1 \n", count, strlen_value, tmp_arr);
		}
		count++; // literal 全域變數編號
		LitTab_collection = LitTab_collection->next;
	}
	fprintf(printFile, "\n");
}


void GenIR(TreeNode *syntaxTree, FILE *codefile)
{
	printFile = codefile;
	reg_no = 1;

	fprintf(printFile, "@.str = private unnamed_addr constant [3 x i8] c\"%c%c\\00\", align 1 ; for scanf \n", '%', 'd');
	fprintf(printFile, "@.str.1 = private unnamed_addr constant [3 x i8] c\"%c%c\\00\", align 1 \n", '%', 'd');
	fprintf(printFile, "@.str.2 = private unnamed_addr constant [3 x i8] c\"%c%c\\00\", align 1 \n", '%', 's');
	fprintf(printFile, "@.str.3 = private unnamed_addr constant [4 x i8] c\"%c%c\\0A\\00\", align 1 \n", '%', 'd');
	fprintf(printFile, "@.str.4 = private unnamed_addr constant [4 x i8] c\"%c%c\\0A\\00\", align 1 \n", '%', 's');
	
	printGlobVar_of_LitData();
	
	/* generate code for TINY program */
	cGen(syntaxTree);

	// declare i32 @__isoc99_scanf(i8*, ...)
	fprintf(printFile, "declare i32 @__isoc99_scanf(i8*, ...) \n");
	fprintf(printFile, "\n");
	// declare i32 @printf(i8*, ...)
	fprintf(printFile, "declare i32 @printf(i8*, ...) \n");
	fprintf(printFile, "\n");
}

