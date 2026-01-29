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




/* First part of user prologue.  */
#line 1 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdio>
#include <sstream>
#include <iostream>
#include <stack>
#include "generated_parser.hpp"
#include <regex>
#include <algorithm>

using Token = class_diagram::generated_parser::Token;
using TokenType = class_diagram::generated_parser::TokenType;

namespace {

std::string CleanQuotedString(std::string text) {
    if (text.empty()) return text;

    if (text.size() >= 2 && text.front() == '"' && text.back() == '"') {
        text = text.substr(1, text.size() - 2);
    }
    else {
        return text;
    }

    static const std::regex whitespace_to_space_regex("[\\t\\n\\r]+");
    text = std::regex_replace(text, whitespace_to_space_regex, " ");

    static const std::regex multiple_spaces_regex(" +");
    text = std::regex_replace(text, multiple_spaces_regex, " ");

    text.erase(0, text.find_first_not_of(" "));
    size_t last = text.find_last_not_of(" ");
    if (last != std::string::npos) {
        text.erase(last + 1);
    }

    return text;
}

std::string RemoveLastChar(const std::string &str) {
    if (str[str.size() - 1] != '\n') {
        return str;
    }
  return CleanQuotedString(str.substr(0, str.size() - 1));
}

} // namespace
std::stack<Token> logs;

void yyerror(const char *s);
extern int yylex();
extern char* yytext;
extern FILE *yyin;
extern void yyrestart(FILE* input_file);

