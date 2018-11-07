#include <string.h>
#include "analyze.h"
#include "util.h"
#include "symtable.h"
#include "yacc.tab.h"

typedef struct IdDclListRec 
{
	char *id_name;
	struct IdDclListRec *next;
} IdDclList;

static IdDclList *id_dcl_set_start;
static IdDclList *id_dcl_set_end;

static int dcl_flag;

static void traceTree(TreeNode *t);

static void id_dcl_set_insert(char *insert_id_name)
{
	if (id_dcl_set_start == NULL) {
		id_dcl_set_start = (IdDclList*) malloc(sizeof(IdDclList));
		id_dcl_set_start->id_name = copyString(insert_id_name);
		id_dcl_set_start->next = NULL;
		id_dcl_set_end = id_dcl_set_start;
	}
	else {
		id_dcl_set_end->next = (IdDclList*) malloc(sizeof(IdDclList));
		id_dcl_set_end->next->id_name = copyString(insert_id_name);
		id_dcl_set_end->next->next = NULL;
		id_dcl_set_end = id_dcl_set_end->next;
	}
}

/* 判斷是否有 repeated dclaration 重複宣告的情況 
 * 若有回傳 1
 * 沒有則將 id 加入 id_dcl_set ，供下個 id 判斷重複宣告用
 * insert_flag: 0 找不到 id，也不對宣告集合作新增 (check type 狀態用)
 * insert_flag: 1 找不到 id，則對宣告集合新增該 id (check dcl 狀態用) 
 */
static int id_ReDcl_mgmt(char * check_id, int insert_flag)
{
	IdDclList *l;
	l = id_dcl_set_start;

	while (l != NULL)
	{
		// 比對到相同的代表有重複宣告，回傳 1
		if (strcmp(l->id_name, check_id) == 0) 
			return 1;
		else {
			l = l->next;
		}
	}

	if (insert_flag == 1)
		id_dcl_set_insert(check_id);

	return 0;
}


static void typeError(TreeNode *t, char *message)
{
	fprintf(listing, "Type error at line %d: %s\n", t->lineno, message);
	error_signal = 1;
}


// 對每個節點的型別作處理跟檢查
static void checkNode_type(TreeNode *t)
{
	switch (t->nodekind)
	{
		case StmtK:
			switch (t->kind.stmt)
			{
				case Type_dclK: 
					break;				

				case Const_dclK: 		
					if (dcl_flag == 5)
						dcl_flag = 0;
					break;

				case AssignK:
				{
					if (dcl_flag == 5) { // const_dcl
						printf("AssignK: check **********\n");
						symtab_type_setting(t->child[0]->attr.name, t->child[1]->type);

						t->child[0]->type = t->child[1]->type;
						printf("t->child[1]->type: %d \n", t->child[1]->type);
						printf("t->child[0]->type: %d \n", t->child[0]->type);
					}
					else {
						if (t->child[0]->const_attr_tag == 1)
							typeError(t->child[0], "You can not assign data to const ID.");
						else if (t->child[0]->type != t->child[1]->type)
							typeError(t->child[0], "Inconsistence data-type for assign.");
					}
					break;
				}
					
				case IfK:
					if (t->child[0]->type != Boolean && t->child[0]->type != Integer)
						typeError(t->child[0], "If test is not Boolean, even not Integer.");
					break;
				case WhileK:
					if (t->child[0]->type != Boolean && t->child[0]->type != Integer)
						typeError(t->child[0], "While test is not Boolean, even not Integer.");
					break;
					
				/* 被宣告為 const 的變數不可再被寫入更改 */
				case ReadK:
					if (t->child[0]->const_attr_tag == 1)
						typeError(t->child[0], "ReadK: Write to const ID.");
					break;
				case PrintK: 
					break;
				case PrintlnK: 
					break;

				default:
					break;
			}
			break;

		case ExpK:
			switch (t->kind.exp)
			{
				case OpK:
					switch (t->attr.op)
					{
						/* +/- 符號除了算數運算外，兼有正/負表示功能，須加以區別 */
						case ADD: // "+"  
						case SUB: // "-"
							if (t->child[0] == NULL)
								printf("Positive or negtive sign. \n");
							else {
								if ((t->child[0]->type != Integer) || (t->child[1]->type != Integer))
									typeError(t, "Arithmetic operator applied to non-integer operand.");
								else
									t->type = Integer;
							}
							break;

						case MUL: // "*"  
						case DIV: // "/"  
						case MOD: // "%"
							if ((t->child[0]->type != Integer) || (t->child[1]->type != Integer))
								typeError(t, "Arithmetic operator applied to non-integer operand.");
							else
								t->type = Integer;
							break;  

						case GR: // ">"  
						case LS: // "<"  
						case EQ: // "==" 
						case NOT_EQ: // "!=" 
						case GR_EQ: // ">=" 
						case LS_EQ: // "<="
							if ((t->child[0]->type != Integer) || (t->child[1]->type != Integer))
								typeError(t, "Comparison operator applied to non-integer operand.");
							else
								t->type = Boolean; 
							break;

						default:
							typeError(t, "Undefined operator. ");
							break;
					}
					break;

				case CharStr_constK:
					if (justChar_notString(t->attr.char_str_item)) 
						t->type = Character;
					else 
						t->type = String;
					break;

				case BoolK:
					t->type = Boolean;
					break;

				case Compound_opdK:
					if (t->child[1]->kind.exp == NumK)
						t->type = Integer;
					else if (t->child[1]->kind.exp == IdK && t->child[1]->type == Integer)
						t->type = Integer;

					/* ID 型態宣告在 vanilla-c 中須在程式開始進行，而且只能是簡單 ID               */
					/* 除了 const ID 外，其他 ID 必先宣告過型態，並經過上面 case Type_dclK: 的處理 */
					/* 因而，組成 Compound_opdK 的 ID 型態一定已被設定過，便可知是否為 Integer     */
					/* 所以可以在下方這裡直接判斷是否為 Integer，如果不是就不該與(+/-)組合         */
					else if (t->child[1]->kind.exp == IdK && t->child[1]->type != Integer)
						typeError(t, "This compound id is not integer.");
					break;

				case NumK:
					t->type = Integer;
					break;

				case IdK:
					// 檢查是否未宣告就使用
					if (dcl_flag == 0) {
						int check;
						check = id_ReDcl_mgmt(t->attr.name, 0);
						if (check == 0)
							typeError(t, "checkNode_dcl() -> IdK: Undefined id.");
					}
					/* 查找 symtab 中的宣告型態給予相同型態 */
					t->type  = id_type_lookup(t->attr.name);
					t->const_attr_tag = id_const_tag(t->attr.name);
					break;

				default:
					break;
			}
			break;
		default:
			break;
	}
}


