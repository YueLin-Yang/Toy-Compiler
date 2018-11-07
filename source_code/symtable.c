#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtable.h"
#include "util.h"

/*  counter for variable memory location  */
static int location = 0;

/*  SIZE is the size of the hash table  */
/*  211 是質數，使hash func 表現更佳    */ 
#define SIZE 211

/* SHIFT is the power of two used as multiplier
 * in hash function
 */
#define SHIFT 4

/*  the hash table  */
static BucketList symbolTable[SIZE];

static BucketList literalTable[SIZE];

BucketList item_transger;

/*  the hash function  */
static int hash( char *key )
{
	int temp = 0;
 	int i = 0;
 	while ( key[i] != '\0' )
 	{
 		temp = ((temp << SHIFT) + key[i]) % SIZE;
 		++i;
 	}
	return temp;
}

/* Louden version st_insert -> ht_insert */
/* Procedure ht_insert inserts line numbers and
 * memory location into the hash table
 * loc = memory location is inserted only the
 * first time, otherwise ignored
 */
void ht_insert( char *name, int lineno, int loc, BucketList hashTable[SIZE], int key )
{
	//int h = hash(name);
	BucketList l = hashTable[key];
	while ((l != NULL) && (strcmp(name, l->name) != 0))
	{
		l = l->next;
	}

	/*  variable not yet in table  */
	if (l == NULL)
	{
		l = (BucketList) malloc(sizeof(struct BucketListRec));

		l->name = copyString(name);
		printf("Insert item l->name: %s \n", l->name);
		l->type = Void;            /* default type is Void   */
		l->const_attr_tag = 0;     /* default tag value is 0 */
		l->lines = (LineList) malloc(sizeof(struct LineListRec));
		l->lines->lineno = lineno;
		printf("Insert lineno: %d \n", l->lines->lineno);
		l->memloc = loc;
		printf("Insert memloc: %d \n", l->memloc);
		l->lines->next = NULL;
		l->next = hashTable[key];
		hashTable[key] = l;
	}

	/*  found in table, so just add line number  */
	else
	{
		LineList t = l->lines;
		while ( t->next != NULL )
		{
			t = t->next;
		}
		t->next = (LineList) malloc(sizeof(struct LineListRec));
		t->next->lineno = lineno;
		printf("Another %s lineno: %d \n", l->name, t->next->lineno);
		t->next->next = NULL;
	}
	item_transger = l;
	printf("================================================== \n");
}   /*  ht_insert  */


/* hash table lookup 
 * Louden version st_lookup -> ht_lookup 
 * Function ht_lookup returns the memory
 * location of avariable or -1 if not found
 */
int ht_lookup( char *name, BucketList hashTable[SIZE], int key )
{
	//int h = hash(name);
	BucketList l = hashTable[key];
	//BucketList l = symbolTable[h];
	while ( (l != NULL) && (strcmp(name, l->name) != 0) )
	{
		l = l->next;
	}
	if ( l == NULL ) {
		printf("Can not find same token.\n");
		return -1;
	}
	else {
		printf("Same token be foundd. \n");
		return l->memloc;
	}
}


void symtab_Mgmt(char *id)
{
	int key = hash(id);

	/*  not yet in table, so treat as new definition  */
	if (ht_lookup(id, symbolTable, key) == -1) {
		ht_insert(id, lineno, location++, symbolTable, key);
	}
	/*  already in table, so ignore location,
		add line number of use only  */
	else {
		ht_insert(id, lineno, 0, symbolTable, key);
	}
}


void littab_Mgmt(char *literal, ExpType type)
{
	int key;
	char firstChar;
	firstChar = *(literal + 1);

	/*  提取字串第一個字元作為 key 的作法
	 *
	 * 	sol 1:
	 *	char str[2] = "\0";  gives {\0, \0} 
	 *	str[0] = fgetc(fp);
	 *
	 *	sol 2:
	 *	char c = 'A';
	 *	char str1[2] = {c , '\0'};
	 *
	 *	sol 3: 
	 *	strcpy( ... , (char[2]) { (char) c, '\0' } );
	 *	The (char[2]) { (char) c, '\0' } part will temporarily generate 
	 *	null-terminated string out of a character c.
	 *	This way you could avoid creating new variables for something 
	 *	that you already have in your hands, provided that you'll 
	 *	only need that single-character string just once.
	 */
	
	/* 這裡採 sol 2: 解法 */
	char tmp[2] = {firstChar, '\0'};
	printf("First Char: %c\n", firstChar);
	printf("Const Literal: %s\n", literal);

	key = hash(tmp);
	/*  not yet in table, so treat as new definition  */
	if (ht_lookup(literal, literalTable, key) == -1) {
		ht_insert(literal, lineno, location++, literalTable, key);
		BucketList l = item_transger;
		l->type = type;
	}
	/*  already in table, so ignore location,
		add line number of use only  */
	else {
		ht_insert(literal, lineno, 0, literalTable, key);
	}
}


void symtab_type_setting(char *id, ExpType type)
{
	int key = hash(id);
	BucketList l = symbolTable[key];

	while ( (l != NULL) && (strcmp(id, l->name) != 0) )
	{
		l = l->next;
	}
	if ( l == NULL ) {
		printf("symtab_type_setting: Can not find this id. \n");
	}
	else {
		switch (type) 
		{
			case Boolean:
				l->type = Boolean;
				break;
			case Integer:
				l->type = Integer;
				break;
			case String:
				l->type = String;
				break;
			case Character:
				l->type = Character;
				break;
			default:
				printf("void symtab_type_setting(char *id, ExpType type): Undefined type.\n");
				break;
		}
	}	
}


