/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    STARTUML = 258,                /* STARTUML  */
    END_UML = 259,                 /* END_UML  */
    CLASS = 260,                   /* CLASS  */
    ABSTRACT = 261,                /* ABSTRACT  */
    ABSTRACT_CLASS = 262,          /* ABSTRACT_CLASS  */
    ANNOTATION = 263,              /* ANNOTATION  */
    CIRCLE = 264,                  /* CIRCLE  */
    DIAMOND = 265,                 /* DIAMOND  */
    ENTITY = 266,                  /* ENTITY  */
    ENUM = 267,                    /* ENUM  */
    EXCEPTION = 268,               /* EXCEPTION  */
    INTERFACE = 269,               /* INTERFACE  */
    METACLASS = 270,               /* METACLASS  */
    PROTOCOL = 271,                /* PROTOCOL  */
    STEREOTYPE = 272,              /* STEREOTYPE  */
    STRUCT = 273,                  /* STRUCT  */
    COLON = 274,                   /* COLON  */
    PIPE = 275,                    /* PIPE  */
    STAR = 276,                    /* STAR  */
    O = 277,                       /* O  */
    HASH = 278,                    /* HASH  */
    X = 279,                       /* X  */
    PLUS = 280,                    /* PLUS  */
    HAT = 281,                     /* HAT  */
    HYPHEN = 282,                  /* HYPHEN  */
    L_ANGLE_BRACE = 283,           /* L_ANGLE_BRACE  */
    R_ANGLE_BRACE = 284,           /* R_ANGLE_BRACE  */
    L_SQUARE_BRACE = 285,          /* L_SQUARE_BRACE  */
    R_SQUARE_BRACE = 286,          /* R_SQUARE_BRACE  */
    L_CURLY_BRACE = 287,           /* L_CURLY_BRACE  */
    R_CURLY_BRACE = 288,           /* R_CURLY_BRACE  */
    LBRACE = 289,                  /* LBRACE  */
    RBRACE = 290,                  /* RBRACE  */
    COMMA = 291,                   /* COMMA  */
    QUOTE = 292,                   /* QUOTE  */
    AT_POSITION = 293,             /* AT_POSITION  */
    AT_POSITION_FIXED = 294,       /* AT_POSITION_FIXED  */
    SPLIT_EDGE = 295,              /* SPLIT_EDGE  */
    SKIP_LAYOUT = 296,             /* SKIP_LAYOUT  */
    DIAGRAM_TYPE = 297,            /* DIAGRAM_TYPE  */
    LAYOUT_TYPE = 298,             /* LAYOUT_TYPE  */
    EDGE_TYPE = 299,               /* EDGE_TYPE  */
    IDENTIFIER = 300,              /* IDENTIFIER  */
    LINE_LAST_IDENTIFIER = 301,    /* LINE_LAST_IDENTIFIER  */
    POSITION = 302,                /* POSITION  */
    POSITION_FIXED = 303,          /* POSITION_FIXED  */
    POSITION_ARGS = 304            /* POSITION_ARGS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 29 "parser.y"

    char *str;

#line 117 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
