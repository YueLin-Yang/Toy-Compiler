#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "yacc.tab.h"

/* nullProc is a do-nothing procedure to
 * generate preorder-only or postorder-only
 * traversals from traverse
 */
void nullProc(TreeNode *t)
{
	if ( t == NULL )
		return;
	else
		return;
}


/* Procedure traverse is a generic recursive
 * syntax tree traversal routine:
 * it applies preProc in preorder and postProc
 * in postorder to tree pointed to by t
 */
void traverse( TreeNode *t, void(*preProc) (TreeNode *), void (*postProc) (TreeNode *))
{
	if (t != NULL)
	{
		preProc(t);
		int i;
		for (i = 0; i < MAXCHILDREN; i++)
			traverse(t->child[i], preProc, postProc);
		postProc(t);
		traverse(t->sibling, preProc, postProc);
	}
}


/* Function copyString allocate and makes a new
 * copy of an existing string
 */
char *copyString(char *s) {

	int n;
	char *t;

	if (s == NULL)
		return NULL;
	n = strlen(s) + 1;
	t = malloc(n);
	if (t == NULL) {
		fprintf(listing, "Out of memory error at line %d\n", lineno);
	}
	else
		strcpy(t, s);
	return t;
}


/* 判斷是 char 還是 string 
   回傳 1 表示 char
   回傳 0 表示 string
 */
int justChar_notString(char *literal)
{
	int result, count;
	count = strlen(literal);

	/* 因儲存的字元有包含上單引號 ex. 'a' 故 strlen() 回傳值為 1個字元 + 2 個引號 = 3 */
	/* 另外，儲存的字串也有包含上雙引號 ex. "string" 故 strlen() 回傳值也同樣多 2     */
	if (count <= 3)
		result = 1;
	else
		result = 0;

	return result;
}


/* Function newStmNode creates a new statement
 * node for syntax tree construction
 */
TreeNode *newStmtNode(StmtKind kind) {

	TreeNode *t = (TreeNode *) malloc(sizeof(TreeNode));
	int i, line;

	if ( kind == WhileK || kind == IfK || kind == ElseK) {
		line = lineno_backtrack_stack[lineno_backtrack_stack_top];
		lineno_backtrack_stack_top -= 1;
	}
	else
		line = lineno;

	if (t == NULL) {
		fprintf(listing, "Out of memory error at line %d\n", lineno);
	}
	else {
		for ( i = 0; i < MAXCHILDREN; i++) {
			t -> child[i] = NULL;
		}
		t -> sibling = NULL;
		t -> nodekind = StmtK;
		t -> kind.stmt = kind;                       /* 傳入值 */
		t -> lineno = line;
	}
	return t;
}


/* Function newExpNode creates a new expression
 * node for syntax tree construction
 */
TreeNode *newExpNode(ExpKind kind) {

	TreeNode *t = (TreeNode *) malloc(sizeof(TreeNode));
	int i;

	if (t == NULL) {
		fprintf(listing, "Out of memory error at line %d\n", lineno);
	}
	else {
		for (i = 0; i < MAXCHILDREN; i++) {
			t -> child[i] = NULL;
		}
		t -> sibling = NULL;
		t -> nodekind = ExpK;
		t -> kind.exp = kind;                       /* 傳入值 */
		t -> lineno = lineno;
		t -> type = Void;
	}
	return t;
}


static char *trans_tokenTypeOp_to_string(TokenType op)
{
	char *ret;
	switch (op)
	{
		case ADD:    ret = "+";  break;
		case SUB:    ret = "-";  break;
		case MUL:    ret = "*";  break;
		case DIV:    ret = "/";  break;
		case MOD:    ret = "%";  break;
		case GR:     ret = ">";  break;
		case LS:     ret = "<";  break;
		case EQ:     ret = "=="; break;
		case NOT_EQ: ret = "!="; break;
		case GR_EQ:  ret = ">="; break;
		case LS_EQ:  ret = "<="; break;
		default:     ret = "Error!!"; break;
	}
	return ret;
}


