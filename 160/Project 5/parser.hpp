/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
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

#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     T_NUMBER = 258,
     T_OR = 259,
     T_AND = 260,
     T_EQUALS = 261,
     T_LEQ = 262,
     T_LE = 263,
     T_MINUS = 264,
     T_PLUS = 265,
     T_DIVIDE = 266,
     T_MULTIPLY = 267,
     T_NOT = 268,
     T_FOR = 269,
     T_EQUAL = 270,
     T_IDENTIFIER = 271,
     T_TRUE = 272,
     T_FALSE = 273,
     T_NEW = 274,
     T_PRINT = 275,
     T_IF = 276,
     T_ELSE = 277,
     T_INT = 278,
     T_BOOL = 279,
     T_NONE = 280,
     T_COLON = 281,
     T_RETURN = 282,
     T_OPENBRACE = 283,
     T_CLOSEBRACE = 284,
     T_OPENBRACKET = 285,
     T_CLOSEBRACKET = 286,
     T_OPENPAREN = 287,
     T_CLOSEPAREN = 288,
     T_SEMICOLON = 289,
     T_COMMA = 290,
     T_DOT = 291
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_PARSER_HPP_INCLUDED  */
