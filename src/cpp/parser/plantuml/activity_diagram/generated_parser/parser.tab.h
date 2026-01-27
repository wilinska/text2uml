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

#ifndef YY_ACTIVITY_PARSER_TAB_H_INCLUDED
# define YY_ACTIVITY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef ACTIVITYDEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define ACTIVITYDEBUG 1
#  else
#   define ACTIVITYDEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define ACTIVITYDEBUG 0
# endif /* ! defined YYDEBUG */
#endif  /* ! defined ACTIVITYDEBUG */
#if ACTIVITYDEBUG
extern int activitydebug;
#endif

/* Token kinds.  */
#ifndef ACTIVITYTOKENTYPE
# define ACTIVITYTOKENTYPE
  enum activitytokentype
  {
    ACTIVITYEMPTY = -2,
    ACTIVITYEOF = 0,               /* "end of file"  */
    ACTIVITYerror = 256,           /* error  */
    ACTIVITYUNDEF = 257,           /* "invalid token"  */
    STARTUML = 258,                /* STARTUML  */
    ENDUML = 259,                  /* ENDUML  */
    START = 260,                   /* START  */
    STOP = 261,                    /* STOP  */
    END = 262,                     /* END  */
    IF = 263,                      /* IF  */
    DETACH = 264,                  /* DETACH  */
    BREAK = 265,                   /* BREAK  */
    THEN = 266,                    /* THEN  */
    ELSE = 267,                    /* ELSE  */
    ELSEIF = 268,                  /* ELSEIF  */
    ENDIF = 269,                   /* ENDIF  */
    KILL = 270,                    /* KILL  */
    MERGE = 271,                   /* MERGE  */
    FORK = 272,                    /* FORK  */
    WHILE = 273,                   /* WHILE  */
    ENDWHILE = 274,                /* ENDWHILE  */
    IS = 275,                      /* IS  */
    SWITCH = 276,                  /* SWITCH  */
    CASE = 277,                    /* CASE  */
    REPEAT_WHILE = 278,            /* REPEAT_WHILE  */
    REPEAT = 279,                  /* REPEAT  */
    NOT = 280,                     /* NOT  */
    ENDSWITCH = 281,               /* ENDSWITCH  */
    BACKWARD = 282,                /* BACKWARD  */
    COLON = 283,                   /* COLON  */
    SEMICOLON = 284,               /* SEMICOLON  */
    ARROW = 285,                   /* ARROW  */
    FORK_AGAIN = 286,              /* FORK_AGAIN  */
    END_FORK = 287,                /* END_FORK  */
    END_MERGE = 288,               /* END_MERGE  */
    SPLIT = 289,                   /* SPLIT  */
    SPLIT_AGAIN = 290,             /* SPLIT_AGAIN  */
    END_SPLIT = 291,               /* END_SPLIT  */
    GROUP = 292,                   /* GROUP  */
    END_GROUP = 293,               /* END_GROUP  */
    PARTITION = 294,               /* PARTITION  */
    OPEN_CURLY_BRACKET = 295,      /* OPEN_CURLY_BRACKET  */
    CLOSE_CURLY_BRACKET = 296,     /* CLOSE_CURLY_BRACKET  */
    SWIMLANE = 297,                /* SWIMLANE  */
    END_REPEAT = 298,              /* END_REPEAT  */
    ID = 299,                      /* ID  */
    ACTIVITY_CONTENT = 300,        /* ACTIVITY_CONTENT  */
    BRACE_CONTENT = 301,           /* BRACE_CONTENT  */
    QUOTED_NAME = 302              /* QUOTED_NAME  */
  };
  typedef enum activitytokentype activitytoken_kind_t;
#endif

/* Value type.  */
#if ! defined ACTIVITYSTYPE && ! defined ACTIVITYSTYPE_IS_DECLARED
union ACTIVITYSTYPE
{
#line 28 "parser.y"

char *str;

#line 123 "parser.tab.h"

};
typedef union ACTIVITYSTYPE ACTIVITYSTYPE;
# define ACTIVITYSTYPE_IS_TRIVIAL 1
# define ACTIVITYSTYPE_IS_DECLARED 1
#endif


extern ACTIVITYSTYPE activitylval;


int activityparse (void);


#endif /* !YY_ACTIVITY_PARSER_TAB_H_INCLUDED  */