#line 130 "parser.tab.c"

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
  YYSYMBOL_END_UML = 4,                    /* END_UML  */
  YYSYMBOL_CLASS = 5,                      /* CLASS  */
  YYSYMBOL_ABSTRACT = 6,                   /* ABSTRACT  */
  YYSYMBOL_ABSTRACT_CLASS = 7,             /* ABSTRACT_CLASS  */
  YYSYMBOL_ANNOTATION = 8,                 /* ANNOTATION  */
  YYSYMBOL_CIRCLE = 9,                     /* CIRCLE  */
  YYSYMBOL_DIAMOND = 10,                   /* DIAMOND  */
  YYSYMBOL_ENTITY = 11,                    /* ENTITY  */
  YYSYMBOL_ENUM = 12,                      /* ENUM  */
  YYSYMBOL_EXCEPTION = 13,                 /* EXCEPTION  */
  YYSYMBOL_INTERFACE = 14,                 /* INTERFACE  */
  YYSYMBOL_METACLASS = 15,                 /* METACLASS  */
  YYSYMBOL_PROTOCOL = 16,                  /* PROTOCOL  */
  YYSYMBOL_STEREOTYPE = 17,                /* STEREOTYPE  */
  YYSYMBOL_STRUCT = 18,                    /* STRUCT  */
  YYSYMBOL_COLON = 19,                     /* COLON  */
  YYSYMBOL_PIPE = 20,                      /* PIPE  */
  YYSYMBOL_STAR = 21,                      /* STAR  */
  YYSYMBOL_O = 22,                         /* O  */
  YYSYMBOL_HASH = 23,                      /* HASH  */
  YYSYMBOL_X = 24,                         /* X  */
  YYSYMBOL_PLUS = 25,                      /* PLUS  */
  YYSYMBOL_HAT = 26,                       /* HAT  */
  YYSYMBOL_HYPHEN = 27,                    /* HYPHEN  */
  YYSYMBOL_DOWN = 28,                      /* DOWN  */
  YYSYMBOL_UP = 29,                        /* UP  */
  YYSYMBOL_LEFT = 30,                      /* LEFT  */
  YYSYMBOL_RIGHT = 31,                     /* RIGHT  */
  YYSYMBOL_L_ANGLE_BRACE = 32,             /* L_ANGLE_BRACE  */
  YYSYMBOL_R_ANGLE_BRACE = 33,             /* R_ANGLE_BRACE  */
  YYSYMBOL_L_SQUARE_BRACE = 34,            /* L_SQUARE_BRACE  */
  YYSYMBOL_R_SQUARE_BRACE = 35,            /* R_SQUARE_BRACE  */
  YYSYMBOL_L_CURLY_BRACE = 36,             /* L_CURLY_BRACE  */
  YYSYMBOL_R_CURLY_BRACE = 37,             /* R_CURLY_BRACE  */
  YYSYMBOL_LBRACE = 38,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 39,                    /* RBRACE  */
  YYSYMBOL_COMMA = 40,                     /* COMMA  */
  YYSYMBOL_QUOTE = 41,                     /* QUOTE  */
  YYSYMBOL_AT_POSITION = 42,               /* AT_POSITION  */
  YYSYMBOL_AT_POSITION_FIXED = 43,         /* AT_POSITION_FIXED  */
  YYSYMBOL_SPLIT_EDGE = 44,                /* SPLIT_EDGE  */
  YYSYMBOL_SKIP_LAYOUT = 45,               /* SKIP_LAYOUT  */
  YYSYMBOL_DIAGRAM_TYPE = 46,              /* DIAGRAM_TYPE  */
  YYSYMBOL_LAYOUT_TYPE = 47,               /* LAYOUT_TYPE  */
  YYSYMBOL_EDGE_TYPE = 48,                 /* EDGE_TYPE  */
  YYSYMBOL_IDENTIFIER = 49,                /* IDENTIFIER  */
  YYSYMBOL_LINE_LAST_IDENTIFIER = 50,      /* LINE_LAST_IDENTIFIER  */
  YYSYMBOL_POSITION = 51,                  /* POSITION  */
  YYSYMBOL_POSITION_FIXED = 52,            /* POSITION_FIXED  */
  YYSYMBOL_POSITION_ARGS = 53,             /* POSITION_ARGS  */
  YYSYMBOL_START_IDENTIFIER = 54,          /* START_IDENTIFIER  */
  YYSYMBOL_ATTRIBUTE = 55,                 /* ATTRIBUTE  */
  YYSYMBOL_YYACCEPT = 56,                  /* $accept  */
  YYSYMBOL_diagram = 57,                   /* diagram  */
  YYSYMBOL_components = 58,                /* components  */
  YYSYMBOL_component = 59,                 /* component  */
  YYSYMBOL_command_line = 60,              /* command_line  */
  YYSYMBOL_ignored = 61,                   /* ignored  */
  YYSYMBOL_node_definition = 62,           /* node_definition  */
  YYSYMBOL_node_type = 63,                 /* node_type  */
  YYSYMBOL_node_body = 64,                 /* node_body  */
  YYSYMBOL_node_element = 65,              /* node_element  */
  YYSYMBOL_extensions = 66,                /* extensions  */
  YYSYMBOL_extension = 67,                 /* extension  */
  YYSYMBOL_position = 68,                  /* position  */
  YYSYMBOL_position_fixed = 69,            /* position_fixed  */
  YYSYMBOL_skip_layoutt = 70,              /* skip_layoutt  */
  YYSYMBOL_attribute = 71,                 /* attribute  */
  YYSYMBOL_method = 72,                    /* method  */
  YYSYMBOL_method_arguments = 73,          /* method_arguments  */
  YYSYMBOL_hyphen_with_direction = 74,     /* hyphen_with_direction  */
  YYSYMBOL_relationship = 75,              /* relationship  */
  YYSYMBOL_relationship_with_label = 76,   /* relationship_with_label  */
  YYSYMBOL_left_connection = 77,           /* left_connection  */
  YYSYMBOL_right_connection = 78,          /* right_connection  */
  YYSYMBOL_connection = 79,                /* connection  */
  YYSYMBOL_label = 80                      /* label  */
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
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

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
#define YYFINAL  28
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   249

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  56
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  120
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  192

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   310


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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    86,    86,    90,    91,    95,    96,    97,    98,   102,
     108,   114,   120,   124,   128,   129,   137,   142,   147,   152,
     157,   165,   169,   173,   177,   181,   185,   189,   193,   197,
     201,   205,   209,   213,   217,   221,   225,   232,   233,   237,
     238,   239,   244,   245,   249,   250,   251,   256,   264,   272,
     276,   280,   286,   292,   298,   303,   309,   314,   320,   325,
     331,   339,   346,   351,   356,   363,   370,   376,   382,   389,
     396,   402,   408,   415,   422,   428,   434,   441,   448,   453,
     458,   467,   474,   479,   485,   493,   494,   495,   496,   497,
     501,   511,   520,   529,   538,   548,   557,   566,   577,   588,
     597,   607,   619,   623,   627,   631,   635,   639,   643,   647,
     651,   655,   659,   663,   667,   671,   678,   684,   691,   697,
     702
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "STARTUML", "END_UML",
  "CLASS", "ABSTRACT", "ABSTRACT_CLASS", "ANNOTATION", "CIRCLE", "DIAMOND",
  "ENTITY", "ENUM", "EXCEPTION", "INTERFACE", "METACLASS", "PROTOCOL",
  "STEREOTYPE", "STRUCT", "COLON", "PIPE", "STAR", "O", "HASH", "X",
  "PLUS", "HAT", "HYPHEN", "DOWN", "UP", "LEFT", "RIGHT", "L_ANGLE_BRACE",
  "R_ANGLE_BRACE", "L_SQUARE_BRACE", "R_SQUARE_BRACE", "L_CURLY_BRACE",
  "R_CURLY_BRACE", "LBRACE", "RBRACE", "COMMA", "QUOTE", "AT_POSITION",
  "AT_POSITION_FIXED", "SPLIT_EDGE", "SKIP_LAYOUT", "DIAGRAM_TYPE",
  "LAYOUT_TYPE", "EDGE_TYPE", "IDENTIFIER", "LINE_LAST_IDENTIFIER",
  "POSITION", "POSITION_FIXED", "POSITION_ARGS", "START_IDENTIFIER",
  "ATTRIBUTE", "$accept", "diagram", "components", "component",
  "command_line", "ignored", "node_definition", "node_type", "node_body",
  "node_element", "extensions", "extension", "position", "position_fixed",
  "skip_layoutt", "attribute", "method", "method_arguments",
  "hyphen_with_direction", "relationship", "relationship_with_label",
  "left_connection", "right_connection", "connection", "label", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-115)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      18,    91,    23,  -115,  -115,  -115,  -115,  -115,  -115,  -115,
    -115,  -115,  -115,  -115,  -115,  -115,  -115,    11,    55,   148,
      44,    46,  -115,  -115,  -115,    43,  -115,  -115,  -115,  -115,
    -115,    25,    30,    61,    84,  -115,  -115,  -115,  -115,  -115,
    -115,  -115,  -115,   176,    93,  -115,    95,    98,  -115,  -115,
    -115,    80,    82,  -115,  -115,  -115,  -115,  -115,  -115,  -115,
    -115,  -115,   136,   124,   -17,    87,   141,  -115,  -115,   -15,
    -115,    89,  -115,   167,    97,   117,   129,  -115,   128,    -8,
    -115,    36,  -115,    94,  -115,  -115,  -115,  -115,   127,  -115,
     134,   135,  -115,   -14,  -115,   -12,  -115,   152,    39,  -115,
      41,  -115,    77,  -115,   146,   177,  -115,   128,  -115,  -115,
    -115,   -37,   193,  -115,   -24,   194,  -115,  -115,  -115,  -115,
     192,   195,  -115,  -115,   134,  -115,   134,  -115,    -2,  -115,
     -21,   196,  -115,    -4,   197,  -115,    33,   199,  -115,  -115,
    -115,  -115,  -115,   190,     8,    34,  -115,   169,    81,   166,
     198,  -115,  -115,   134,  -115,  -115,   173,   106,  -115,   175,
     114,  -115,   179,   126,  -115,  -115,   191,  -115,   181,  -115,
    -115,   183,  -115,  -115,  -115,  -115,  -115,  -115,   185,  -115,
    -115,   187,  -115,  -115,   189,   200,  -115,  -115,  -115,  -115,
    -115,  -115
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,    21,    22,    23,    24,    25,    27,    29,
      30,    31,    32,    33,    34,    35,    36,     0,     0,    14,
       0,     0,     4,     8,     5,     0,     7,     6,     1,    28,
      26,     0,     0,     0,    14,    13,    12,   110,   111,   112,
     113,   114,   115,    85,   103,   104,     0,     0,   105,     2,
       3,     0,    16,     9,    10,    11,    15,    89,    88,    86,
      87,   102,     0,     0,     0,     0,     0,   107,   108,    50,
      90,     0,   109,     0,     0,     0,     0,    20,     0,     0,
      60,     0,    51,     0,    38,    40,    41,    19,     0,   106,
       0,     0,    94,    50,    91,    50,    92,     0,     0,    58,
       0,    56,     0,    54,     0,     0,    46,    39,    43,    44,
      45,     0,     0,    59,     0,     0,    52,    17,    37,    18,
     116,   119,    98,    49,     0,    95,     0,    96,    50,    93,
       0,     0,    57,     0,     0,    55,     0,     0,    53,    47,
      48,    42,    78,    84,     0,     0,    62,     0,     0,     0,
       0,    99,   100,     0,    97,    74,     0,     0,    70,     0,
       0,    66,     0,     0,    83,    79,     0,    77,     0,    63,
      61,     0,   118,   117,   120,   101,    75,    73,     0,    71,
      69,     0,    67,    65,     0,    82,    80,    64,    76,    72,
      68,    81
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -115,  -115,  -115,   217,  -115,   207,  -115,  -115,   180,   -74,
    -115,   137,  -115,  -115,   -92,  -115,  -115,  -114,   201,  -115,
    -115,  -115,   174,   222,  -113
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,    21,    22,    23,    36,    24,    25,    83,    84,
     107,   108,   109,   110,    92,    85,    86,   144,    46,    26,
      27,    47,    71,    72,   122
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
     147,   125,   142,   127,    90,   124,    74,   126,    75,   118,
      76,   151,   143,   152,   118,   146,   156,   153,   155,   159,
      77,     1,   162,    28,    78,   143,    91,    91,   143,    91,
     111,   168,    79,    80,   171,   158,   154,    81,    82,    91,
     175,   112,   113,   178,    29,   143,   181,   165,   166,   184,
      49,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    37,    38,    39,    40,    41,
      42,    43,   161,   167,   114,    53,    44,   130,    17,   133,
      54,    45,   143,   143,    18,   115,   116,    19,   131,   132,
     134,   135,    51,    52,    30,    20,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      74,    55,    75,    61,    76,   136,    64,    74,    65,    75,
     170,    76,    62,    17,    87,    43,   137,   138,    78,    18,
     143,   117,    19,    34,    35,    78,    79,    80,    93,    94,
      20,    81,    82,    79,    80,   177,    98,    99,    81,    82,
      74,    73,    75,   180,    76,   143,    66,    37,    38,    39,
      40,    41,    42,   143,   119,   183,   100,   101,    78,    67,
     104,   105,    68,   106,    89,   143,    79,    80,   102,   103,
     123,    81,    82,   120,   121,    69,    70,    66,    37,    38,
      39,    40,    41,    42,    31,    32,    33,    34,    35,   139,
      67,   128,   129,    68,    57,    58,    59,    60,   169,   166,
     172,   173,   176,   166,   179,   166,    95,    96,   182,   166,
     186,   166,   187,   166,   188,   166,   189,   166,   190,   166,
     140,   145,   148,   149,   157,   160,   150,   163,    50,   164,
     185,    56,    48,   174,   141,    88,     0,    97,    63,   191
};

