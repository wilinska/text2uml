/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Substitute the type names.  */
#define YYSTYPE         ACTIVITYSTYPE
/* Substitute the variable and function names.  */
#define yyparse         activityparse
#define yylex           activitylex
#define yyerror         activityerror
#define yydebug         activitydebug
#define yynerrs         activitynerrs
#define yylval          activitylval
#define yychar          activitychar

/* First part of user prologue.  */
#line 2 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdio>
#include <sstream>
#include <iostream>
#include <queue>
#include "generated_parser.hpp"


using Token = generated_parser::Token;
using TokenType = generated_parser::TokenType;

std::string RemoveLastChar(const std::string &str) {
  return str.substr(0, str.size() - 1);
}


void activityerror(const char *s);
extern int yylex();
extern FILE *activityin;

#line 103 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_STARTUML = 3,                   /* STARTUML  */
  YYSYMBOL_ENDUML = 4,                     /* ENDUML  */
  YYSYMBOL_START = 5,                      /* START  */
  YYSYMBOL_STOP = 6,                       /* STOP  */
  YYSYMBOL_END = 7,                        /* END  */
  YYSYMBOL_IF = 8,                         /* IF  */
  YYSYMBOL_DETACH = 9,                     /* DETACH  */
  YYSYMBOL_BREAK = 10,                     /* BREAK  */
  YYSYMBOL_THEN = 11,                      /* THEN  */
  YYSYMBOL_ELSE = 12,                      /* ELSE  */
  YYSYMBOL_ELSEIF = 13,                    /* ELSEIF  */
  YYSYMBOL_ENDIF = 14,                     /* ENDIF  */
  YYSYMBOL_KILL = 15,                      /* KILL  */
  YYSYMBOL_MERGE = 16,                     /* MERGE  */
  YYSYMBOL_FORK = 17,                      /* FORK  */
  YYSYMBOL_WHILE = 18,                     /* WHILE  */
  YYSYMBOL_ENDWHILE = 19,                  /* ENDWHILE  */
  YYSYMBOL_IS = 20,                        /* IS  */
  YYSYMBOL_EQUALS = 21,                    /* EQUALS  */
  YYSYMBOL_SWITCH = 22,                    /* SWITCH  */
  YYSYMBOL_CASE = 23,                      /* CASE  */
  YYSYMBOL_REPEAT_WHILE = 24,              /* REPEAT_WHILE  */
  YYSYMBOL_REPEAT = 25,                    /* REPEAT  */
  YYSYMBOL_NOT = 26,                       /* NOT  */
  YYSYMBOL_ENDSWITCH = 27,                 /* ENDSWITCH  */
  YYSYMBOL_BACKWARD = 28,                  /* BACKWARD  */
  YYSYMBOL_COLON = 29,                     /* COLON  */
  YYSYMBOL_SEMICOLON = 30,                 /* SEMICOLON  */
  YYSYMBOL_ARROW = 31,                     /* ARROW  */
  YYSYMBOL_FORK_AGAIN = 32,                /* FORK_AGAIN  */
  YYSYMBOL_END_FORK = 33,                  /* END_FORK  */
  YYSYMBOL_END_MERGE = 34,                 /* END_MERGE  */
  YYSYMBOL_SPLIT = 35,                     /* SPLIT  */
  YYSYMBOL_SPLIT_AGAIN = 36,               /* SPLIT_AGAIN  */
  YYSYMBOL_END_SPLIT = 37,                 /* END_SPLIT  */
  YYSYMBOL_GROUP = 38,                     /* GROUP  */
  YYSYMBOL_END_GROUP = 39,                 /* END_GROUP  */
  YYSYMBOL_PARTITION = 40,                 /* PARTITION  */
  YYSYMBOL_OPEN_CURLY_BRACKET = 41,        /* OPEN_CURLY_BRACKET  */
  YYSYMBOL_CLOSE_CURLY_BRACKET = 42,       /* CLOSE_CURLY_BRACKET  */
  YYSYMBOL_SWIMLANE = 43,                  /* SWIMLANE  */
  YYSYMBOL_ID = 44,                        /* ID  */
  YYSYMBOL_ACTIVITY_CONTENT = 45,          /* ACTIVITY_CONTENT  */
  YYSYMBOL_BRACE_CONTENT = 46,             /* BRACE_CONTENT  */
  YYSYMBOL_QUOTED_NAME = 47,               /* QUOTED_NAME  */
  YYSYMBOL_YYACCEPT = 48,                  /* $accept  */
  YYSYMBOL_diagram = 49,                   /* diagram  */
  YYSYMBOL_statements = 50,                /* statements  */
  YYSYMBOL_statement = 51,                 /* statement  */
  YYSYMBOL_swim_statements = 52,           /* swim_statements  */
  YYSYMBOL_then_statements = 53,           /* then_statements  */
  YYSYMBOL_else_statements = 54,           /* else_statements  */
  YYSYMBOL_if_stat = 55,                   /* if_stat  */
  YYSYMBOL_then_stat = 56,                 /* then_stat  */
  YYSYMBOL_else_stat = 57,                 /* else_stat  */
  YYSYMBOL_elseif_stat = 58,               /* elseif_stat  */
  YYSYMBOL_conditional_statement = 59,     /* conditional_statement  */
  YYSYMBOL_loop_statements_with_breaks = 60, /* loop_statements_with_breaks  */
  YYSYMBOL_while_statement = 61,           /* while_statement  */
  YYSYMBOL_repeat_statement = 62,          /* repeat_statement  */
  YYSYMBOL_endwhile_statement = 63,        /* endwhile_statement  */
  YYSYMBOL_switch_case = 64,               /* switch_case  */
  YYSYMBOL_case_statements = 65,           /* case_statements  */
  YYSYMBOL_case_statement = 66,            /* case_statement  */
  YYSYMBOL_eq = 67,                        /* eq  */
  YYSYMBOL_elseif_statements = 68,         /* elseif_statements  */
  YYSYMBOL_elseif_statement = 69,          /* elseif_statement  */
  YYSYMBOL_fork_statement = 70,            /* fork_statement  */
  YYSYMBOL_fork_statements = 71,           /* fork_statements  */
  YYSYMBOL_split_statement = 72,           /* split_statement  */
  YYSYMBOL_split_statements = 73,          /* split_statements  */
  YYSYMBOL_group_statement = 74,           /* group_statement  */
  YYSYMBOL_partition_statement = 75        /* partition_statement  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined ACTIVITYSTYPE_IS_TRIVIAL && ACTIVITYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  29
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   489

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  48
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  67
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  135

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   302


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      45,    46,    47
};

#if ACTIVITYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    38,    38,    39,    40,    44,    45,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      65,    66,    69,    70,    74,    75,    79,    80,    84,    85,
      89,    90,    94,    95,    99,   100,   104,   105,   109,   110,
     111,   112,   116,   117,   118,   119,   122,   123,   127,   131,
     132,   136,   140,   141,   146,   147,   151,   152,   157,   158,
     162,   163,   167,   168,   172,   173,   177,   181
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if ACTIVITYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "STARTUML", "ENDUML",
  "START", "STOP", "END", "IF", "DETACH", "BREAK", "THEN", "ELSE",
  "ELSEIF", "ENDIF", "KILL", "MERGE", "FORK", "WHILE", "ENDWHILE", "IS",
  "EQUALS", "SWITCH", "CASE", "REPEAT_WHILE", "REPEAT", "NOT", "ENDSWITCH",
  "BACKWARD", "COLON", "SEMICOLON", "ARROW", "FORK_AGAIN", "END_FORK",
  "END_MERGE", "SPLIT", "SPLIT_AGAIN", "END_SPLIT", "GROUP", "END_GROUP",
  "PARTITION", "OPEN_CURLY_BRACKET", "CLOSE_CURLY_BRACKET", "SWIMLANE",
  "ID", "ACTIVITY_CONTENT", "BRACE_CONTENT", "QUOTED_NAME", "$accept",
  "diagram", "statements", "statement", "swim_statements",
  "then_statements", "else_statements", "if_stat", "then_stat",
  "else_stat", "elseif_stat", "conditional_statement",
  "loop_statements_with_breaks", "while_statement", "repeat_statement",
  "endwhile_statement", "switch_case", "case_statements", "case_statement",
  "eq", "elseif_statements", "elseif_statement", "fork_statement",
  "fork_statements", "split_statement", "split_statements",
  "group_statement", "partition_statement", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-98)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      11,   129,    29,   -98,   -98,   -98,   -98,   -14,   -98,   444,
     -13,    -8,   444,   444,    -4,    -3,   444,   -98,   153,   -98,
      24,   -98,   -98,   -98,   -98,   -98,   -98,   -98,   -98,   -98,
       4,   218,   194,    20,   259,   -21,   265,   444,     5,   306,
      41,   -98,   -98,     1,   444,   -98,   -98,     3,   444,    -6,
     -11,     6,     7,    28,    20,   -98,    33,   444,   444,   -22,
     330,   444,   444,   -98,   -98,   -98,   104,   -98,   218,   -98,
     -98,    10,   444,   -98,   444,   444,   -98,   -98,    13,    32,
     265,   -98,   -98,   -98,   354,   -98,    14,    15,    50,   -98,
     444,    24,    52,   -10,   -98,   -98,    46,    -9,   444,     4,
      49,   -98,   -98,   -98,     4,    24,   -98,   395,   444,   444,
     -98,   -98,   444,   -98,    25,    30,    31,   444,   -98,   -98,
     444,   420,    46,    44,     4,   -98,   444,   -98,   -98,    35,
      38,   -98,    48,    39,   -98
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     2,     7,     8,     9,     0,    10,     0,
       0,     0,     0,     0,     0,     0,     0,    11,     0,     5,
       0,    12,    14,    15,    13,    16,    17,    18,    19,     1,
      27,     0,     0,     0,    36,     0,     0,     0,     0,    20,
       0,     3,     6,    29,     0,    52,    53,     0,     0,     0,
       0,     0,     0,     0,    49,    37,     0,     0,     0,     0,
       0,     0,     0,     4,    28,    22,     0,    26,    60,    58,
      59,    47,     0,    38,     0,     0,    48,    50,     0,     0,
      64,    63,    62,    66,     0,    21,    31,     0,     0,    23,
       0,     0,     0,    54,    61,    46,     0,     0,    51,    42,
       0,    65,    67,    30,    32,     0,    24,     0,     0,     0,
      55,    39,     0,    40,     0,     0,     0,     0,    34,    25,
      56,     0,     0,     0,    43,    33,    57,    35,    41,     0,
       0,    44,     0,     0,    45
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -98,   -98,    21,   -18,    16,   -97,   -34,   -98,   -82,    -5,
      -2,   -98,   -30,   -98,   -98,   -91,   -98,    34,   -98,   -31,
      -1,   -98,   -98,    27,   -98,    17,   -98,   -98
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,    34,    19,    40,    66,   107,    20,    44,    90,
      91,    21,    35,    22,    23,    73,    24,    53,    54,    47,
      92,    93,    25,    49,    26,    59,    27,    28
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      42,    51,    50,    87,    56,   111,   113,    57,    71,   108,
      71,   120,    81,    42,     1,    82,    42,    72,    42,   112,
     126,    42,    18,   117,    45,    46,    65,    69,    70,    29,
      31,   128,    30,    32,    36,    43,    88,    39,    33,    79,
      37,    38,    42,    52,    97,    63,    61,    64,    89,    67,
      42,    78,    74,    75,    96,    76,    95,   100,    60,    99,
     103,   104,    42,    87,    86,    71,    42,   115,   114,    68,
     129,   123,   106,   116,   133,   121,   124,   125,    85,    80,
      42,   131,    84,    39,   132,   134,   105,   109,    77,   119,
      65,   106,   110,   130,   122,    94,    98,   101,     0,    65,
       0,     0,    89,   119,     0,     0,     0,     0,    89,     4,
       5,     6,     7,     8,     0,     0,    86,    87,     0,     0,
       0,     9,    10,     0,     0,     0,    11,     0,     0,    12,
       0,     0,     0,     3,     4,     5,     6,     7,     8,    13,
       0,     0,    14,     0,    15,     0,     9,    10,     0,    17,
      88,    11,     0,     0,    12,     0,     0,    41,     4,     5,
       6,     7,     8,     0,    13,     0,     0,    14,     0,    15,
       9,    10,    16,     0,    17,    11,     0,     0,    12,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    13,     0,
       0,    14,     0,    15,     0,     0,     0,     0,    17,     4,
       5,     6,     7,     8,     0,     0,     0,     0,     0,     0,
       0,     9,    10,     0,    45,    46,    11,     0,     0,    12,
       0,     0,     0,     4,     5,     6,     7,     8,     0,    13,
       0,     0,    14,     0,    15,     9,    10,     0,     0,    17,
      11,     0,     0,    12,     0,     0,     0,     0,     0,     0,
      48,     0,     0,    13,     0,     0,    14,     0,    15,     0,
       0,     0,     0,    17,     4,     5,     6,     7,     8,    55,
       4,     5,     6,     7,     8,     0,     9,    10,     0,     0,
       0,    11,     9,    10,    12,     0,     0,    11,     0,     0,
      12,     0,     0,     0,    13,     0,     0,    14,     0,    15,
      13,    58,     0,    14,    17,    15,     0,     0,     0,     0,
      17,     4,     5,     6,     7,     8,     0,     0,     0,     0,
       0,     0,     0,     9,    10,     0,     0,     0,    11,     0,
       0,    12,     0,     0,     0,     4,     5,     6,     7,     8,
       0,    13,     0,     0,    14,     0,    15,     9,    10,    62,
       0,    17,    11,     0,     0,    12,     0,     0,     0,     4,
       5,     6,     7,     8,     0,    13,     0,     0,    14,    83,
      15,     9,    10,     0,     0,    17,    11,     0,     0,    12,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    13,
       0,     0,    14,     0,    15,     0,   102,     0,     0,    17,
       4,     5,     6,     7,     8,     0,     0,     0,     0,   118,
       0,     0,     9,    10,     0,     0,     0,    11,     0,     0,
      12,     0,     0,     0,     0,     4,     5,     6,     7,     8,
      13,     0,     0,    14,   127,    15,     0,     9,    10,     0,
      17,     0,    11,     0,     0,    12,     0,     0,     0,     4,
       5,     6,     7,     8,     0,    13,     0,     0,    14,     0,
      15,     9,    10,     0,     0,    17,    11,     0,     0,    12,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    13,
       0,     0,    14,     0,    15,     0,     0,     0,     0,    17
};

static const yytype_int8 yycheck[] =
{
      18,    32,    32,    13,    25,    96,    97,    28,    19,    91,
      19,   108,    34,    31,     3,    37,    34,    28,    36,    28,
     117,    39,     1,   105,    20,    21,    44,    33,    34,     0,
       9,   122,    46,    46,    13,    11,    46,    16,    46,    57,
      44,    44,    60,    23,    74,     4,    41,    46,    66,    46,
      68,    18,    46,    46,    72,    27,    46,    25,    37,    46,
      46,    46,    80,    13,    12,    19,    84,    18,    99,    48,
      26,    46,    90,   104,    26,   109,    46,    46,    62,    58,
      98,    46,    61,    62,    46,    46,    88,    92,    54,   107,
     108,   109,    93,   124,   112,    68,    75,    80,    -1,   117,
      -1,    -1,   120,   121,    -1,    -1,    -1,    -1,   126,     5,
       6,     7,     8,     9,    -1,    -1,    12,    13,    -1,    -1,
      -1,    17,    18,    -1,    -1,    -1,    22,    -1,    -1,    25,
      -1,    -1,    -1,     4,     5,     6,     7,     8,     9,    35,
      -1,    -1,    38,    -1,    40,    -1,    17,    18,    -1,    45,
      46,    22,    -1,    -1,    25,    -1,    -1,     4,     5,     6,
       7,     8,     9,    -1,    35,    -1,    -1,    38,    -1,    40,
      17,    18,    43,    -1,    45,    22,    -1,    -1,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,
      -1,    38,    -1,    40,    -1,    -1,    -1,    -1,    45,     5,
       6,     7,     8,     9,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    17,    18,    -1,    20,    21,    22,    -1,    -1,    25,
      -1,    -1,    -1,     5,     6,     7,     8,     9,    -1,    35,
      -1,    -1,    38,    -1,    40,    17,    18,    -1,    -1,    45,
      22,    -1,    -1,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      32,    -1,    -1,    35,    -1,    -1,    38,    -1,    40,    -1,
      -1,    -1,    -1,    45,     5,     6,     7,     8,     9,    10,
       5,     6,     7,     8,     9,    -1,    17,    18,    -1,    -1,
      -1,    22,    17,    18,    25,    -1,    -1,    22,    -1,    -1,
      25,    -1,    -1,    -1,    35,    -1,    -1,    38,    -1,    40,
      35,    36,    -1,    38,    45,    40,    -1,    -1,    -1,    -1,
      45,     5,     6,     7,     8,     9,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    17,    18,    -1,    -1,    -1,    22,    -1,
      -1,    25,    -1,    -1,    -1,     5,     6,     7,     8,     9,
      -1,    35,    -1,    -1,    38,    -1,    40,    17,    18,    43,
      -1,    45,    22,    -1,    -1,    25,    -1,    -1,    -1,     5,
       6,     7,     8,     9,    -1,    35,    -1,    -1,    38,    39,
      40,    17,    18,    -1,    -1,    45,    22,    -1,    -1,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,
      -1,    -1,    38,    -1,    40,    -1,    42,    -1,    -1,    45,
       5,     6,     7,     8,     9,    -1,    -1,    -1,    -1,    14,
      -1,    -1,    17,    18,    -1,    -1,    -1,    22,    -1,    -1,
      25,    -1,    -1,    -1,    -1,     5,     6,     7,     8,     9,
      35,    -1,    -1,    38,    14,    40,    -1,    17,    18,    -1,
      45,    -1,    22,    -1,    -1,    25,    -1,    -1,    -1,     5,
       6,     7,     8,     9,    -1,    35,    -1,    -1,    38,    -1,
      40,    17,    18,    -1,    -1,    45,    22,    -1,    -1,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,
      -1,    -1,    38,    -1,    40,    -1,    -1,    -1,    -1,    45
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    49,     4,     5,     6,     7,     8,     9,    17,
      18,    22,    25,    35,    38,    40,    43,    45,    50,    51,
      55,    59,    61,    62,    64,    70,    72,    74,    75,     0,
      46,    50,    46,    46,    50,    60,    50,    44,    44,    50,
      52,     4,    51,    11,    56,    20,    21,    67,    32,    71,
      60,    67,    23,    65,    66,    10,    25,    28,    36,    73,
      50,    41,    43,     4,    46,    51,    53,    46,    50,    33,
      34,    19,    28,    63,    46,    46,    27,    65,    18,    51,
      50,    34,    37,    39,    50,    52,    12,    13,    46,    51,
      57,    58,    68,    69,    71,    46,    51,    60,    50,    46,
      25,    73,    42,    46,    46,    58,    51,    54,    56,    57,
      68,    63,    28,    63,    67,    18,    67,    56,    14,    51,
      53,    54,    51,    46,    46,    46,    53,    14,    63,    26,
      67,    46,    46,    26,    46
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    48,    49,    49,    49,    50,    50,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      52,    52,    53,    53,    54,    54,    55,    55,    56,    56,
      57,    57,    58,    58,    59,    59,    60,    60,    61,    61,
      61,    61,    62,    62,    62,    62,    63,    63,    64,    65,
      65,    66,    67,    67,    68,    68,    69,    69,    70,    70,
      71,    71,    72,    72,    73,    73,    74,    75
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     3,     4,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     2,     1,     2,     4,     2,     2,     1,
       2,     1,     2,     4,     6,     7,     1,     2,     4,     6,
       6,     8,     5,     7,     9,    11,     2,     1,     4,     1,
       2,     3,     1,     1,     1,     2,     3,     4,     4,     4,
       2,     3,     4,     4,     2,     3,     4,     5
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = ACTIVITYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == ACTIVITYEMPTY)                                        \
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

/* Backward compatibility with an undocumented macro.
   Use ACTIVITYerror or ACTIVITYUNDEF. */
