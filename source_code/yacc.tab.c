/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 2 "yacc.y" /* yacc.c:339  */


#define YYPARSER /* distinguishes Yacc output from other code files */

#ifndef _GLOBALS_H_
	#define _GLOBALS_H_
	#include "globals.h"
#endif

#include <stdlib.h>
#include "lex.yy.h"
#include "parse.h"
#include "util.h"

#define YYSTYPE TreeNode *

static char *savedName;      /* for use in assignments */
static int savedLineNo;      /* for use in assignments */
static TreeNode *savedTree;  /* stores syntax tree for later return */

int yyerror(char * message);
static int yylex(void);


#line 91 "yacc.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "yacc.tab.h".  */
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

/* Copy the second part of user declarations.  */

#line 181 "yacc.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   139

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  39
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  71
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  135

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   293

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    41,    41,    52,    59,    91,   102,   105,   106,   109,
     117,   125,   163,   169,   174,   183,   183,   198,   203,   208,
     213,   220,   227,   232,   237,   242,   249,   258,   265,   276,
     279,   280,   281,   282,   283,   284,   303,   312,   335,   341,
     350,   357,   365,   370,   375,   380,   385,   390,   395,   402,
     405,   412,   419,   426,   433,   440,   447,   450,   457,   464,
     467,   474,   481,   488,   498,   499,   509,   521,   526,   533,
     543,   553
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "MAIN", "WHILE", "IF", "ELSE", "READ",
  "PRINT", "PRINTLN", "TRUE_TOKEN", "FALSE_TOKEN", "SEMICOLON", "COMMA",
  "BOOL_DECLAR", "CHAR_DECLAR", "CONST_DECLAR", "STR_DECLAR", "INT_DECLAR",
  "ID", "NUMBER", "STRING_CONST", "CHAR_CONST", "ASSIGN", "ADD", "SUB",
  "MUL", "DIV", "MOD", "GR", "LS", "EQ", "NOT_EQ", "GR_EQ", "LS_EQ",
  "L_BRACE", "R_BRACE", "L_PARENTH", "R_PARENTH", "$accept", "PROGRAM",
  "prog_hdr", "prog_body", "dcl_list", "dcl_stmt", "const_dcl",
  "const_list", "const_stmt", "id_assign", "$@1", "literal", "var_dcl",
  "data_type", "id_list", "stmt_list", "stmt", "assignment_stmt",
  "compound_stmt", "selection_stmt", "else_stmt", "iteration_stmt",
  "io_stmt", "null_stmt", "simple_expr", "additive_expr", "term", "factor",
  "number", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293
};
# endif

