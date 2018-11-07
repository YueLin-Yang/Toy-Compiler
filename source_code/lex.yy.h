#ifndef _GLOBALS_H_
#define _GLOBALS_H_
#include "globals.h"
#endif

/*  MAXTOKENLEN is the maximum size of a token  */
#define MAXTOKENLEN 60

/* lexeme of identifier or reserved word */
char tokenString[MAXTOKENLEN+1];

TokenType getToken(void);