#define YYERRCODE ACTIVITYUNDEF


/* Enable debugging if requested.  */
#if ACTIVITYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
#else /* !ACTIVITYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !ACTIVITYDEBUG */


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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = ACTIVITYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == ACTIVITYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= ACTIVITYEOF)
    {
      yychar = ACTIVITYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == ACTIVITYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = ACTIVITYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = ACTIVITYEMPTY;
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
| yyreduce -- do a reduction.  |
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

#line 1325 "parser.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == ACTIVITYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= ACTIVITYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == ACTIVITYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = ACTIVITYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != ACTIVITYEMPTY)
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 185 "parser.y"


void activityerror(const char *s) {
fprintf(stderr, "Error: %s\n", s);
}

namespace generated_parser {

std::queue<Token> parse(const std::string& input) {
    ClearLogs();

    // Konwertuj std::stringbuf na FILE*
    FILE* file = fmemopen(const_cast<char*>(input.c_str()), input.size(), "r");
    if (!file) {
        perror("fmemopen");
        return {};
    }

    // Ustaw bufor jako wejście dla Flex
    activityin = file;

    int result = yyparse();
    if (result == 0) {
        std::cout << "Parsing successful!" << std::endl;
    } else {
        std::cerr << "Parsing failed!" << std::endl;
        auto logs = GetLogs();
        while (!logs.empty())
        {
          const auto token = logs.front();
          std::cerr << "Parsed token: " <<  token.type << " *" << token.name << "*" << std::endl;
          logs.pop();
        }
    }

    fclose(file); // Zamknij FILE*

    return GetLogs();
}

}
