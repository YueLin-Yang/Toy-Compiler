#include <stdio.h>

#ifndef GLOBALS_H
	#define GLOBALS_H
	#include "globals.h"
#endif


void traverse(TreeNode *t, void(*preProc) (TreeNode *), void (*postProc) (TreeNode *));

void nullProc(TreeNode *t);

char *copyString(char *s); 

int justChar_notString(char *literal);

TreeNode *newStmtNode(StmtKind kind);

TreeNode *newExpNode(ExpKind kind);

void printSyntaxTree(FILE* printFile, TreeNode *syntaxTree);