char *TreeNodeInfoStr(TreeNode *t)
{
	char *info = (char *)malloc(60);
	char *kind;
	/* 初始化空間內容， 避免未知亂碼出現 */
	*info = '\0';

	if (t->nodekind == StmtK)
	{
		switch (t->kind.stmt)
		{
			case IfK:
				kind = "IfK: ";
				strcat(info, kind);
				break;
			case ElseK:
				kind = "ElseK: ";
				strcat(info, kind);
				break;
			case WhileK:
				kind = "WhileK: ";
				strcat(info, kind);
				break;
			case AssignK:
				kind = "AssignK: ";
				strcat(info, kind);
				break;
			case ReadK:
				kind = "ReadK: ";
				strcat(info, kind);
				break;
			case PrintK:
				kind = "PrintK: ";
				strcat(info, kind);
				break;
			case PrintlnK:
				kind = "PrintlnK: ";
				strcat(info, kind);
				break;
			case Type_dclK:
				kind = "Type_dclK: ";
				char *type_dcl = t->attr.dcl;
				strcat(info, kind);
				strcat(info, type_dcl);
				break;
			case Const_dclK:
				kind = "Const_dclK: ";
				char *const_dcl = t->attr.dcl;
				strcat(info, kind);
				strcat(info, const_dcl);
				break;
			case MainK:
				kind = "MainK: ";
				strcpy(info, kind);
				break;
			case PgbdK:
				kind = "PgbdK: ";
				strcpy(info, kind);
				break;
		}
	}
	else if (t->nodekind == ExpK)
	{
		switch (t->kind.exp)
		{
			case OpK:
				kind = "OpK: ";
				char *op_str = trans_tokenTypeOp_to_string(t->attr.op);
				strcat(info, kind);
				strcat(info, op_str);
				break;
			case NumK:
				kind = "NumK: ";
				char s[64];
				sprintf(s, "%d", t->attr.val); 
				strcat(info, kind);
				strcat(info, s);
				break;
			case IdK:
				kind = "IdK: ";
				char *id_name = t->attr.name;
				strcat(info, kind);
				strcat(info, id_name);
				break;
			case CharStr_constK:
				kind = "CharStr_constK: ";
				char *char_str_value = t->attr.char_str_item;
				strcat(info, kind);
				strcat(info, char_str_value);
				break;
			case Compound_opdK:
				kind = "Compound_opdK: ";
				strcat(info, kind);
				break;
			case BoolK:
				kind = "BoolK: ";
				char *bool_Value;
				if (t->attr.bool_Value == 0) {
					char tmp[] = "FALSE";
					bool_Value = tmp;
				}
				else if (t->attr.bool_Value == 1) {
					char tmp[] = "TRUE";
					bool_Value = tmp;
				}
				strcat(info, kind);
				strcat(info, bool_Value);
				break;			
			
		}
	}
	else {
		kind = "Neither StmtK nor ExpK, must something wrong. ";
		strcat(info, kind);
	}

	return info;
}


void preOrderPrint(FILE* printFile, TreeNode *t, int depth)
{
	if (t != NULL) {
		char *infoString, *rightShift;
		infoString = TreeNodeInfoStr(t);

		int x;
		for (x = 0; x <= depth; x++) {
			fprintf(printFile, "         ");
		}
		fprintf(printFile, "------ %s    line: %d \n", infoString, t->lineno);

		// printf("%d\n", depth);
		int i;
		for (i = 0; i < MAXCHILDREN; i++) {
			preOrderPrint(printFile, t->child[i], ++depth);
			depth--;
		}
		preOrderPrint(printFile, t->sibling, depth);
	}
}


void printSyntaxTree(FILE* printFile, TreeNode *syntaxTree)
{
	preOrderPrint(printFile, syntaxTree, 0);
}

