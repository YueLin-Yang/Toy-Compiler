/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_YACC_TAB_H_INCLUDED
# define YY_YY_YACC_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    MAIN = 258,
    WHILE = 259,
    IF = 260,
    ELSE = 261,
    READ = 262,
    PRINT = 263,
    PRINTLN = 264,
    TRUE_TOKEN = 265,
    FALSE_TOKEN = 266,
    SEMICOLON = 267,
    COMMA = 268,
    BOOL_DECLAR = 269,
    CHAR_DECLAR = 270,
    CONST_DECLAR = 271,
    STR_DECLAR = 272,
    INT_DECLAR = 273,
    ID = 274,
    NUMBER = 275,
    STRING_CONST = 276,
    CHAR_CONST = 277,
    ASSIGN = 278,
    ADD = 279,
    SUB = 280,
    MUL = 281,
    DIV = 282,
    MOD = 283,
    GR = 284,
    LS = 285,
    EQ = 286,
    NOT_EQ = 287,
    GR_EQ = 288,
    LS_EQ = 289,
    L_BRACE = 290,
    R_BRACE = 291,
    L_PARENTH = 292,
    R_PARENTH = 293
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_YACC_TAB_H_INCLUDED  */