#define YYPACT_NINF -75

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-75)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       9,   -20,    21,     1,    39,   -75,   -75,   -75,   -75,    87,
     -75,   -75,    28,   -75,   -75,   -75,   -75,   -75,    74,    -3,
     -75,    -5,   -75,    54,   -75,    18,    62,    73,    75,    76,
      77,   -75,   -75,   -75,    24,   -75,   -75,   -75,   -75,   -75,
     -75,   -75,    88,   -75,    28,   -75,   -75,   -75,   -75,   -75,
     -75,    95,    96,   -75,   -75,   -75,    98,    24,    24,    74,
      35,    35,     6,   -75,    20,    33,    24,   106,    56,    70,
     -75,   -75,   -75,   -75,   -75,   -75,   -75,    81,    82,    13,
      83,    84,    85,    86,    89,    90,   -75,   -75,   -75,    91,
     -75,    24,    24,    24,    24,    24,    24,    24,    24,    24,
      24,    24,    15,    15,   113,   114,   118,   119,   120,   121,
     122,   -75,    70,    70,    38,    38,    38,    38,    38,    38,
     -75,   -75,   -75,   -75,   129,   -75,   -75,   -75,   -75,   -75,
     -75,   -75,    15,   -75,   -75
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     1,     6,     2,     3,    29,
      24,    23,     0,    25,    22,     5,     7,     8,     0,     0,
      15,     0,    11,     0,    27,     0,     0,     0,     0,     0,
       0,    49,    29,     4,     0,    28,    30,    31,    32,    33,
      34,    35,     0,     9,     0,    19,    20,    12,    71,    17,
      18,     0,     0,    13,    14,    21,     0,     0,     0,     0,
       0,     0,     0,    67,     0,     0,     0,     0,    56,    59,
      63,    68,    16,    10,    69,    70,    26,     0,     0,     0,
       0,     0,    68,     0,     0,    68,    37,    65,    66,     0,
      36,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    64,    57,    58,    52,    51,    54,    55,    53,    50,
      60,    61,    62,    41,    38,    42,    44,    43,    45,    47,
      46,    48,     0,    39,    40
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -75,   -75,   -75,   -75,   -75,   -75,   -75,   -75,    92,    -9,
     -75,    46,   -75,   -75,    78,   107,   -74,   -75,   -75,   -75,
     -75,   -75,   -75,   -75,    34,   -27,    17,   -17,   -23
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     7,     9,    15,    16,    21,    22,    34,
      42,    53,    17,    18,    25,    19,    35,    36,    37,    38,
     133,    39,    40,    41,    67,    68,    69,    70,    71
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      54,    26,    27,    23,    28,    29,    30,    43,    44,    31,
      26,    27,     1,    28,    29,    30,    20,     4,    31,    26,
      27,     5,    28,    29,    30,    20,    56,    31,   123,   124,
      55,    56,    32,    33,    20,    23,     6,    82,    85,    87,
      74,    32,    86,    63,    48,    45,    46,    20,    64,    65,
      32,   104,    88,    75,    63,    48,    49,    50,   134,    64,
      65,    66,    91,    92,    45,    46,   114,   115,   116,   117,
     118,   119,    66,    47,    48,    49,    50,     8,    51,    52,
      91,    92,   120,   121,   122,    93,    94,    95,    96,    97,
      98,    77,    78,    24,    81,    84,    99,   100,   101,    57,
      89,    10,    11,    12,    13,    14,    80,    83,   112,   113,
      58,    72,    59,    60,    61,    74,    75,    76,    90,   102,
     103,   105,   106,   107,   108,   125,   126,   109,   110,   111,
     127,   128,   129,   130,   131,   132,    73,    79,     0,    62
};

