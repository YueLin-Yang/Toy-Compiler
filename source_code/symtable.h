#ifndef GLOBALS_H
	#define GLOBALS_H
	#include "globals.h"
#endif

#include <stdio.h>


/* the list of line numbers of the source
 * code in which a variable is referenced
 */
typedef struct LineListRec
{
	int lineno;
	struct LineListRec *next;
} *LineList;


/* The record in the bucket lists for
 * each variable, including name,
 * assigned memory location, and
 * the list of line numbers in which
 * it appears in the source code
 */
typedef struct BucketListRec
{
	char *name;
	ExpType type;
	int const_attr_tag;
	LineList lines;
	int memloc; /*  memory location for variable  */
	struct BucketListRec *next;
} *BucketList;


typedef struct LitTabListRec
{
	char *ret_item;
	struct LitTabListRec *next;
} LitTabList;


void symtab_Mgmt(char *id);

void littab_Mgmt(char *literal, ExpType type);

void printSymTab(FILE *printFile);

void printLitTab(FILE *printFile);

void symtab_type_setting(char *id, ExpType type);

void symtab_const_setting(char *id);

int id_const_tag(char *id);

ExpType id_type_lookup(char *id);

LitTabList *get_LitTab_collection(void);
