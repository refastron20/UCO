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
#line 7 "interpreter.y" /* yacc.c:339  */

#include <iostream>
#include <string>

/*******************************************/
/* NEW in example 5 */
/* pow */
#include <math.h>
/*******************************************/

/*******************************************/
/* NEW in example 6 */
/* Use for recovery of runtime errors */
#include <setjmp.h>
#include <signal.h>
/*******************************************/

/* Error recovery functions */
#include "../error/error.hpp"

/* Macros for the screen */
#include "../includes/macros.hpp"


/*******************************************/
/*
  NEW in example 16
  AST class
  IMPORTANT: this file must be before init.hpp
*/
#include "../ast/ast.hpp"


/*******************************************/
/* NEW in example 7 */
/* Table of symbol */
#include "../table/table.hpp"
/*******************************************/

/*******************************************/
#include "../table/numericVariable.hpp"
/*******************************************/

/* NEW in example 15 */
#include "../table/logicalVariable.hpp"

/*******************************************/
/* NEW in example 11 */
#include "../table/numericConstant.hpp"
/*******************************************/

/*******************************************/
/* NEW in example 15 */
#include "../table/logicalConstant.hpp"
/*******************************************/

/*******************************************/
/* NEW in example 13 */
#include "../table/builtinParameter1.hpp"
/*******************************************/

/*******************************************/
/* NEW in example 14 */
#include "../table/builtinParameter0.hpp"
#include "../table/builtinParameter2.hpp"
/*******************************************/


/*******************************************/
/* NEW in example 10 */
#include "../table/init.hpp"
/*******************************************/

/*!
	\brief  Lexical or scanner function
	\return int
	\note   C++ requires that yylex returns an int value
	\sa     yyparser
*/
int yylex();


extern int lineNumber; //!< External line counter


/* NEW in example 15 */
extern bool interactiveMode; //!< Control the interactive mode of execution of the interpreter

/* New in example 17 */
extern int control; //!< External: to control the interactive mode in "if" and "while" sentences




/***********************************************************/
/* NEW in example 2 */
extern std::string progname; //!<  Program name
/***********************************************************/

/*******************************************/
/* NEW in example 6 */
/*
 jhmp_buf
    This is an array type capable of storing the information of a calling environment to be restored later.
   This information is filled by calling macro setjmp and can be restored by calling function longjmp.
*/
jmp_buf begin; //!<  It enables recovery of runtime errors
/*******************************************/


/*******************************************/
/* NEW in example 7 */
extern lp::Table table; //!< Extern Table of Symbols

/*******************************************/
/* NEW in example 16 */
extern lp::AST *root; //!< External root of the abstract syntax tree AST


#line 186 "interpreter.tab.c" /* yacc.c:339  */

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
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "interpreter.tab.h".  */
#ifndef YY_YY_INTERPRETER_TAB_H_INCLUDED
# define YY_YY_INTERPRETER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    SEMICOLON = 258,
    READ = 259,
    READSTRING = 260,
    WRITE = 261,
    WRITESTRING = 262,
    IF = 263,
    THEN = 264,
    ELSE = 265,
    ENDIF = 266,
    WHILE = 267,
    DO = 268,
    ENDWHILE = 269,
    REPEAT = 270,
    UNTIL = 271,
    FOR = 272,
    FROM = 273,
    TO = 274,
    STEP = 275,
    ENDFOR = 276,
    CLEAR = 277,
    PLACE = 278,
    LETFCURLYBRACKET = 279,
    RIGHTCURLYBRACKET = 280,
    ASSIGNMENT = 281,
    COMMA = 282,
    NUMBER = 283,
    STRING = 284,
    BOOL = 285,
    VARIABLE = 286,
    UNDEFINED = 287,
    CONSTANT = 288,
    BUILTIN = 289,
    OR = 290,
    AND = 291,
    GREATER_OR_EQUAL = 292,
    LESS_OR_EQUAL = 293,
    GREATER_THAN = 294,
    LESS_THAN = 295,
    EQUAL = 296,
    NOT_EQUAL = 297,
    NOT = 298,
    PLUS = 299,
    MINUS = 300,
    CONCAT = 301,
    MULTIPLICATION = 302,
    DIVISION = 303,
    MODULO = 304,
    QUOTIENT = 305,
    LPAREN = 306,
    RPAREN = 307,
    UNARY = 308,
    POWER = 309
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 138 "interpreter.y" /* yacc.c:355  */

  char * identifier; 				 /* NEW in example 7 */
  double number;
  bool logic;						 /* NEW in example 15 */
  char * string;
  lp::ExpNode *expNode;  			 /* NEW in example 16 */
  std::list<lp::ExpNode *>  *parameters;    // New in example 16; NOTE: #include<list> must be in interpreter.l, init.cpp, interpreter.cpp
  std::list<lp::Statement *> *stmts; /* NEW in example 16 */
  lp::Statement *st;				 /* NEW in example 16 */
  lp::AST *prog;					 /* NEW in example 16 */

