/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INT = 258,
     ID = 259,
     S = 260,
     PRINT = 261,
     WHILE = 262,
     IF = 263,
     FOR = 264,
     DEF = 265,
     LT = 266,
     GT = 267,
     LTE = 268,
     GTE = 269,
     EQ = 270,
     NEQ = 271,
     MOD = 272,
     IFX = 273,
     ELSE = 274,
     UMINUS = 275
   };
#endif
/* Tokens.  */
#define INT 258
#define ID 259
#define S 260
#define PRINT 261
#define WHILE 262
#define IF 263
#define FOR 264
#define DEF 265
#define LT 266
#define GT 267
#define LTE 268
#define GTE 269
#define EQ 270
#define NEQ 271
#define MOD 272
#define IFX 273
#define ELSE 274
#define UMINUS 275




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 31 "batata.y"
{
  int ival; //Integer values.
  char sval; // Char values.
  char *string; //string values;

  nodeType *nPtr;


}
/* Line 1529 of yacc.c.  */
#line 99 "batata.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