// 專職 dcl 宣告命名檢查部分，設定 symboltable 資訊
static void checkNode_dcl (TreeNode *t)
{
	switch (t->nodekind)
	{
		case StmtK:
			switch (t->kind.stmt)
			{
				case Type_dclK: 
				{
					char int_type[] = "int";
					char char_type[] = "char";
					char bool_type[] = "bool";
					char string_type[] = "string";

					if (strcmp(t->attr.dcl, int_type) == 0) {
						dcl_flag = 1;
					}
					else if (strcmp(t->attr.dcl, char_type) == 0) {
						dcl_flag = 2;
					}
					else if (strcmp(t->attr.dcl, bool_type) == 0) {
						dcl_flag = 3;
					}
					else if (strcmp(t->attr.dcl, string_type) == 0) {
						dcl_flag = 4;
					}
					else
						typeError(t, "Undefined type.");

					traceTree(t->child[0]);
					dcl_flag = 0;
					break;
				}

				case Const_dclK: 
				{
					printf("goto Const_dclK\n");
					dcl_flag = 5;
					traceTree(t->child[0]);
					dcl_flag = 0;
					break;
				}

				case AssignK:
				{
					if (dcl_flag == 5) {
						traceTree(t->child[0]);
						if (t->child[1]->kind.exp == IdK) {
							int check;
							check = id_ReDcl_mgmt(t->child[1]->attr.name, 0);
							if (check == 0)
								typeError (t->child[1], "Undefined id.");
						}
					}
					else
						typeError(t, "AssignK of checkNode_dcl: dcl_flag != 5 (dcl_flag should be 5, 因為宣告狀態只有 const_dcl 用到 AssignK)");
					break;
				}

				case MainK:
					break;
				case PgbdK:
					traceTree(t->child[0]);
					break;
				default:
					break;
			}
			break;

		case ExpK:
			switch (t->kind.exp) 
			{
				case IdK:
				{
					int check = 0;
					IdDclList *l;
					l = id_dcl_set_start;

					// 未設定成宣告狀態，不符此處要求動作
					if (dcl_flag == 0) {
						/* 查找 symtab 中的宣告型態給予相同型態 */ 
						//t->type = id_type_lookup(t->attr.name);
						//typeError(t, "Undefined declaration.");
						//if (error_signal == 1)
							//printf("Node: %s\n", t->attr.name);
						typeError(t, "checkNode_dcl() -> IdK: dcl_flag == 0 ");
					}
					else { // ID 宣告狀態
						// 檢查是否有重複宣告
						check = id_ReDcl_mgmt(t->attr.name, 1);
						if (check == 1) 
							typeError(t, "ID repeated declaration.");
						else {
							if (dcl_flag == 1) {
								symtab_type_setting(t->attr.name, Integer);
							}
							else if (dcl_flag == 2) {
								symtab_type_setting(t->attr.name, Character);
							}
							else if (dcl_flag == 3) {
								symtab_type_setting(t->attr.name, Boolean);
							}
							else if (dcl_flag == 4) {
								symtab_type_setting(t->attr.name, String);
							} 
							else if (dcl_flag == 5) {
								printf("dcl_flag == 5 ***********\n");
								symtab_const_setting(t->attr.name);
							}
							else {
								typeError(t, "checkNode_dcl() -> IdK: dcl_flag != 0 ~ 5  ");
							}
						}
					}
					break;
				}

				default:
					break;
			}
			break;

		default:
			break;
	}
}


static void traceTree(TreeNode *t)
{
	if (t != NULL)
	{
		checkNode_dcl(t);
		traceTree(t->sibling);
	}
}


static void dclCheck(TreeNode *syntaxTree)
{
	traceTree(syntaxTree);
}


static void const_dcl_flag_set(TreeNode *t)
{
	if (t->nodekind == StmtK && t->kind.stmt == Const_dclK) {
		dcl_flag = 5;
	}
}


/* Procedure typeCheck performs type checking
 * by a postorder syntax tree traversal
 */
static void typeCheck(TreeNode *syntaxTree)
{
	traverse(syntaxTree, const_dcl_flag_set, checkNode_type);
}


void semantic(TreeNode *syntaxTree)
{
	dclCheck(syntaxTree);
	typeCheck(syntaxTree);
}