static const yytype_int16 yycheck[] =
{
      23,     4,     5,    12,     7,     8,     9,    12,    13,    12,
       4,     5,     3,     7,     8,     9,    19,    37,    12,     4,
       5,     0,     7,     8,     9,    19,    13,    12,   102,   103,
      12,    13,    35,    36,    19,    44,    35,    60,    61,    19,
      20,    35,    36,    19,    20,    10,    11,    19,    24,    25,
      35,    38,    19,    20,    19,    20,    21,    22,   132,    24,
      25,    37,    24,    25,    10,    11,    93,    94,    95,    96,
      97,    98,    37,    19,    20,    21,    22,    38,    24,    25,
      24,    25,    99,   100,   101,    29,    30,    31,    32,    33,
      34,    57,    58,    19,    60,    61,    26,    27,    28,    37,
      66,    14,    15,    16,    17,    18,    60,    61,    91,    92,
      37,    23,    37,    37,    37,    20,    20,    19,    12,    38,
      38,    38,    38,    38,    38,    12,    12,    38,    38,    38,
      12,    12,    12,    12,    12,     6,    44,    59,    -1,    32
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    40,    41,    37,     0,    35,    42,    38,    43,
      14,    15,    16,    17,    18,    44,    45,    51,    52,    54,
      19,    46,    47,    48,    19,    53,     4,     5,     7,     8,
       9,    12,    35,    36,    48,    55,    56,    57,    58,    60,
      61,    62,    49,    12,    13,    10,    11,    19,    20,    21,
      22,    24,    25,    50,    67,    12,    13,    37,    37,    37,
      37,    37,    54,    19,    24,    25,    37,    63,    64,    65,
      66,    67,    23,    47,    20,    20,    19,    63,    63,    53,
      50,    63,    67,    50,    63,    67,    36,    19,    19,    63,
      12,    24,    25,    29,    30,    31,    32,    33,    34,    26,
      27,    28,    38,    38,    38,    38,    38,    38,    38,    38,
      38,    38,    65,    65,    64,    64,    64,    64,    64,    64,
      66,    66,    66,    55,    55,    12,    12,    12,    12,    12,
      12,    12,     6,    59,    55
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    39,    40,    41,    42,    43,    43,    44,    44,    45,
      46,    46,    47,    47,    47,    49,    48,    50,    50,    50,
      50,    51,    52,    52,    52,    52,    53,    53,    54,    54,
      55,    55,    55,    55,    55,    55,    56,    57,    58,    58,
      59,    60,    61,    61,    61,    61,    61,    61,    61,    62,
      63,    63,    63,    63,    63,    63,    63,    64,    64,    64,
      65,    65,    65,    65,    66,    66,    66,    66,    66,    67,
      67,    67
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     3,     4,     2,     0,     1,     1,     3,
       3,     1,     2,     2,     2,     0,     3,     1,     1,     1,
       1,     3,     1,     1,     1,     1,     3,     1,     2,     0,
       1,     1,     1,     1,     1,     1,     3,     3,     5,     6,
       2,     5,     5,     5,     5,     5,     5,     5,     5,     1,
       3,     3,     3,     3,     3,     3,     1,     3,     3,     1,
       3,     3,     3,     1,     3,     2,     2,     1,     1,     2,
       2,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 42 "yacc.y" /* yacc.c:1646  */
    {
	                       		YYSTYPE t = (yyvsp[0]);
	                       		if (t != NULL) {
	                       			(yyvsp[-1])->sibling = (yyvsp[0]);
	                       			savedTree = (yyvsp[-1]);
	                       		}
	                       		else { savedTree = (yyvsp[-1]); }
	                       	}
#line 1360 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 53 "yacc.y" /* yacc.c:1646  */
    {
								(yyval) = newStmtNode(MainK);
								(yyval)->attr.name = copyString(tokenString);
							}
#line 1369 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 60 "yacc.y" /* yacc.c:1646  */
    {
								(yyval) = newStmtNode(PgbdK);
								(yyval)->child[0] = (yyvsp[-2]);
								(yyval)->child[1] = (yyvsp[-1]);
							}
#line 1379 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 92 "yacc.y" /* yacc.c:1646  */
    {
								YYSTYPE t = (yyvsp[-1]);
								if (t != NULL) {
									while (t->sibling != NULL)
										t = t->sibling;
									t->sibling = (yyvsp[0]);
									(yyval) = (yyvsp[-1]);
								}
								else { (yyval) = (yyvsp[0]); }
							}
#line 1394 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 102 "yacc.y" /* yacc.c:1646  */
    { (yyval) = NULL; }
#line 1400 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 105 "yacc.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1406 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 106 "yacc.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1412 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 110 "yacc.y" /* yacc.c:1646  */
    {
								(yyval) = newStmtNode(Const_dclK);
								(yyval)->attr.dcl = "const";
								(yyval)->child[0] = (yyvsp[-1]);
							}
#line 1422 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 118 "yacc.y" /* yacc.c:1646  */
    {                                                            
								YYSTYPE t = (yyvsp[-2]);                     
		                    	while (t->sibling != NULL)
		                        	t = t->sibling;
		                     	t->sibling = (yyvsp[0]);
		                     	(yyval) = (yyvsp[-2]); 
							}
#line 1434 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 125 "yacc.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1440 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 164 "yacc.y" /* yacc.c:1646  */
    {
								(yyvsp[-1])->child[1] = newExpNode(IdK);
								(yyvsp[-1])->child[1]->attr.name = copyString(tokenString);
								(yyval) = (yyvsp[-1]);	      
							}
#line 1450 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 170 "yacc.y" /* yacc.c:1646  */
    {
								(yyvsp[-1])->child[1] = (yyvsp[0]);
								(yyval) = (yyvsp[-1]);
							}
#line 1459 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 175 "yacc.y" /* yacc.c:1646  */
    {
								(yyvsp[-1])->child[1] = (yyvsp[0]);
								(yyval) = (yyvsp[-1]);
							}
#line 1468 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 183 "yacc.y" /* yacc.c:1646  */
    {	savedName = copyString(tokenString);                     
								savedLineNo = lineno; }
#line 1475 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 186 "yacc.y" /* yacc.c:1646  */
    {
								(yyval) = newStmtNode(AssignK);
								(yyval)->child[0] = newExpNode(IdK);
								(yyval)->child[0]->attr.name = savedName;
								(yyval)->child[0]->lineno = savedLineNo;

								/* 注意: 此處對宣告為 const 屬性的 ID 下標記 */  
								/* 改至 analyze.c 設定 (認為屬語意分析相關)  */ 
								/* $$->child[0]->const_attr_tag = 1;         */             
							}
#line 1490 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 199 "yacc.y" /* yacc.c:1646  */
    {
								(yyval) = newExpNode(CharStr_constK);
								(yyval)->attr.char_str_item = copyString(tokenString);
							}
#line 1499 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 204 "yacc.y" /* yacc.c:1646  */
    {
								(yyval) = newExpNode(CharStr_constK);
								(yyval)->attr.char_str_item = copyString(tokenString);
							}
#line 1508 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 209 "yacc.y" /* yacc.c:1646  */
    {
								(yyval) = newExpNode(BoolK);
								(yyval)->attr.bool_Value = 1;
							}
#line 1517 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 214 "yacc.y" /* yacc.c:1646  */
    {
								(yyval) = newExpNode(BoolK);
								(yyval)->attr.bool_Value = 0;
							}
#line 1526 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 221 "yacc.y" /* yacc.c:1646  */
    {
								(yyvsp[-2])->child[0] = (yyvsp[-1]);
								(yyval) = (yyvsp[-2]);
							}
#line 1535 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 228 "yacc.y" /* yacc.c:1646  */
    {
								(yyval) = newStmtNode(Type_dclK);
								(yyval)->attr.dcl = copyString(tokenString);
							}
#line 1544 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 233 "yacc.y" /* yacc.c:1646  */
    {
								(yyval) = newStmtNode(Type_dclK);
								(yyval)->attr.dcl = copyString(tokenString);
							}
#line 1553 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 238 "yacc.y" /* yacc.c:1646  */
    {
								(yyval) = newStmtNode(Type_dclK);
								(yyval)->attr.dcl = copyString(tokenString);
							}
#line 1562 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 243 "yacc.y" /* yacc.c:1646  */
    {
								(yyval) = newStmtNode(Type_dclK);
								(yyval)->attr.dcl = copyString(tokenString);
							}
#line 1571 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 250 "yacc.y" /* yacc.c:1646  */
    {
								YYSTYPE t = (yyvsp[-2]);
		                    	while (t->sibling != NULL)
		                        	t = t->sibling;
		                     	t->sibling = newExpNode(IdK);
		                     	t->sibling->attr.name = copyString(tokenString);
		                     	(yyval) = (yyvsp[-2]); 
							}
#line 1584 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 259 "yacc.y" /* yacc.c:1646  */
    {
								(yyval) = newExpNode(IdK);
	                   			(yyval)->attr.name = copyString(tokenString);
							}
#line 1593 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 266 "yacc.y" /* yacc.c:1646  */
    {
								YYSTYPE t = (yyvsp[-1]);
			                    if (t != NULL) { 
			                    	while (t->sibling != NULL)
			                    		t = t->sibling;
			                    	t->sibling = (yyvsp[0]);
			                     	(yyval) = (yyvsp[-1]); 
			                    }
			                    else (yyval) = (yyvsp[0]);
							}
#line 1608 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 276 "yacc.y" /* yacc.c:1646  */
    { (yyval) = NULL; }
#line 1614 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 279 "yacc.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1620 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 280 "yacc.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1626 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 281 "yacc.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1632 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 282 "yacc.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1638 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 283 "yacc.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1644 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 284 "yacc.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1650 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 304 "yacc.y" /* yacc.c:1646  */
    {
								(yyvsp[-2])->child[1] = (yyvsp[-1]);
								(yyval) = (yyvsp[-2]);                            
							}
#line 1659 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 312 "yacc.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]); }
#line 1665 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 336 "yacc.y" /* yacc.c:1646  */
    {
								(yyval) = newStmtNode(IfK);
								(yyval)->child[0] = (yyvsp[-2]);
								(yyval)->child[1] = (yyvsp[0]);
							}
#line 1675 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 342 "yacc.y" /* yacc.c:1646  */
    {
								(yyval) = newStmtNode(IfK);
								(yyval)->child[0] = (yyvsp[-3]);
								(yyval)->child[1] = (yyvsp[-1]);
								(yyval)->child[2] = (yyvsp[0]);
							}
#line 1686 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 351 "yacc.y" /* yacc.c:1646  */
    {
								(yyval) = newStmtNode(ElseK);
								(yyval)->child[0] = (yyvsp[0]);
							}
#line 1695 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 358 "yacc.y" /* yacc.c:1646  */
    {
								(yyval) = newStmtNode(WhileK);
								(yyval)->child[0] = (yyvsp[-2]);
	                   			(yyval)->child[1] = (yyvsp[0]);
							}
#line 1705 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 366 "yacc.y" /* yacc.c:1646  */
    {
								(yyval) = newStmtNode(ReadK);
								(yyval)->child[0] = (yyvsp[-2]);
							}
#line 1714 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 371 "yacc.y" /* yacc.c:1646  */
    {
								(yyval) = newStmtNode(PrintK);
								(yyval)->child[0] = (yyvsp[-2]);
							}
#line 1723 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 376 "yacc.y" /* yacc.c:1646  */
    {
								(yyval) = newStmtNode(PrintK);
								(yyval)->child[0] = (yyvsp[-2]);
							}
#line 1732 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 381 "yacc.y" /* yacc.c:1646  */
    {
								(yyval) = newStmtNode(PrintK);
								(yyval)->child[0] = (yyvsp[-2]);
							}
#line 1741 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 386 "yacc.y" /* yacc.c:1646  */
    {
								(yyval) = newStmtNode(PrintlnK);
								(yyval)->child[0] = (yyvsp[-2]);
							}
#line 1750 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 391 "yacc.y" /* yacc.c:1646  */
    {
								(yyval) = newStmtNode(PrintlnK);
								(yyval)->child[0] = (yyvsp[-2]);
							}
#line 1759 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 396 "yacc.y" /* yacc.c:1646  */
    {
								(yyval) = newStmtNode(PrintlnK);
								(yyval)->child[0] = (yyvsp[-2]);
							}
#line 1768 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 402 "yacc.y" /* yacc.c:1646  */
    { (yyval) = NULL; }
#line 1774 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 406 "yacc.y" /* yacc.c:1646  */
    {
								(yyval) = newExpNode(OpK);
	                   			(yyval)->child[0] = (yyvsp[-2]);
	                   			(yyval)->child[1] = (yyvsp[0]);
	                   			(yyval)->attr.op = LS_EQ;
							}
#line 1785 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 413 "yacc.y" /* yacc.c:1646  */
    {
								(yyval) = newExpNode(OpK);
	                   			(yyval)->child[0] = (yyvsp[-2]);
	                   			(yyval)->child[1] = (yyvsp[0]);
	                   			(yyval)->attr.op = LS;
							}
#line 1796 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 420 "yacc.y" /* yacc.c:1646  */
    {
								(yyval) = newExpNode(OpK);
	                   			(yyval)->child[0] = (yyvsp[-2]);
	                   			(yyval)->child[1] = (yyvsp[0]);
	                   			(yyval)->attr.op = GR;
							}
#line 1807 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 427 "yacc.y" /* yacc.c:1646  */
    {
								(yyval) = newExpNode(OpK);
	                   			(yyval)->child[0] = (yyvsp[-2]);
	                   			(yyval)->child[1] = (yyvsp[0]);
	                   			(yyval)->attr.op = GR_EQ;
							}
#line 1818 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 434 "yacc.y" /* yacc.c:1646  */
    {
								(yyval) = newExpNode(OpK);
	                   			(yyval)->child[0] = (yyvsp[-2]);
	                   			(yyval)->child[1] = (yyvsp[0]);
	                   			(yyval)->attr.op = EQ;
							}
#line 1829 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 441 "yacc.y" /* yacc.c:1646  */
    {
								(yyval) = newExpNode(OpK);
	                   			(yyval)->child[0] = (yyvsp[-2]);
	                   			(yyval)->child[1] = (yyvsp[0]);
	                   			(yyval)->attr.op = NOT_EQ;
							}
#line 1840 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 447 "yacc.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1846 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 451 "yacc.y" /* yacc.c:1646  */
    {
								(yyval) = newExpNode(OpK);
								(yyval)->child[0] = (yyvsp[-2]);
	                   			(yyval)->child[1] = (yyvsp[0]);
	                   			(yyval)->attr.op = ADD;
							}
#line 1857 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 458 "yacc.y" /* yacc.c:1646  */
    {
								(yyval) = newExpNode(OpK);
								(yyval)->child[0] = (yyvsp[-2]);
	                   			(yyval)->child[1] = (yyvsp[0]);
	                   			(yyval)->attr.op = SUB;
							}
#line 1868 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 464 "yacc.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1874 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 468 "yacc.y" /* yacc.c:1646  */
    {
								(yyval) = newExpNode(OpK);
	                   			(yyval)->child[0] = (yyvsp[-2]);
	                   			(yyval)->child[1] = (yyvsp[0]);
	                   			(yyval)->attr.op = MUL;
							}
#line 1885 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 475 "yacc.y" /* yacc.c:1646  */
    {
								(yyval) = newExpNode(OpK);
	                   			(yyval)->child[0] = (yyvsp[-2]);
	                   			(yyval)->child[1] = (yyvsp[0]);
	                   			(yyval)->attr.op = DIV;
							}
#line 1896 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 482 "yacc.y" /* yacc.c:1646  */
    {
								(yyval) = newExpNode(OpK);
	                   			(yyval)->child[0] = (yyvsp[-2]);
	                   			(yyval)->child[1] = (yyvsp[0]);
	                   			(yyval)->attr.op = MOD;
							}
#line 1907 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 488 "yacc.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1913 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 498 "yacc.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]); }
#line 1919 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 500 "yacc.y" /* yacc.c:1646  */
    {
								(yyval) = newExpNode(Compound_opdK);

								(yyval)->child[0] = newExpNode(OpK);
								(yyval)->child[0]->attr.op = ADD;

								(yyval)->child[1] = newExpNode(IdK);
								(yyval)->child[1]->attr.name = copyString(tokenString); 
							}
#line 1933 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 510 "yacc.y" /* yacc.c:1646  */
    {
								
								(yyval) = newExpNode(Compound_opdK);

								(yyval)->child[0] = newExpNode(OpK);
								(yyval)->child[0]->attr.op = SUB;

								(yyval)->child[1] = newExpNode(IdK);
								(yyval)->child[1]->attr.name = copyString(tokenString); 
							
							}
#line 1949 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 522 "yacc.y" /* yacc.c:1646  */
    {
								(yyval) = newExpNode(IdK);
	                   			(yyval)->attr.name = copyString(tokenString);                 /* 注意 tokenString 傳遞 */
							}
#line 1958 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 526 "yacc.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1964 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 534 "yacc.y" /* yacc.c:1646  */
    {
								(yyval) = newExpNode(Compound_opdK);

								(yyval)->child[0] = newExpNode(OpK);
								(yyval)->child[0]->attr.op = ADD;

								(yyval)->child[1] = newExpNode(NumK);
								(yyval)->child[1]->attr.val = atoi(tokenString);
							}
#line 1978 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 544 "yacc.y" /* yacc.c:1646  */
    {
								(yyval) = newExpNode(Compound_opdK);

								(yyval)->child[0] = newExpNode(OpK);
								(yyval)->child[0]->attr.op = SUB;

								(yyval)->child[1] = newExpNode(NumK);
								(yyval)->child[1]->attr.val = atoi(tokenString);
							}
#line 1992 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 554 "yacc.y" /* yacc.c:1646  */
    {
								(yyval) = newExpNode(NumK);
								(yyval)->attr.val = atoi(tokenString);                     /* 注意 tokenString 傳遞 */
							}
#line 2001 "yacc.tab.c" /* yacc.c:1646  */
    break;


#line 2005 "yacc.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 560 "yacc.y" /* yacc.c:1906  */



/* Reference COMPILER CONSTRUCTION 	Principles and Practice - Kenneth C. Louden */
int yyerror(char * message)
{ 
	fprintf(listing, "Syntax error at line %d: %s\n", lineno, message);
  	fprintf(listing, "Current token: ");
  	/* printToken(yychar, tokenString); 代處理 */ 
  	error_signal = 1;
  	printf("Yacc - Syntax error at line %d: %s\n", lineno, message);                           
  	return 0;
}


/* yylex calls getToken to make Yacc/Bison output
 * compatible with ealier versions of the TINY scanner
 */
static int yylex(void)
{ 
	printf("Yacc - Parsing to line : %d \n", lineno);
	return getToken(); 
}                                                   


TreeNode *parse(void)
{ 
	yyparse();
  	return savedTree;
}