#line 293 "interpreter.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_INTERPRETER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 310 "interpreter.tab.c" /* yacc.c:358  */

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   675

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  55
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  20
/* YYNRULES -- Number of rules.  */
#define YYNRULES  68
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  161

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   309

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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   240,   240,   254,   259,   281,   292,   297,   302,   307,
     312,   317,   323,   329,   334,   339,   344,   349,   358,   364,
     371,   378,   384,   391,   398,   406,   415,   425,   434,   445,
     455,   465,   474,   485,   492,   498,   505,   510,   516,   523,
     530,   534,   540,   546,   552,   558,   564,   569,   575,   581,
     587,   593,   600,   606,   612,   619,   666,   672,   678,   684,
     690,   696,   702,   708,   714,   724,   729,   740,   745
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SEMICOLON", "READ", "READSTRING",
  "WRITE", "WRITESTRING", "IF", "THEN", "ELSE", "ENDIF", "WHILE", "DO",
  "ENDWHILE", "REPEAT", "UNTIL", "FOR", "FROM", "TO", "STEP", "ENDFOR",
  "CLEAR", "PLACE", "LETFCURLYBRACKET", "RIGHTCURLYBRACKET", "ASSIGNMENT",
  "COMMA", "NUMBER", "STRING", "BOOL", "VARIABLE", "UNDEFINED", "CONSTANT",
  "BUILTIN", "OR", "AND", "GREATER_OR_EQUAL", "LESS_OR_EQUAL",
  "GREATER_THAN", "LESS_THAN", "EQUAL", "NOT_EQUAL", "NOT", "PLUS",
  "MINUS", "CONCAT", "MULTIPLICATION", "DIVISION", "MODULO", "QUOTIENT",
  "LPAREN", "RPAREN", "UNARY", "POWER", "$accept", "program", "stmtlist",
  "stmt", "controlSymbol", "write", "read", "writestring", "readstring",
  "if", "while", "repeat", "for", "cond", "asgn", "clear", "place", "exp",
  "listOfExp", "restOfListOfExp", YY_NULLPTR
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309
};
# endif

#define YYPACT_NINF -45

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-45)))