void symtab_const_setting(char *id)
{
	int key = hash(id);
	BucketList l = symbolTable[key];

	while ( (l != NULL) && (strcmp(id, l->name) != 0) )
	{
		l = l->next;
	}
	if ( l == NULL ) {
		printf("symtab_const_setting(): Can not find this id. \n");
	}
	else {
		printf("do symtab_const_setting()\n");
		l->const_attr_tag = 1;
	}
}


int id_const_tag(char *id)
{
	int key = hash(id);
	BucketList l = symbolTable[key];

	while ( (l != NULL) && (strcmp(id, l->name) != 0) )
	{
		l = l->next;
	}
	if ( l == NULL ) {
		printf("int id_const_tag(char *id): Can not find this id. \n");
		error_signal = 1;
	}
	else {
		return l->const_attr_tag;
	}
}


ExpType id_type_lookup(char *id)
{
	int key = hash(id);
	BucketList l = symbolTable[key];

	while ( (l != NULL) && (strcmp(id, l->name) != 0) )
	{
		l = l->next;
	}
	if ( l == NULL ) {
		printf("ExpType id_type_lookup(char *id): Can not find this id. \n");
		error_signal = 1;
	}
	else {
		return l->type;
	}
}


/* Procedure printSymTab prints a formatted
 * listing of the symbol table contents
 * to the listing file
 */
void printSymTab(FILE *printFile)
{
	int i;
	char *print_str;
	//fprintf(printFile, " Identifier      Type    Const    Sequence    Line Numbers \n"); //加入印出 sequence 的版本
	//fprintf(printFile, "-------------    ----    -----    --------    ------------ \n"); **加入印出 sequence 的版本
	fprintf(printFile, " Identifier      Type    Const    Line Numbers \n"); //不印出 sequence 的版本
	fprintf(printFile, "-------------    ----    -----    ------------ \n"); //不印出 sequence 的版本

	for (i = 0; i < SIZE; ++i)
	{
		if (symbolTable[i] != NULL)
		{
			BucketList l = symbolTable[i];

			while (l != NULL)
			{
				fprintf(printFile, "%-16s ", l->name);
				switch (l->type) 
				{
					case Integer:
						print_str = "int";
						break;
					case Boolean:
						print_str ="bool";
						break;
					case Character:
						print_str = "char";
						break;
					case String:
						print_str = "str";
						break;
					default:
						break;
				}
				fprintf(printFile, "%-8s", print_str);
				if (l->const_attr_tag == 1)
					print_str = "Y";
				else 
					print_str = "N";
				fprintf(printFile, "%-9s", print_str); 
				//fprintf(printFile, "%-8d ", l->memloc);    加入印出 sequence 的版本

				LineList t = l->lines;
				while (t != NULL)
				{
					fprintf(printFile, "%-4d ", t->lineno);
					t = t->next;
				}
				fprintf(printFile, "\n");
				fprintf(printFile, "====================================================================== \n");
				
				l = l->next;
			}
		}
	}
} /*  printSymTab  */


void printLitTab(FILE *printFile)
{
	int i;
	char *print_str;

	fprintf(printFile, "            Literal               Type    Line Numbers \n"); 
	fprintf(printFile, "------------------------------    ----    ------------ \n"); 

	for (i = 0; i < SIZE; ++i)
	{
		if (literalTable[i] != NULL)
		{
			BucketList l = literalTable[i];
			
			while (l != NULL)
			{
				//fprintf(printFile, "\n");
				//fprintf(printFile, "Literal     : %s \n", l->name);
				//fprintf(printFile, "Sequence    : %d \n", l->memloc); 加入印出 sequence 的版本
				//fprintf(printFile, "Type        : %d \n", l->type);

				fprintf(printFile, "%-33s ", l->name);
				switch (l->type) 
				{
					case Integer:
						print_str = "int";
						break;
					case Boolean:
						print_str ="bool";
						break;
					case Character:
						print_str = "char";
						break;
					case String:
						print_str = "str";
						break;
					default:
						break;
				}
				fprintf(printFile, "%-8s", print_str);

				LineList t = l->lines;
				while (t != NULL)
				{
					//fprintf(printFile, "Line Numbers: %d \n", t->lineno);
					fprintf(printFile, "%-4d ", t->lineno);
					t = t->next;
				}
				fprintf(printFile, "\n");
				fprintf(printFile, "====================================================== \n");
				
				l = l->next;
			}
		}
	}
} /*  printLitTab  */


/* 幫助 GenIR 取得 literalTable 中所儲存的 Char & String */
LitTabList *get_LitTab_collection(void)
{
	int i;
	LitTabList *first = NULL, *current, *previous;
	int first_flag = 0;
	
	for (i = 0; i < SIZE; ++i)
	{
		if (literalTable[i] != NULL)
		{
			BucketList l = literalTable[i];
			while (l != NULL)
			{
				current = (LitTabList*) malloc(sizeof(LitTabList));
				current->ret_item = copyString(l->name);
				if (first_flag == 0) {
					first = current;
					first_flag = 1;
				}
				else {
					previous->next = current; 
				}
				current->next = NULL;
				previous = current;
				
				l = l->next;
			}
		}
	}
	return first;
}