static const yytype_int16 yycheck[] =
{
     114,    93,    39,    95,    19,    19,    23,    19,    25,    83,
      27,   124,    49,   126,    88,    39,   130,    19,    39,   133,
      37,     3,   136,     0,    41,    49,    41,    41,    49,    41,
      38,   145,    49,    50,   148,    39,   128,    54,    55,    41,
     153,    49,    50,   157,    33,    49,   160,    39,    40,   163,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    21,    22,    23,    24,    25,
      26,    27,    39,    39,    38,    50,    32,    38,    32,    38,
      50,    37,    49,    49,    38,    49,    50,    41,    49,    50,
      49,    50,    49,    50,    39,    49,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      23,    50,    25,    20,    27,    38,    36,    23,    36,    25,
      39,    27,    27,    32,    37,    27,    49,    50,    41,    38,
      49,    37,    41,    49,    50,    41,    49,    50,    49,    50,
      49,    54,    55,    49,    50,    39,    49,    50,    54,    55,
      23,    27,    25,    39,    27,    49,    20,    21,    22,    23,
      24,    25,    26,    49,    37,    39,    49,    50,    41,    33,
      42,    43,    36,    45,    33,    49,    49,    50,    49,    50,
      45,    54,    55,    49,    50,    49,    50,    20,    21,    22,
      23,    24,    25,    26,    46,    47,    48,    49,    50,    53,
      33,    49,    50,    36,    28,    29,    30,    31,    39,    40,
      44,    45,    39,    40,    39,    40,    49,    50,    39,    40,
      39,    40,    39,    40,    39,    40,    39,    40,    39,    40,
      53,    38,    38,    41,    38,    38,    41,    38,    21,    49,
      49,    34,    20,    45,   107,    65,    -1,    73,    47,    49
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    57,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    32,    38,    41,
      49,    58,    59,    60,    62,    63,    75,    76,     0,    33,
      39,    46,    47,    48,    49,    50,    61,    21,    22,    23,
      24,    25,    26,    27,    32,    37,    74,    77,    79,     4,
      59,    49,    50,    50,    50,    50,    61,    28,    29,    30,
      31,    20,    27,    74,    36,    36,    20,    33,    36,    49,
      50,    78,    79,    27,    23,    25,    27,    37,    41,    49,
      50,    54,    55,    64,    65,    71,    72,    37,    64,    33,
      19,    41,    70,    49,    50,    49,    50,    78,    49,    50,
      49,    50,    49,    50,    42,    43,    45,    66,    67,    68,
      69,    38,    49,    50,    38,    49,    50,    37,    65,    37,
      49,    50,    80,    45,    19,    70,    19,    70,    49,    50,
      38,    49,    50,    38,    49,    50,    38,    49,    50,    53,
      53,    67,    39,    49,    73,    38,    39,    73,    38,    41,
      41,    80,    80,    19,    70,    39,    73,    38,    39,    73,
      38,    39,    73,    38,    49,    39,    40,    39,    73,    39,
      39,    73,    44,    45,    45,    80,    39,    39,    73,    39,
      39,    73,    39,    39,    73,    49,    39,    39,    39,    39,
      39,    49
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    56,    57,    58,    58,    59,    59,    59,    59,    60,
      60,    60,    60,    61,    61,    61,    62,    62,    62,    62,
      62,    63,    63,    63,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    63,    64,    64,    65,
      65,    65,    66,    66,    67,    67,    67,    68,    69,    70,
      70,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    73,    73,    73,    73,    74,    74,    74,    74,    74,
      75,    75,    75,    75,    75,    75,    75,    75,    76,    76,
      76,    76,    77,    77,    77,    77,    78,    78,    78,    78,
      79,    79,    79,    79,    79,    79,    80,    80,    80,    80,
      80
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     2,     1,     1,     1,     1,     1,     3,
       3,     3,     2,     1,     0,     2,     2,     5,     5,     4,
       4,     1,     1,     1,     1,     1,     2,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     2,
       1,     1,     2,     1,     1,     1,     1,     2,     2,     2,
       0,     1,     2,     3,     2,     3,     2,     3,     2,     2,
       1,     4,     3,     4,     5,     5,     4,     5,     6,     5,
       4,     5,     6,     5,     4,     5,     6,     4,     3,     4,
       5,     4,     3,     2,     1,     1,     2,     2,     2,     2,
       4,     5,     5,     6,     5,     6,     6,     7,     6,     7,
       7,     8,     2,     1,     1,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     3,     1,
       3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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

  yychar = YYEMPTY; /* Cause a token to be read.  */

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
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
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
  yychar = YYEMPTY;
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
  case 9: /* command_line: QUOTE DIAGRAM_TYPE LINE_LAST_IDENTIFIER  */
#line 103 "parser.y"
    {
        logs.push(Token{TokenType::DIAGRAM_TYPE, RemoveLastChar(std::string((yyvsp[0].str)))});
        free((yyvsp[0].str));
    }
#line 1351 "parser.tab.c"
    break;

  case 10: /* command_line: QUOTE LAYOUT_TYPE LINE_LAST_IDENTIFIER  */
#line 109 "parser.y"
    {
        logs.push(Token{TokenType::LAYOUT_TYPE, RemoveLastChar(std::string((yyvsp[0].str)))});
        free((yyvsp[0].str));
    }
#line 1360 "parser.tab.c"
    break;

  case 11: /* command_line: QUOTE EDGE_TYPE LINE_LAST_IDENTIFIER  */
#line 115 "parser.y"
    {
        logs.push(Token{TokenType::EDGE_TYPE, RemoveLastChar(std::string((yyvsp[0].str)))});
        free((yyvsp[0].str));
    }
#line 1369 "parser.tab.c"
    break;

  case 13: /* ignored: LINE_LAST_IDENTIFIER  */
#line 125 "parser.y"
    {
        free((yyvsp[0].str));
    }
#line 1377 "parser.tab.c"
    break;

  case 15: /* ignored: IDENTIFIER ignored  */
#line 130 "parser.y"
    {
        free((yyvsp[-1].str));
    }
#line 1385 "parser.tab.c"
    break;

  case 16: /* node_definition: node_type LINE_LAST_IDENTIFIER  */
#line 138 "parser.y"
    {
        logs.push(Token{TokenType::NODE_NAME, RemoveLastChar(std::string((yyvsp[0].str)))});
        free((yyvsp[0].str));
    }
#line 1394 "parser.tab.c"
    break;

  case 17: /* node_definition: node_type IDENTIFIER L_CURLY_BRACE node_body R_CURLY_BRACE  */
#line 143 "parser.y"
    {
        logs.push(Token{TokenType::NODE_NAME, CleanQuotedString(std::string((yyvsp[-3].str)))});
        free((yyvsp[-3].str));
    }
#line 1403 "parser.tab.c"
    break;

  case 18: /* node_definition: node_type LINE_LAST_IDENTIFIER L_CURLY_BRACE node_body R_CURLY_BRACE  */
#line 148 "parser.y"
    {
        logs.push(Token{TokenType::NODE_NAME, RemoveLastChar(std::string((yyvsp[-3].str)))});
        free((yyvsp[-3].str));
    }
#line 1412 "parser.tab.c"
    break;

  case 19: /* node_definition: node_type LINE_LAST_IDENTIFIER L_CURLY_BRACE R_CURLY_BRACE  */
#line 153 "parser.y"
    {
        logs.push(Token{TokenType::NODE_NAME, RemoveLastChar(std::string((yyvsp[-2].str)))});
        free((yyvsp[-2].str));
    }
#line 1421 "parser.tab.c"
    break;

  case 20: /* node_definition: node_type IDENTIFIER L_CURLY_BRACE R_CURLY_BRACE  */
#line 158 "parser.y"
    {
        logs.push(Token{TokenType::NODE_NAME, CleanQuotedString(std::string((yyvsp[-2].str)))});
        free((yyvsp[-2].str));
    }
#line 1430 "parser.tab.c"
    break;

  case 21: /* node_type: CLASS  */
#line 166 "parser.y"
    {
        logs.push(Token{TokenType::NODE_TYPE, "Class"});
    }
#line 1438 "parser.tab.c"
    break;

  case 22: /* node_type: ABSTRACT  */
#line 170 "parser.y"
    {
        logs.push(Token{TokenType::NODE_TYPE, "Abstract"});
    }
#line 1446 "parser.tab.c"
    break;

  case 23: /* node_type: ABSTRACT_CLASS  */
#line 174 "parser.y"
    {
        logs.push(Token{TokenType::NODE_TYPE, "Abstract"});
    }
#line 1454 "parser.tab.c"
    break;

  case 24: /* node_type: ANNOTATION  */
#line 178 "parser.y"
    {
        logs.push(Token{TokenType::NODE_TYPE, "Annotation"});
    }
#line 1462 "parser.tab.c"
    break;

  case 25: /* node_type: CIRCLE  */
#line 182 "parser.y"
    {
        logs.push(Token{TokenType::NODE_TYPE, "Circle"});
    }
#line 1470 "parser.tab.c"
    break;

  case 26: /* node_type: LBRACE RBRACE  */
#line 186 "parser.y"
    {
        logs.push(Token{TokenType::NODE_TYPE, "CIRCLE"});
    }
#line 1478 "parser.tab.c"
    break;

  case 27: /* node_type: DIAMOND  */
#line 190 "parser.y"
    {
        logs.push(Token{TokenType::NODE_TYPE, "Diamond"});
    }
#line 1486 "parser.tab.c"
    break;

  case 28: /* node_type: L_ANGLE_BRACE R_ANGLE_BRACE  */
#line 194 "parser.y"
    {
        logs.push(Token{TokenType::NODE_TYPE, "Diamond"});
    }
#line 1494 "parser.tab.c"
    break;

  case 29: /* node_type: ENTITY  */
#line 198 "parser.y"
    {
        logs.push(Token{TokenType::NODE_TYPE, "Entity"});
    }
#line 1502 "parser.tab.c"
    break;

  case 30: /* node_type: ENUM  */
#line 202 "parser.y"
    {
        logs.push(Token{TokenType::NODE_TYPE, "Enum"});
    }
#line 1510 "parser.tab.c"
    break;

  case 31: /* node_type: EXCEPTION  */
#line 206 "parser.y"
    {
        logs.push(Token{TokenType::NODE_TYPE, "Exception"});
    }
#line 1518 "parser.tab.c"
    break;

  case 32: /* node_type: INTERFACE  */
#line 210 "parser.y"
    {
        logs.push(Token{TokenType::NODE_TYPE, "Interface"});
    }
#line 1526 "parser.tab.c"
    break;

  case 33: /* node_type: METACLASS  */
#line 214 "parser.y"
    {
        logs.push(Token{TokenType::NODE_TYPE, "Metaclass"});
    }
#line 1534 "parser.tab.c"
    break;

  case 34: /* node_type: PROTOCOL  */
#line 218 "parser.y"
    {
        logs.push(Token{TokenType::NODE_TYPE, "Protocol"});
    }
#line 1542 "parser.tab.c"
    break;

  case 35: /* node_type: STEREOTYPE  */
#line 222 "parser.y"
    {
        logs.push(Token{TokenType::NODE_TYPE, "Stereotype"});
    }
#line 1550 "parser.tab.c"
    break;

  case 36: /* node_type: STRUCT  */
#line 226 "parser.y"
    {
        logs.push(Token{TokenType::NODE_TYPE, "Struct"});
    }
#line 1558 "parser.tab.c"
    break;

  case 46: /* extension: SKIP_LAYOUT  */
#line 251 "parser.y"
                  {
        logs.push(Token{TokenType::SKIP_LAYOUT, std::string("")});
    }
#line 1566 "parser.tab.c"
    break;

  case 47: /* position: AT_POSITION POSITION_ARGS  */
#line 257 "parser.y"
    {
        logs.push(Token{TokenType::POSITION, std::string((yyvsp[0].str))});
        free((yyvsp[0].str));
    }
#line 1575 "parser.tab.c"
    break;

  case 48: /* position_fixed: AT_POSITION_FIXED POSITION_ARGS  */
#line 265 "parser.y"
    {
        logs.push(Token{TokenType::POSITION_FIXED, std::string((yyvsp[0].str))});
        free((yyvsp[0].str));
    }
#line 1584 "parser.tab.c"
    break;

  case 49: /* skip_layoutt: QUOTE SKIP_LAYOUT  */
#line 273 "parser.y"
    {
        logs.push(Token{TokenType::SKIP_LAYOUT, std::string("")});
    }
#line 1592 "parser.tab.c"
    break;

  case 51: /* attribute: ATTRIBUTE  */
#line 281 "parser.y"
    {
        logs.push(Token{TokenType::ATTRIBUTE, RemoveLastChar(std::string((yyvsp[0].str)))});
        free((yyvsp[0].str));
    }
#line 1601 "parser.tab.c"
    break;

  case 52: /* attribute: START_IDENTIFIER LINE_LAST_IDENTIFIER  */
#line 287 "parser.y"
    {
        logs.push(Token{TokenType::ATTRIBUTE, std::string((yyvsp[-1].str)) + " " + RemoveLastChar(std::string((yyvsp[0].str)))});
        free((yyvsp[-1].str));
        free((yyvsp[0].str));
    }
#line 1611 "parser.tab.c"
    break;

  case 53: /* attribute: HYPHEN IDENTIFIER LINE_LAST_IDENTIFIER  */
#line 293 "parser.y"
    {
        logs.push(Token{TokenType::ATTRIBUTE, "- " + std::string((yyvsp[-1].str)) + " " + RemoveLastChar(std::string((yyvsp[0].str)))});
        free((yyvsp[-1].str));
        free((yyvsp[0].str));
    }
#line 1621 "parser.tab.c"
    break;

  case 54: /* attribute: HYPHEN LINE_LAST_IDENTIFIER  */
#line 299 "parser.y"
    {
        logs.push(Token{TokenType::ATTRIBUTE, "- " + RemoveLastChar(std::string((yyvsp[0].str)))});
        free((yyvsp[0].str));
    }
#line 1630 "parser.tab.c"
    break;

  case 55: /* attribute: PLUS IDENTIFIER LINE_LAST_IDENTIFIER  */
#line 304 "parser.y"
    {
        logs.push(Token{TokenType::ATTRIBUTE, "+ " + CleanQuotedString(std::string((yyvsp[-1].str))) + " " + RemoveLastChar(std::string((yyvsp[0].str)))});
        free((yyvsp[-1].str));
        free((yyvsp[0].str));
    }
#line 1640 "parser.tab.c"
    break;

  case 56: /* attribute: PLUS LINE_LAST_IDENTIFIER  */
#line 310 "parser.y"
    {
        logs.push(Token{TokenType::ATTRIBUTE, "+ " + RemoveLastChar(std::string((yyvsp[0].str)))});
        free((yyvsp[0].str));
    }
#line 1649 "parser.tab.c"
    break;

  case 57: /* attribute: HASH IDENTIFIER LINE_LAST_IDENTIFIER  */
#line 315 "parser.y"
    {
        logs.push(Token{TokenType::ATTRIBUTE, "# " + CleanQuotedString(std::string((yyvsp[-1].str))) + " " + RemoveLastChar(std::string((yyvsp[0].str)))});
        free((yyvsp[-1].str));
        free((yyvsp[0].str));
    }
#line 1659 "parser.tab.c"
    break;

  case 58: /* attribute: HASH LINE_LAST_IDENTIFIER  */
#line 321 "parser.y"
    {
        logs.push(Token{TokenType::ATTRIBUTE, "# " + RemoveLastChar(std::string((yyvsp[0].str)))});
        free((yyvsp[0].str));
    }
#line 1668 "parser.tab.c"
    break;

  case 59: /* attribute: IDENTIFIER LINE_LAST_IDENTIFIER  */
#line 326 "parser.y"
    {
        logs.push(Token{TokenType::ATTRIBUTE, CleanQuotedString(std::string((yyvsp[-1].str))) + " " + RemoveLastChar(std::string((yyvsp[0].str)))});
        free((yyvsp[-1].str));
        free((yyvsp[0].str));
    }
#line 1678 "parser.tab.c"
    break;

  case 60: /* attribute: LINE_LAST_IDENTIFIER  */
#line 332 "parser.y"
    {
        logs.push(Token{TokenType::ATTRIBUTE, RemoveLastChar(std::string((yyvsp[0].str)))});
        free((yyvsp[0].str));
    }
#line 1687 "parser.tab.c"
    break;

  case 61: /* method: START_IDENTIFIER IDENTIFIER LBRACE RBRACE  */
#line 340 "parser.y"
    {
        logs.push(Token{TokenType::METHOD, std::string((yyvsp[-3].str)) + " " + CleanQuotedString(std::string((yyvsp[-2].str)))});
        free((yyvsp[-3].str));
        free((yyvsp[-2].str));
    }
#line 1697 "parser.tab.c"
    break;

  case 62: /* method: START_IDENTIFIER LBRACE RBRACE  */
#line 347 "parser.y"
    {
        logs.push(Token{TokenType::METHOD, std::string((yyvsp[-2].str))});
        free((yyvsp[-2].str));
    }
#line 1706 "parser.tab.c"
    break;

  case 63: /* method: START_IDENTIFIER LBRACE method_arguments RBRACE  */
#line 352 "parser.y"
    {
        logs.push(Token{TokenType::METHOD, std::string((yyvsp[-3].str))});
        free((yyvsp[-3].str));
    }
#line 1715 "parser.tab.c"
    break;

  case 64: /* method: START_IDENTIFIER IDENTIFIER LBRACE method_arguments RBRACE  */
#line 357 "parser.y"
    {
        logs.push(Token{TokenType::METHOD, std::string((yyvsp[-4].str)) + " " + CleanQuotedString(std::string((yyvsp[-3].str)))});
        free((yyvsp[-4].str));
        free((yyvsp[-3].str));
    }
#line 1725 "parser.tab.c"
    break;

  case 65: /* method: HYPHEN IDENTIFIER IDENTIFIER LBRACE RBRACE  */
#line 364 "parser.y"
    {
        logs.push(Token{TokenType::METHOD, "- " + CleanQuotedString(std::string((yyvsp[-3].str))) + " " + CleanQuotedString(std::string((yyvsp[-2].str)))});
        free((yyvsp[-3].str));
        free((yyvsp[-2].str));
    }
#line 1735 "parser.tab.c"
    break;

  case 66: /* method: HYPHEN IDENTIFIER LBRACE RBRACE  */
#line 371 "parser.y"
    {
        logs.push(Token{TokenType::METHOD, "- " + CleanQuotedString(std::string((yyvsp[-2].str)))});
        free((yyvsp[-2].str));
    }
#line 1744 "parser.tab.c"
    break;

  case 67: /* method: HYPHEN IDENTIFIER LBRACE method_arguments RBRACE  */
#line 377 "parser.y"
    {
        logs.push(Token{TokenType::METHOD, "- " + CleanQuotedString(std::string((yyvsp[-3].str)))});
        free((yyvsp[-3].str));
    }
#line 1753 "parser.tab.c"
    break;

  case 68: /* method: HYPHEN IDENTIFIER IDENTIFIER LBRACE method_arguments RBRACE  */
#line 383 "parser.y"
    {
        logs.push(Token{TokenType::METHOD, "- " + CleanQuotedString(std::string((yyvsp[-4].str))) + " " + CleanQuotedString(std::string((yyvsp[-3].str)))});
        free((yyvsp[-4].str));
        free((yyvsp[-3].str));
    }
#line 1763 "parser.tab.c"
    break;

  case 69: /* method: PLUS IDENTIFIER IDENTIFIER LBRACE RBRACE  */
#line 390 "parser.y"
    {
        logs.push(Token{TokenType::METHOD, "+ " + CleanQuotedString(std::string((yyvsp[-3].str))) + " " + CleanQuotedString(std::string((yyvsp[-2].str)))});
        free((yyvsp[-3].str));
        free((yyvsp[-2].str));
    }
#line 1773 "parser.tab.c"
    break;

  case 70: /* method: PLUS IDENTIFIER LBRACE RBRACE  */
#line 397 "parser.y"
    {
        logs.push(Token{TokenType::METHOD, "+ " + CleanQuotedString(std::string((yyvsp[-2].str)))});
        free((yyvsp[-2].str));
    }
#line 1782 "parser.tab.c"
    break;

  case 71: /* method: PLUS IDENTIFIER LBRACE method_arguments RBRACE  */
#line 403 "parser.y"
    {
        logs.push(Token{TokenType::METHOD, "+ " + CleanQuotedString(std::string((yyvsp[-3].str)))});
        free((yyvsp[-3].str));
    }
#line 1791 "parser.tab.c"
    break;

  case 72: /* method: PLUS IDENTIFIER IDENTIFIER LBRACE method_arguments RBRACE  */
#line 409 "parser.y"
    {
        logs.push(Token{TokenType::METHOD, "+ " + CleanQuotedString(std::string((yyvsp[-4].str))) + " " + CleanQuotedString(std::string((yyvsp[-3].str)))});
        free((yyvsp[-4].str));
        free((yyvsp[-3].str));
    }
#line 1801 "parser.tab.c"
    break;

  case 73: /* method: HASH IDENTIFIER IDENTIFIER LBRACE RBRACE  */
#line 416 "parser.y"
    {
        logs.push(Token{TokenType::METHOD, "# " + CleanQuotedString(std::string((yyvsp[-3].str))) + " " + CleanQuotedString(std::string((yyvsp[-2].str)))});
        free((yyvsp[-3].str));
        free((yyvsp[-2].str));
    }
#line 1811 "parser.tab.c"
    break;

  case 74: /* method: HASH IDENTIFIER LBRACE RBRACE  */
#line 423 "parser.y"
    {
        logs.push(Token{TokenType::METHOD, "# " + CleanQuotedString(std::string((yyvsp[-2].str)))});
        free((yyvsp[-2].str));
    }
#line 1820 "parser.tab.c"
    break;

  case 75: /* method: HASH IDENTIFIER LBRACE method_arguments RBRACE  */
#line 429 "parser.y"
    {
        logs.push(Token{TokenType::METHOD, "# " + CleanQuotedString(std::string((yyvsp[-3].str)))});
        free((yyvsp[-3].str));
    }
#line 1829 "parser.tab.c"
    break;

  case 76: /* method: HASH IDENTIFIER IDENTIFIER LBRACE method_arguments RBRACE  */
#line 435 "parser.y"
    {
        logs.push(Token{TokenType::METHOD, "# " + CleanQuotedString(std::string((yyvsp[-4].str))) + " " + CleanQuotedString(std::string((yyvsp[-3].str)))});
        free((yyvsp[-4].str));
        free((yyvsp[-3].str));
    }
#line 1839 "parser.tab.c"
    break;

  case 77: /* method: IDENTIFIER IDENTIFIER LBRACE RBRACE  */
#line 442 "parser.y"
    {
        logs.push(Token{TokenType::METHOD, CleanQuotedString(std::string((yyvsp[-3].str))) + " " + CleanQuotedString(std::string((yyvsp[-2].str)))});
        free((yyvsp[-3].str));
        free((yyvsp[-2].str));
    }
#line 1849 "parser.tab.c"
    break;

  case 78: /* method: IDENTIFIER LBRACE RBRACE  */
#line 449 "parser.y"
    {
        logs.push(Token{TokenType::METHOD, CleanQuotedString(std::string((yyvsp[-2].str)))});
        free((yyvsp[-2].str));
    }
#line 1858 "parser.tab.c"
    break;

  case 79: /* method: IDENTIFIER LBRACE method_arguments RBRACE  */
#line 454 "parser.y"
    {
        logs.push(Token{TokenType::METHOD, CleanQuotedString(std::string((yyvsp[-3].str)))});
        free((yyvsp[-3].str));
    }
#line 1867 "parser.tab.c"
    break;

  case 80: /* method: IDENTIFIER IDENTIFIER LBRACE method_arguments RBRACE  */
#line 459 "parser.y"
    {
        logs.push(Token{TokenType::METHOD, CleanQuotedString(std::string((yyvsp[-4].str))) + " " + CleanQuotedString(std::string((yyvsp[-3].str)))});
        free((yyvsp[-4].str));
        free((yyvsp[-3].str));
    }
#line 1877 "parser.tab.c"
    break;

  case 81: /* method_arguments: method_arguments COMMA IDENTIFIER IDENTIFIER  */
#line 468 "parser.y"
    {
        logs.push(Token{TokenType::METHOD_ARGUMENT, CleanQuotedString(std::string((yyvsp[-1].str))) + " " + CleanQuotedString(std::string((yyvsp[0].str)))});
        free((yyvsp[-1].str));
        free((yyvsp[0].str));
    }
#line 1887 "parser.tab.c"
    break;

  case 82: /* method_arguments: method_arguments COMMA IDENTIFIER  */
#line 475 "parser.y"
    {
        logs.push(Token{TokenType::METHOD_ARGUMENT, CleanQuotedString(std::string((yyvsp[0].str)))});
        free((yyvsp[0].str));
    }
#line 1896 "parser.tab.c"
    break;

  case 83: /* method_arguments: IDENTIFIER IDENTIFIER  */
#line 480 "parser.y"
    {
        logs.push(Token{TokenType::METHOD_ARGUMENT, CleanQuotedString(std::string((yyvsp[-1].str))) + " " + CleanQuotedString(std::string((yyvsp[0].str)))});
        free((yyvsp[-1].str));
        free((yyvsp[0].str));
    }
#line 1906 "parser.tab.c"
    break;

  case 84: /* method_arguments: IDENTIFIER  */
#line 486 "parser.y"
    {
        logs.push(Token{TokenType::METHOD_ARGUMENT, CleanQuotedString(std::string((yyvsp[0].str)))});
        free((yyvsp[0].str));
    }
#line 1915 "parser.tab.c"
    break;

  case 90: /* relationship: IDENTIFIER hyphen_with_direction HYPHEN LINE_LAST_IDENTIFIER  */
#line 502 "parser.y"
    {
        logs.push(Token{TokenType::ARROW_HEAD, std::string("None")});
        logs.push(Token{TokenType::NODE_NAME, CleanQuotedString(std::string((yyvsp[-3].str)))});
        logs.push(Token{TokenType::NODE_NAME, RemoveLastChar(std::string((yyvsp[0].str)))});
        logs.push(Token{TokenType::LINE, std::string("Hyphen")});
        logs.push(Token{TokenType::ARROW_HEAD, std::string("None")});
        free((yyvsp[-3].str));
        free((yyvsp[0].str));
    }
#line 1929 "parser.tab.c"
    break;

  case 91: /* relationship: IDENTIFIER hyphen_with_direction HYPHEN right_connection LINE_LAST_IDENTIFIER  */
#line 512 "parser.y"
    {
        logs.push(Token{TokenType::NODE_NAME, CleanQuotedString(std::string((yyvsp[-4].str)))});
        logs.push(Token{TokenType::NODE_NAME, RemoveLastChar(std::string((yyvsp[0].str)))});
        logs.push(Token{TokenType::LINE, std::string("Hyphen")});
        logs.push(Token{TokenType::ARROW_HEAD, std::string("None")});
        free((yyvsp[-4].str));
        free((yyvsp[0].str));
    }
#line 1942 "parser.tab.c"
    break;

  case 92: /* relationship: IDENTIFIER left_connection hyphen_with_direction HYPHEN LINE_LAST_IDENTIFIER  */
#line 521 "parser.y"
    {
        logs.push(Token{TokenType::ARROW_HEAD, std::string("None")});
        logs.push(Token{TokenType::NODE_NAME, CleanQuotedString(std::string((yyvsp[-4].str)))});
        logs.push(Token{TokenType::NODE_NAME, RemoveLastChar(std::string((yyvsp[0].str)))});
        logs.push(Token{TokenType::LINE, std::string("Hyphen")});
        free((yyvsp[-4].str));
        free((yyvsp[0].str));
    }
#line 1955 "parser.tab.c"
    break;

  case 93: /* relationship: IDENTIFIER left_connection hyphen_with_direction HYPHEN right_connection LINE_LAST_IDENTIFIER  */
#line 530 "parser.y"
    {
        logs.push(Token{TokenType::NODE_NAME, CleanQuotedString(std::string((yyvsp[-5].str)))});
        logs.push(Token{TokenType::NODE_NAME, RemoveLastChar(std::string((yyvsp[0].str)))});
        logs.push(Token{TokenType::LINE, std::string("Hyphen")});
        free((yyvsp[-5].str));
        free((yyvsp[0].str));
    }
#line 1967 "parser.tab.c"
    break;

  case 94: /* relationship: IDENTIFIER hyphen_with_direction HYPHEN IDENTIFIER skip_layoutt  */
#line 539 "parser.y"
    {
        logs.push(Token{TokenType::ARROW_HEAD, std::string("None")});
        logs.push(Token{TokenType::NODE_NAME, CleanQuotedString(std::string((yyvsp[-4].str)))});
        logs.push(Token{TokenType::NODE_NAME, RemoveLastChar(std::string((yyvsp[-1].str)))});
        logs.push(Token{TokenType::LINE, std::string("Hyphen")});
        logs.push(Token{TokenType::ARROW_HEAD, std::string("None")});
        free((yyvsp[-4].str));
        free((yyvsp[-1].str));
    }
#line 1981 "parser.tab.c"
    break;

  case 95: /* relationship: IDENTIFIER hyphen_with_direction HYPHEN right_connection IDENTIFIER skip_layoutt  */
#line 549 "parser.y"
    {
        logs.push(Token{TokenType::NODE_NAME, CleanQuotedString(std::string((yyvsp[-5].str)))});
        logs.push(Token{TokenType::NODE_NAME, RemoveLastChar(std::string((yyvsp[-1].str)))});
        logs.push(Token{TokenType::LINE, std::string("Hyphen")});
        logs.push(Token{TokenType::ARROW_HEAD, std::string("None")});
        free((yyvsp[-5].str));
        free((yyvsp[-1].str));
    }
#line 1994 "parser.tab.c"
    break;

  case 96: /* relationship: IDENTIFIER left_connection hyphen_with_direction HYPHEN IDENTIFIER skip_layoutt  */
#line 558 "parser.y"
    {
        logs.push(Token{TokenType::ARROW_HEAD, std::string("None")});
        logs.push(Token{TokenType::NODE_NAME, CleanQuotedString(std::string((yyvsp[-5].str)))});
        logs.push(Token{TokenType::NODE_NAME, RemoveLastChar(std::string((yyvsp[-1].str)))});
        logs.push(Token{TokenType::LINE, std::string("Hyphen")});
        free((yyvsp[-5].str));
        free((yyvsp[-1].str));
    }
#line 2007 "parser.tab.c"
    break;

  case 97: /* relationship: IDENTIFIER left_connection hyphen_with_direction HYPHEN right_connection IDENTIFIER skip_layoutt  */
#line 567 "parser.y"
    {
        logs.push(Token{TokenType::NODE_NAME, CleanQuotedString(std::string((yyvsp[-6].str)))});
        logs.push(Token{TokenType::NODE_NAME, CleanQuotedString(std::string((yyvsp[-1].str)))});
        logs.push(Token{TokenType::LINE, std::string("Hyphen")});
        free((yyvsp[-6].str));
        free((yyvsp[-1].str));
    }
#line 2019 "parser.tab.c"
    break;

  case 98: /* relationship_with_label: IDENTIFIER hyphen_with_direction HYPHEN IDENTIFIER COLON label  */
#line 578 "parser.y"
    {
        logs.push(Token{TokenType::ARROW_HEAD, std::string("None")});
        logs.push(Token{TokenType::LABEL, std::string("")});
        logs.push(Token{TokenType::NODE_NAME, CleanQuotedString(std::string((yyvsp[-5].str)))});
        logs.push(Token{TokenType::NODE_NAME, CleanQuotedString(std::string((yyvsp[-2].str)))});
        logs.push(Token{TokenType::LINE, std::string("Hyphen")});
        logs.push(Token{TokenType::ARROW_HEAD, std::string("None")});
        free((yyvsp[-5].str));
        free((yyvsp[-2].str));
    }
#line 2034 "parser.tab.c"
    break;

  case 99: /* relationship_with_label: IDENTIFIER hyphen_with_direction HYPHEN right_connection IDENTIFIER COLON label  */
#line 589 "parser.y"
    {
        logs.push(Token{TokenType::NODE_NAME, CleanQuotedString(std::string((yyvsp[-6].str)))});
        logs.push(Token{TokenType::NODE_NAME, CleanQuotedString(std::string((yyvsp[-2].str)))});
        logs.push(Token{TokenType::LINE, std::string("Hyphen")});
        logs.push(Token{TokenType::ARROW_HEAD, std::string("None")});
        free((yyvsp[-6].str));
        free((yyvsp[-2].str));
    }
#line 2047 "parser.tab.c"
    break;

  case 100: /* relationship_with_label: IDENTIFIER left_connection hyphen_with_direction HYPHEN IDENTIFIER COLON label  */
#line 598 "parser.y"
    {
        logs.push(Token{TokenType::ARROW_HEAD, std::string("None")});
        logs.push(Token{TokenType::LABEL, std::string("")});
        logs.push(Token{TokenType::NODE_NAME, CleanQuotedString(std::string((yyvsp[-6].str)))});
        logs.push(Token{TokenType::NODE_NAME, CleanQuotedString(std::string((yyvsp[-2].str)))});
        logs.push(Token{TokenType::LINE, std::string("Hyphen")});
        free((yyvsp[-6].str));
        free((yyvsp[-2].str));
    }
#line 2061 "parser.tab.c"
    break;

  case 101: /* relationship_with_label: IDENTIFIER left_connection hyphen_with_direction HYPHEN right_connection IDENTIFIER COLON label  */
#line 608 "parser.y"
    {
        logs.push(Token{TokenType::NODE_NAME, CleanQuotedString(std::string((yyvsp[-7].str)))});
        logs.push(Token{TokenType::NODE_NAME, CleanQuotedString(std::string((yyvsp[-2].str)))});
        logs.push(Token{TokenType::LINE, std::string("Hyphen")});
        free((yyvsp[-7].str));
        free((yyvsp[-2].str));
    }
#line 2073 "parser.tab.c"
    break;

  case 102: /* left_connection: L_ANGLE_BRACE PIPE  */
#line 620 "parser.y"
    {
        logs.push(Token{TokenType::ARROW_HEAD, std::string("OpenArrow")});
    }
#line 2081 "parser.tab.c"
    break;

  case 103: /* left_connection: L_ANGLE_BRACE  */
#line 624 "parser.y"
    {
        logs.push(Token{TokenType::ARROW_HEAD, std::string("Arrow")});
    }
#line 2089 "parser.tab.c"
    break;

  case 104: /* left_connection: R_CURLY_BRACE  */
#line 628 "parser.y"
    {
        logs.push(Token{TokenType::ARROW_HEAD, std::string("ThreeLines")});
    }
#line 2097 "parser.tab.c"
    break;

  case 106: /* right_connection: PIPE R_ANGLE_BRACE  */
#line 636 "parser.y"
    {
        logs.push(Token{TokenType::ARROW_HEAD, std::string("OpenArrow")});
    }
#line 2105 "parser.tab.c"
    break;

  case 107: /* right_connection: R_ANGLE_BRACE  */
#line 640 "parser.y"
    {
        logs.push(Token{TokenType::ARROW_HEAD, std::string("Arrow")});
    }
#line 2113 "parser.tab.c"
    break;

  case 108: /* right_connection: L_CURLY_BRACE  */
#line 644 "parser.y"
    {
        logs.push(Token{TokenType::ARROW_HEAD, std::string("ThreeLines")});
    }
#line 2121 "parser.tab.c"
    break;

  case 110: /* connection: STAR  */
#line 652 "parser.y"
    {
        logs.push(Token{TokenType::ARROW_HEAD, std::string("Rhomb")});
    }
#line 2129 "parser.tab.c"
    break;

  case 111: /* connection: O  */
#line 656 "parser.y"
    {
        logs.push(Token{TokenType::ARROW_HEAD, std::string("OpenRhomb")});
    }
#line 2137 "parser.tab.c"
    break;

  case 112: /* connection: HASH  */
#line 660 "parser.y"
    {
        logs.push(Token{TokenType::ARROW_HEAD, std::string("Square")});
    }
#line 2145 "parser.tab.c"
    break;

  case 113: /* connection: X  */
#line 664 "parser.y"
    {
        logs.push(Token{TokenType::ARROW_HEAD, std::string("X")});
    }
#line 2153 "parser.tab.c"
    break;

  case 114: /* connection: PLUS  */
#line 668 "parser.y"
    {
        logs.push(Token{TokenType::ARROW_HEAD, std::string("Circle")});
    }
#line 2161 "parser.tab.c"
    break;

  case 115: /* connection: HAT  */
#line 672 "parser.y"
    {
        logs.push(Token{TokenType::ARROW_HEAD, std::string("OpenArrow")});
    }
#line 2169 "parser.tab.c"
    break;

  case 116: /* label: IDENTIFIER  */
#line 679 "parser.y"
    {
        logs.push(Token{TokenType::LABEL, CleanQuotedString(std::string((yyvsp[0].str)))});
        free((yyvsp[0].str));
    }
#line 2178 "parser.tab.c"
    break;

  case 117: /* label: IDENTIFIER QUOTE SKIP_LAYOUT  */
#line 685 "parser.y"
    {
        logs.push(Token{TokenType::LABEL, CleanQuotedString(std::string((yyvsp[-2].str)))});
        logs.push(Token{TokenType::SKIP_LAYOUT, std::string("")});
        free((yyvsp[-2].str));
    }
#line 2188 "parser.tab.c"
    break;

  case 118: /* label: IDENTIFIER QUOTE SPLIT_EDGE  */
#line 692 "parser.y"
    {
        logs.push(Token{TokenType::SPLIT_EDGE, "None"});
        logs.push(Token{TokenType::LABEL, CleanQuotedString(std::string((yyvsp[-2].str)))});
        free((yyvsp[-2].str));
    }
#line 2198 "parser.tab.c"
    break;

  case 119: /* label: LINE_LAST_IDENTIFIER  */
#line 698 "parser.y"
    {
        logs.push(Token{TokenType::LABEL, RemoveLastChar(std::string((yyvsp[0].str)))});
        free((yyvsp[0].str));
    }
#line 2207 "parser.tab.c"
    break;

  case 120: /* label: LINE_LAST_IDENTIFIER QUOTE SKIP_LAYOUT  */
#line 703 "parser.y"
    {
        logs.push(Token{TokenType::LABEL, RemoveLastChar(std::string((yyvsp[-2].str)))});
        logs.push(Token{TokenType::SKIP_LAYOUT, std::string("")});
        free((yyvsp[-2].str));
    }
#line 2217 "parser.tab.c"
    break;


#line 2221 "parser.tab.c"

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
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 710 "parser.y"


void yyerror(const char *s) {
  class_diagram::generated_parser::FillLastError("Error: " + std::string(s) + " Field: " + std::string(yytext));
fprintf(stderr, "Error: %s. Field: %s\n", s, yytext);
}

namespace class_diagram {
namespace generated_parser {

void clearLogs() {
   std::stack<Token> empty;
   logs.swap(empty);
}


std::pair<std::string, std::stack<Token>> parse_class_diagram(const std::string& input) {
    clearLogs();

    // Convert std::stringbuf to FILE*
    FILE* file = fmemopen(const_cast<char*>(input.c_str()), input.size(), "r");
    if (!file) {
        perror("fmemopen");
        return {};
    }

    // Set buffer as input for Flex
    yyrestart(file);
    std::string result_string{};

    int result = yyparse();
    if (result == 0) {
        std::cout << "Parsing successful!" << std::endl;
    } else {
        std::cerr << "Parsing failed!" << std::endl;
        while (!logs.empty())
        {
          const auto token = logs.top();
          std::cerr << "Detected token: " << token.type << " " << token.name << std::endl;
          logs.pop();
        }
        result_string += GetLastError() + "\n";
    }

    fclose(file); // Zamknij FILE*

    return std::make_pair(result_string, logs);
}

}}