#define YYTABLE_NINF -3

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-3)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -45,     5,     3,   -45,   -45,   -45,   -35,   -24,   -23,    55,
     -45,   -45,   -45,   -45,   -45,    -2,    11,    22,   -45,    21,
      47,    49,    51,   -45,   -45,   -45,   -45,    52,    53,    54,
     -14,     2,    55,   -45,   -45,   -45,   -45,    29,    55,    55,
      55,    55,   566,    34,    36,   -45,    59,    55,   450,   450,
     -45,   -45,   -45,   -45,   -45,   -45,   -45,    39,    40,    41,
      44,   486,    55,    -3,    43,    43,   506,    55,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      55,    55,    55,   469,    92,    55,    89,   248,    87,   402,
      11,    22,   -45,   566,   -45,   566,   -45,   -45,   -45,   -45,
     -45,   426,    56,   -45,   585,   603,   621,   621,   621,   621,
     621,   621,   442,   442,    27,    43,    43,    43,    43,    43,
      57,   526,   -45,   -45,    36,    55,    55,    55,   -45,   -45,
     102,   -45,   186,   279,   -45,   134,   546,   426,   -45,   -45,
     -45,   -45,    55,   -45,   -45,   217,   310,    90,   -45,   -45,
     -45,   -45,    55,   341,   372,   110,   -45,   -45,   -45,   403,
     -45
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     1,     5,     6,     0,     0,     0,     0,
      18,    18,    18,    18,    38,     0,     0,     0,     4,     0,
       0,     0,     0,    12,    13,    14,    15,     0,     0,     0,
       0,     0,     0,    42,    40,    53,    54,     0,     0,     0,
       0,     0,    22,     0,     0,     3,     0,     0,     0,     0,
       8,     9,    10,    11,     7,    17,    16,     0,     0,     0,
       0,     0,    65,    64,    49,    50,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      53,    54,    35,    34,    37,    36,    20,    21,    23,    24,
      19,    67,     0,    48,    63,    62,    57,    59,    56,    58,
      60,    61,    43,    44,    41,    45,    46,    51,    47,    52,
      54,     0,     3,     3,     0,     0,     0,     0,    66,    55,
       0,    33,     0,     0,    30,     0,     0,    67,     3,     3,
      27,    29,     0,    39,    68,     0,     0,     0,     3,    25,
      28,     3,     0,     0,     0,     0,    26,    32,     3,     0,
      31
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -45,   -45,   -44,   -45,     1,   -45,   -45,   -45,   -45,   -45,
     -45,   -45,   -45,   -42,   -27,   -45,   -45,    -9,   -45,   -25
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    18,    43,    19,    20,    21,    22,    23,
      24,    25,    26,    84,    27,    28,    29,   121,   102,   128
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      42,    87,    86,    -2,     4,     3,     5,     6,     7,     8,
       9,    10,    44,    45,    46,    11,    30,    57,    12,    58,
      13,    92,    94,    61,    50,    14,    15,    31,    32,    63,
      64,    65,    66,    59,    16,    60,    17,    48,    89,    93,
      95,    75,    76,    77,    78,    79,    80,    81,    49,    47,
      51,    82,    52,   101,    53,    54,    55,    56,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,    78,    79,    80,    81,   132,   133,
      62,    82,   134,    33,    34,    83,    35,    85,    36,    37,
      88,    96,    97,    98,   145,   146,    99,    82,    38,    39,
      40,   122,   123,   151,   153,   125,    41,   154,   129,   130,
     152,   138,   144,     0,   159,     0,   135,   136,   137,     0,
       0,     0,     0,   158,     0,    67,    68,    69,    70,    71,
      72,    73,    74,   147,    75,    76,    77,    78,    79,    80,
      81,     0,     0,   155,    82,    67,    68,    69,    70,    71,
      72,    73,    74,   142,    75,    76,    77,    78,    79,    80,
      81,     0,     0,     0,    82,     0,     0,     0,     0,    67,
      68,    69,    70,    71,    72,    73,    74,     0,    75,    76,
      77,    78,    79,    80,    81,     0,     0,     4,    82,     5,
       6,     7,     8,     9,    10,     0,   139,   140,    11,     0,
       0,    12,     0,    13,     0,     0,     0,     0,    14,    15,
       0,     0,     0,     0,     0,     0,     0,    16,     4,    17,
       5,     6,     7,     8,     9,    10,     0,   148,   149,    11,
       0,     0,    12,     0,    13,     0,     0,     0,     0,    14,
      15,     0,     0,     0,     0,     0,     0,     0,    16,     4,
      17,     5,     6,     7,     8,     9,    10,     0,     0,     0,
      11,     0,     0,    12,   124,    13,     0,     0,     0,     0,
      14,    15,     0,     0,     0,     0,     0,     0,     0,    16,
       4,    17,     5,     6,     7,     8,     9,    10,     0,     0,
       0,    11,     0,   141,    12,     0,    13,     0,     0,     0,
       0,    14,    15,     0,     0,     0,     0,     0,     0,     0,
      16,     4,    17,     5,     6,     7,     8,     9,    10,     0,
       0,   150,    11,     0,     0,    12,     0,    13,     0,     0,
       0,     0,    14,    15,     0,     0,     0,     0,     0,     0,
       0,    16,     4,    17,     5,     6,     7,     8,     9,    10,
       0,     0,   156,    11,     0,     0,    12,     0,    13,     0,
       0,     0,     0,    14,    15,     0,     0,     0,     0,     0,
       0,     0,    16,     4,    17,     5,     6,     7,     8,     9,
      10,     0,     0,     0,    11,     0,     0,    12,     0,    13,
       0,     0,     0,   157,    14,    15,     0,     0,     0,     0,
       0,     0,     0,    16,     4,    17,     5,     6,     7,     8,
       9,    10,     0,     0,     0,    11,     0,     0,    12,     0,
      13,     0,     0,     0,   160,    14,    15,     0,     0,   126,
       0,     0,     0,     0,    16,     0,    17,    67,    68,    69,
      70,    71,    72,    73,    74,     0,    75,    76,    77,    78,
      79,    80,    81,   127,     0,     0,    82,     0,     0,     0,
       0,    67,    68,    69,    70,    71,    72,    73,    74,     0,
      75,    76,    77,    78,    79,    80,    81,     0,    33,    34,
      82,    90,     0,    91,    37,     0,     0,     0,    77,    78,
      79,    80,    81,    38,    39,    40,    82,    33,    34,     0,
      35,    41,   120,    37,     0,     0,     0,     0,     0,     0,
       0,     0,    38,    39,    40,     0,     0,     0,     0,     0,
      41,    67,    68,    69,    70,    71,    72,    73,    74,     0,
      75,    76,    77,    78,    79,    80,    81,     0,   100,     0,
      82,    67,    68,    69,    70,    71,    72,    73,    74,     0,
      75,    76,    77,    78,    79,    80,    81,     0,   103,     0,
      82,    67,    68,    69,    70,    71,    72,    73,    74,     0,
      75,    76,    77,    78,    79,    80,    81,     0,   131,     0,
      82,    67,    68,    69,    70,    71,    72,    73,    74,     0,
      75,    76,    77,    78,    79,    80,    81,     0,   143,     0,
      82,    67,    68,    69,    70,    71,    72,    73,    74,     0,
      75,    76,    77,    78,    79,    80,    81,     0,     0,     0,
      82,    68,    69,    70,    71,    72,    73,    74,     0,    75,
      76,    77,    78,    79,    80,    81,     0,     0,     0,    82,
      69,    70,    71,    72,    73,    74,     0,    75,    76,    77,
      78,    79,    80,    81,     0,     0,     0,    82,    -3,    -3,
      -3,    -3,    -3,    -3,     0,    75,    76,    77,    78,    79,
      80,    81,     0,     0,     0,    82
};

