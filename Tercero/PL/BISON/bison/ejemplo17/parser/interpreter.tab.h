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
#line 138 "interpreter.y" /* yacc.c:1909  */

  char * identifier; 				 /* NEW in example 7 */
  double number;
  bool logic;						 /* NEW in example 15 */
  char * string;
  lp::ExpNode *expNode;  			 /* NEW in example 16 */
  std::list<lp::ExpNode *>  *parameters;    // New in example 16; NOTE: #include<list> must be in interpreter.l, init.cpp, interpreter.cpp
  std::list<lp::Statement *> *stmts; /* NEW in example 16 */
  lp::Statement *st;				 /* NEW in example 16 */
  lp::AST *prog;					 /* NEW in example 16 */

#line 121 "interpreter.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_INTERPRETER_TAB_H_INCLUDED  */