static const yytype_int16 yycheck[] =
{
       9,    45,    44,     0,     1,     0,     3,     4,     5,     6,
       7,     8,    11,    12,    13,    12,    51,    31,    15,    33,
      17,    48,    49,    32,     3,    22,    23,    51,    51,    38,
      39,    40,    41,    31,    31,    33,    33,    26,    47,    48,
      49,    44,    45,    46,    47,    48,    49,    50,    26,    51,
       3,    54,     3,    62,     3,     3,     3,     3,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    47,    48,    49,    50,   122,   123,
      51,    54,   124,    28,    29,    51,    31,    51,    33,    34,
      31,    52,    52,    52,   138,   139,    52,    54,    43,    44,
      45,     9,    13,    13,   148,    18,    51,   151,    52,    52,
      20,     9,   137,    -1,   158,    -1,   125,   126,   127,    -1,
      -1,    -1,    -1,    13,    -1,    35,    36,    37,    38,    39,
      40,    41,    42,   142,    44,    45,    46,    47,    48,    49,
      50,    -1,    -1,   152,    54,    35,    36,    37,    38,    39,
      40,    41,    42,    19,    44,    45,    46,    47,    48,    49,
      50,    -1,    -1,    -1,    54,    -1,    -1,    -1,    -1,    35,
      36,    37,    38,    39,    40,    41,    42,    -1,    44,    45,
      46,    47,    48,    49,    50,    -1,    -1,     1,    54,     3,
       4,     5,     6,     7,     8,    -1,    10,    11,    12,    -1,
      -1,    15,    -1,    17,    -1,    -1,    -1,    -1,    22,    23,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,     1,    33,
       3,     4,     5,     6,     7,     8,    -1,    10,    11,    12,
      -1,    -1,    15,    -1,    17,    -1,    -1,    -1,    -1,    22,
      23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,     1,
      33,     3,     4,     5,     6,     7,     8,    -1,    -1,    -1,
      12,    -1,    -1,    15,    16,    17,    -1,    -1,    -1,    -1,
      22,    23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,
       1,    33,     3,     4,     5,     6,     7,     8,    -1,    -1,
      -1,    12,    -1,    14,    15,    -1,    17,    -1,    -1,    -1,
      -1,    22,    23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      31,     1,    33,     3,     4,     5,     6,     7,     8,    -1,
      -1,    11,    12,    -1,    -1,    15,    -1,    17,    -1,    -1,
      -1,    -1,    22,    23,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    31,     1,    33,     3,     4,     5,     6,     7,     8,
      -1,    -1,    11,    12,    -1,    -1,    15,    -1,    17,    -1,
      -1,    -1,    -1,    22,    23,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    31,     1,    33,     3,     4,     5,     6,     7,
       8,    -1,    -1,    -1,    12,    -1,    -1,    15,    -1,    17,
      -1,    -1,    -1,    21,    22,    23,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    31,     1,    33,     3,     4,     5,     6,
       7,     8,    -1,    -1,    -1,    12,    -1,    -1,    15,    -1,
      17,    -1,    -1,    -1,    21,    22,    23,    -1,    -1,    27,
      -1,    -1,    -1,    -1,    31,    -1,    33,    35,    36,    37,
      38,    39,    40,    41,    42,    -1,    44,    45,    46,    47,
      48,    49,    50,    27,    -1,    -1,    54,    -1,    -1,    -1,
      -1,    35,    36,    37,    38,    39,    40,    41,    42,    -1,
      44,    45,    46,    47,    48,    49,    50,    -1,    28,    29,
      54,    31,    -1,    33,    34,    -1,    -1,    -1,    46,    47,
      48,    49,    50,    43,    44,    45,    54,    28,    29,    -1,
      31,    51,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    43,    44,    45,    -1,    -1,    -1,    -1,    -1,
      51,    35,    36,    37,    38,    39,    40,    41,    42,    -1,
      44,    45,    46,    47,    48,    49,    50,    -1,    52,    -1,
      54,    35,    36,    37,    38,    39,    40,    41,    42,    -1,
      44,    45,    46,    47,    48,    49,    50,    -1,    52,    -1,
      54,    35,    36,    37,    38,    39,    40,    41,    42,    -1,
      44,    45,    46,    47,    48,    49,    50,    -1,    52,    -1,
      54,    35,    36,    37,    38,    39,    40,    41,    42,    -1,
      44,    45,    46,    47,    48,    49,    50,    -1,    52,    -1,
      54,    35,    36,    37,    38,    39,    40,    41,    42,    -1,
      44,    45,    46,    47,    48,    49,    50,    -1,    -1,    -1,
      54,    36,    37,    38,    39,    40,    41,    42,    -1,    44,
      45,    46,    47,    48,    49,    50,    -1,    -1,    -1,    54,
      37,    38,    39,    40,    41,    42,    -1,    44,    45,    46,
      47,    48,    49,    50,    -1,    -1,    -1,    54,    37,    38,
      39,    40,    41,    42,    -1,    44,    45,    46,    47,    48,
      49,    50,    -1,    -1,    -1,    54
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    56,    57,     0,     1,     3,     4,     5,     6,     7,
       8,    12,    15,    17,    22,    23,    31,    33,    58,    60,
      61,    62,    63,    64,    65,    66,    67,    69,    70,    71,
      51,    51,    51,    28,    29,    31,    33,    34,    43,    44,
      45,    51,    72,    59,    59,    59,    59,    51,    26,    26,
       3,     3,     3,     3,     3,     3,     3,    31,    33,    31,
      33,    72,    51,    72,    72,    72,    72,    35,    36,    37,
      38,    39,    40,    41,    42,    44,    45,    46,    47,    48,
      49,    50,    54,    51,    68,    51,    68,    57,    31,    72,
      31,    33,    69,    72,    69,    72,    52,    52,    52,    52,
      52,    72,    73,    52,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      33,    72,     9,    13,    16,    18,    27,    27,    74,    52,
      52,    52,    57,    57,    68,    72,    72,    72,     9,    10,
      11,    14,    19,    52,    74,    57,    57,    72,    10,    11,
      11,    13,    20,    57,    57,    72,    11,    21,    13,    57,
      21
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    55,    56,    57,    57,    57,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    58,    59,    60,
      61,    61,    62,    63,    63,    64,    64,    64,    64,    65,
      66,    67,    67,    68,    69,    69,    69,    69,    70,    71,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    73,    73,    74,    74
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     2,     1,     2,     2,     2,
       2,     2,     1,     1,     1,     1,     2,     2,     0,     4,
       4,     4,     2,     4,     4,     8,    10,     6,     8,     6,
       5,    12,    10,     3,     3,     3,     3,     3,     1,     6,
       1,     3,     1,     3,     3,     3,     3,     3,     3,     2,
       2,     3,     3,     1,     1,     4,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     0,     2,     0,     3
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
#line 241 "interpreter.y" /* yacc.c:1646  */
    {
		    // Create a new AST
			(yyval.prog) = new lp::AST((yyvsp[0].stmts));

			// Assign the AST to the root
			root = (yyval.prog);

			// End of parsing
			//	return 1;
		  }
#line 1606 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 254 "interpreter.y" /* yacc.c:1646  */
    {
			// create a empty list of statements
			(yyval.stmts) = new std::list<lp::Statement *>();
		  }
#line 1615 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 260 "interpreter.y" /* yacc.c:1646  */
    {
			// copy up the list and add the stmt to it
			(yyval.stmts) = (yyvsp[-1].stmts);
			(yyval.stmts)->push_back((yyvsp[0].st));

			// Control the interative mode of execution of the interpreter
			if (interactiveMode == true && control == 0)
 			{
				for(std::list<lp::Statement *>::iterator it = (yyval.stmts)->begin();
						it != (yyval.stmts)->end();
						it++)
				{
					(*it)->evaluate();
					 //(*it)->print();
				}

				// Delete the AST code, because it has already run in the interactive mode.
				(yyval.stmts)->clear();
			}
		}
#line 1640 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 282 "interpreter.y" /* yacc.c:1646  */
    {
			 // just copy up the stmtlist when an error occurs
			 (yyval.stmts) = (yyvsp[-1].stmts);

			 // The previous look-ahead token ought to be discarded with `yyclearin;'
			 yyclearin;
       }
#line 1652 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 293 "interpreter.y" /* yacc.c:1646  */
    {
		// Create a new empty statement node
		(yyval.st) = new lp::EmptyStmt();
	  }
#line 1661 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 298 "interpreter.y" /* yacc.c:1646  */
    {
		// Default action
		// $$ = $1;
	  }
#line 1670 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 303 "interpreter.y" /* yacc.c:1646  */
    {
		// Default action
		// $$ = $1;
	  }
#line 1679 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 308 "interpreter.y" /* yacc.c:1646  */
    {
		// Default action
		// $$ = $1;
	  }
#line 1688 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 313 "interpreter.y" /* yacc.c:1646  */
    {
		// Default action
		// $$ = $1;
	  }
#line 1697 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 318 "interpreter.y" /* yacc.c:1646  */
    {
		// Default action
		// $$ = $1;
	  }
#line 1706 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 324 "interpreter.y" /* yacc.c:1646  */
    {
		// Default action
		// $$ = $1;
	 }
#line 1715 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 330 "interpreter.y" /* yacc.c:1646  */
    {
		// Default action
		// $$ = $1;
	 }
#line 1724 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 335 "interpreter.y" /* yacc.c:1646  */
    {
 		// Default action
 		// $$ = $1;
 	 }
#line 1733 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 340 "interpreter.y" /* yacc.c:1646  */
    {
    // Default action
 		// $$ = $1;
  }
#line 1742 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 345 "interpreter.y" /* yacc.c:1646  */
    {
    // Default action
 		// $$ = $1;
  }
#line 1751 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 350 "interpreter.y" /* yacc.c:1646  */
    {
    // Default action
 		// $$ = $1;
  }
#line 1760 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 358 "interpreter.y" /* yacc.c:1646  */
    {
			// To control the interactive mode in "if" and "while" sentences
			control++;
		}
#line 1769 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 365 "interpreter.y" /* yacc.c:1646  */
    {
			// Create a new print node
			 (yyval.st) = new lp::WriteStmt((yyvsp[-1].expNode));
		}
#line 1778 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 372 "interpreter.y" /* yacc.c:1646  */
    {
			// Create a new read node
			 (yyval.st) = new lp::ReadStmt((yyvsp[-1].identifier));
		}
#line 1787 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 379 "interpreter.y" /* yacc.c:1646  */
    {
 			execerror("Semantic error in \"read statement\": it is not allowed to modify a constant ",(yyvsp[-1].identifier));
		}
#line 1795 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 385 "interpreter.y" /* yacc.c:1646  */
    {
			// Create a new print node
			 (yyval.st) = new lp::WriteStringStmt((yyvsp[0].expNode));
		}
#line 1804 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 392 "interpreter.y" /* yacc.c:1646  */
    {
			// Create a new read node
			 (yyval.st) = new lp::ReadStringStmt((yyvsp[-1].identifier));
		}
#line 1813 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 399 "interpreter.y" /* yacc.c:1646  */
    {
 			execerror("Semantic error in \"readstring statement\": it is not allowed to modify a constant ",(yyvsp[-1].identifier));
		}
#line 1821 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 407 "interpreter.y" /* yacc.c:1646  */
    {
    // Create a new if statement node
    lp::ConstantNode *aux = new lp::ConstantNode((yyvsp[-4].identifier));
    (yyval.st) = new lp::IfStmt(aux, (yyvsp[-1].stmts));
    // To control the interactive mode
    control--;
    warning("warning: useless if:", "condition is constant");
  }
#line 1834 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 416 "interpreter.y" /* yacc.c:1646  */
    {
     lp::ConstantNode *aux = new lp::ConstantNode((yyvsp[-6].identifier));
		// Create a new if statement node
		(yyval.st) = new lp::IfStmt(aux, (yyvsp[-3].stmts), (yyvsp[-1].stmts));

		// To control the interactive mode
    control--;
    warning("warning: useless if:", "condition is constant");
  }
#line 1848 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 426 "interpreter.y" /* yacc.c:1646  */
    {
		// Create a new if statement node
		(yyval.st) = new lp::IfStmt((yyvsp[-3].expNode), (yyvsp[-1].stmts));
		// To control the interactive mode
		control--;
	}
#line 1859 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 435 "interpreter.y" /* yacc.c:1646  */
    {
		// Create a new if statement node
		(yyval.st) = new lp::IfStmt((yyvsp[-5].expNode), (yyvsp[-3].stmts), (yyvsp[-1].stmts));

		// To control the interactive mode
		control--;
	 }
#line 1871 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 446 "interpreter.y" /* yacc.c:1646  */
    {
			// Create a new while statement node
			(yyval.st) = new lp::WhileStmt((yyvsp[-3].expNode), (yyvsp[-1].stmts));

			// To control the interactive mode
			control--;
    }
#line 1883 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 456 "interpreter.y" /* yacc.c:1646  */
    {
			// Create a new repeat statement node
			(yyval.st) = new lp::RepeatStmt((yyvsp[-2].stmts), (yyvsp[0].expNode));

			// To control the interactive mode
			control--;
    }
#line 1895 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 466 "interpreter.y" /* yacc.c:1646  */
    {
			// Create a new for statement node
			(yyval.st) = new lp::ForStmt((yyvsp[-9].identifier), (yyvsp[-7].expNode), (yyvsp[-5].expNode), (yyvsp[-3].expNode), (yyvsp[-1].stmts));

			// To control the interactive mode
			control--;
    }
#line 1907 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 475 "interpreter.y" /* yacc.c:1646  */
    {
			// Create a new for statement node
			(yyval.st) = new lp::ForStmt((yyvsp[-7].identifier), (yyvsp[-5].expNode), (yyvsp[-3].expNode), (yyvsp[-1].stmts));

			// To control the interactive mode
			control--;
    }
#line 1919 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 486 "interpreter.y" /* yacc.c:1646  */
    {
			(yyval.expNode) = (yyvsp[-1].expNode);
		}
#line 1927 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 493 "interpreter.y" /* yacc.c:1646  */
    {
			// Create a new assignment node
			(yyval.st) = new lp::AssignmentStmt((yyvsp[-2].identifier), (yyvsp[0].expNode));
		}
#line 1936 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 499 "interpreter.y" /* yacc.c:1646  */
    {
			// Create a new assignment node
			(yyval.st) = new lp::AssignmentStmt((yyvsp[-2].identifier), (lp::AssignmentStmt *) (yyvsp[0].st));
		}
#line 1945 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 506 "interpreter.y" /* yacc.c:1646  */
    {
 			execerror("Semantic error in assignment: it is not allowed to modify a constant ", (yyvsp[-2].identifier));
		}
#line 1953 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 511 "interpreter.y" /* yacc.c:1646  */
    {
 			execerror("Semantic error in multiple assignment: it is not allowed to modify a constant ",(yyvsp[-2].identifier));
		}
#line 1961 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 517 "interpreter.y" /* yacc.c:1646  */
    {
			// Create a new clear node
			 (yyval.st) = new lp::ClearStmt();
		}
#line 1970 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 524 "interpreter.y" /* yacc.c:1646  */
    {
			// Create a new clear node
			 (yyval.st) = new lp::PlaceStmt((yyvsp[-3].expNode), (yyvsp[-1].expNode));
		}
#line 1979 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 531 "interpreter.y" /* yacc.c:1646  */
    {
      (yyval.expNode) = new lp::StringNode((yyvsp[0].string));
    }
#line 1987 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 535 "interpreter.y" /* yacc.c:1646  */
    {
      (yyval.expNode) = new lp::ConcatNode((yyvsp[-2].expNode), (yyvsp[0].expNode));
    }
#line 1995 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 541 "interpreter.y" /* yacc.c:1646  */
    {
			// Create a new number node
			(yyval.expNode) = new lp::NumberNode((yyvsp[0].number));
		}
#line 2004 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 547 "interpreter.y" /* yacc.c:1646  */
    {
			// Create a new plus node
			 (yyval.expNode) = new lp::PlusNode((yyvsp[-2].expNode), (yyvsp[0].expNode));
		 }
#line 2013 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 553 "interpreter.y" /* yacc.c:1646  */
    {
			// Create a new minus node
			(yyval.expNode) = new lp::MinusNode((yyvsp[-2].expNode), (yyvsp[0].expNode));
		}
#line 2022 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 559 "interpreter.y" /* yacc.c:1646  */
    {
			// Create a new multiplication node
			(yyval.expNode) = new lp::MultiplicationNode((yyvsp[-2].expNode), (yyvsp[0].expNode));
		}
#line 2031 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 565 "interpreter.y" /* yacc.c:1646  */
    {
		  // Create a new division node
		  (yyval.expNode) = new lp::DivisionNode((yyvsp[-2].expNode), (yyvsp[0].expNode));
	   }
#line 2040 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 570 "interpreter.y" /* yacc.c:1646  */
    {
		  // Create a new quotient node
		  (yyval.expNode) = new lp::QuotientNode((yyvsp[-2].expNode), (yyvsp[0].expNode));
	   }
#line 2049 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 576 "interpreter.y" /* yacc.c:1646  */
    {
		    // just copy up the expression node
			(yyval.expNode) = (yyvsp[-1].expNode);
		 }
#line 2058 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 582 "interpreter.y" /* yacc.c:1646  */
    {
		  // Create a new unary plus node
  		  (yyval.expNode) = new lp::UnaryPlusNode((yyvsp[0].expNode));
		}
#line 2067 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 588 "interpreter.y" /* yacc.c:1646  */
    {
		  // Create a new unary minus node
  		  (yyval.expNode) = new lp::UnaryMinusNode((yyvsp[0].expNode));
		}
#line 2076 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 594 "interpreter.y" /* yacc.c:1646  */
    {
		  // Create a new modulo node

		  (yyval.expNode) = new lp::ModuloNode((yyvsp[-2].expNode), (yyvsp[0].expNode));
       }
#line 2086 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 601 "interpreter.y" /* yacc.c:1646  */
    {
		  // Create a new power node
  		  (yyval.expNode) = new lp::PowerNode((yyvsp[-2].expNode), (yyvsp[0].expNode));
		}
#line 2095 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 607 "interpreter.y" /* yacc.c:1646  */
    {
		  // Create a new variable node
		  (yyval.expNode) = new lp::VariableNode((yyvsp[0].identifier));
		}
#line 2104 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 613 "interpreter.y" /* yacc.c:1646  */
    {
		  // Create a new constant node
		  (yyval.expNode) = new lp::ConstantNode((yyvsp[0].identifier));

		}
#line 2114 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 620 "interpreter.y" /* yacc.c:1646  */
    {
			// Get the identifier in the table of symbols as Builtin
			lp::Builtin *f= (lp::Builtin *) table.getSymbol((yyvsp[-3].identifier));

			// Check the number of parameters
			if (f->getNParameters() ==  (int) (yyvsp[-1].parameters)->size())
			{
				switch(f->getNParameters())
				{
					case 0:
						{
							// Create a new Builtin Function with 0 parameters node
							(yyval.expNode) = new lp::BuiltinFunctionNode_0((yyvsp[-3].identifier));
						}
						break;

					case 1:
						{
							// Get the expression from the list of expressions
							lp::ExpNode *e = (yyvsp[-1].parameters)->front();

							// Create a new Builtin Function with 1 parameter node
							(yyval.expNode) = new lp::BuiltinFunctionNode_1((yyvsp[-3].identifier),e);
						}
						break;

					case 2:
						{
							// Get the expressions from the list of expressions
							lp::ExpNode *e1 = (yyvsp[-1].parameters)->front();
							(yyvsp[-1].parameters)->pop_front();
							lp::ExpNode *e2 = (yyvsp[-1].parameters)->front();

							// Create a new Builtin Function with 2 parameters node
							(yyval.expNode) = new lp::BuiltinFunctionNode_2((yyvsp[-3].identifier),e1,e2);
						}
						break;

					default:
				  			 execerror("Syntax error: too many parameters for function ", (yyvsp[-3].identifier));
				}
			}
			else
	  			 execerror("Syntax error: incompatible number of parameters for function", (yyvsp[-3].identifier));
		}
#line 2164 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 667 "interpreter.y" /* yacc.c:1646  */
    {
		  // Create a new "greater than" node
 			(yyval.expNode) = new lp::GreaterThanNode((yyvsp[-2].expNode),(yyvsp[0].expNode));
		}
#line 2173 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 673 "interpreter.y" /* yacc.c:1646  */
    {
		  // Create a new "greater or equal" node
 			(yyval.expNode) = new lp::GreaterOrEqualNode((yyvsp[-2].expNode),(yyvsp[0].expNode));
		}
#line 2182 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 679 "interpreter.y" /* yacc.c:1646  */
    {
		  // Create a new "less than" node
 			(yyval.expNode) = new lp::LessThanNode((yyvsp[-2].expNode),(yyvsp[0].expNode));
		}
#line 2191 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 685 "interpreter.y" /* yacc.c:1646  */
    {
		  // Create a new "less or equal" node
 			(yyval.expNode) = new lp::LessOrEqualNode((yyvsp[-2].expNode),(yyvsp[0].expNode));
		}
#line 2200 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 691 "interpreter.y" /* yacc.c:1646  */
    {
		  // Create a new "equal" node
 			(yyval.expNode) = new lp::EqualNode((yyvsp[-2].expNode),(yyvsp[0].expNode));
		}
#line 2209 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 697 "interpreter.y" /* yacc.c:1646  */
    {
		  // Create a new "not equal" node
 			(yyval.expNode) = new lp::NotEqualNode((yyvsp[-2].expNode),(yyvsp[0].expNode));
		}
#line 2218 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 703 "interpreter.y" /* yacc.c:1646  */
    {
		  // Create a new "logic and" node
 			(yyval.expNode) = new lp::AndNode((yyvsp[-2].expNode),(yyvsp[0].expNode));
		}
#line 2227 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 709 "interpreter.y" /* yacc.c:1646  */
    {
		  // Create a new "logic or" node
 			(yyval.expNode) = new lp::OrNode((yyvsp[-2].expNode),(yyvsp[0].expNode));
		}
#line 2236 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 715 "interpreter.y" /* yacc.c:1646  */
    {
		  // Create a new "logic negation" node
 			(yyval.expNode) = new lp::NotNode((yyvsp[0].expNode));
		}
#line 2245 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 724 "interpreter.y" /* yacc.c:1646  */
    {
			    // Create a new list STL
				(yyval.parameters) = new std::list<lp::ExpNode *>();
			}
#line 2254 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 730 "interpreter.y" /* yacc.c:1646  */
    {
				(yyval.parameters) = (yyvsp[0].parameters);

				// Insert the expression in the list of expressions
				(yyval.parameters)->push_front((yyvsp[-1].expNode));
			}
#line 2265 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 740 "interpreter.y" /* yacc.c:1646  */
    {
			    // Create a new list STL
				(yyval.parameters) = new std::list<lp::ExpNode *>();
			}
#line 2274 "interpreter.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 746 "interpreter.y" /* yacc.c:1646  */
    {
				// Get the list of expressions
				(yyval.parameters) = (yyvsp[0].parameters);

				// Insert the expression in the list of expressions
				(yyval.parameters)->push_front((yyvsp[-1].expNode));
			}
#line 2286 "interpreter.tab.c" /* yacc.c:1646  */
    break;


#line 2290 "interpreter.tab.c" /* yacc.c:1646  */
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
#line 757 "interpreter.y" /* yacc.c:1906  */

