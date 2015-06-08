/* A Bison parser, made by GNU Bison 3.0.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 6 "lang.y" /* yacc.c:339  */


#include <string>
#include <cstring>
#include <math.h>
#include <map>
#include "ast.h"
#include "lang.yystype.h"

typedef void* yyscan_t;
void yyerror (yyscan_t yyscanner, char const *msg);
void yyerror (yyscan_t yyscanner, Ast* ast, char const *msg);
int yylex(YYSTYPE *yylval_param, yyscan_t yyscanner);
bool parseExpression(const std::string& inp);


#line 83 "lang.tab.cpp" /* yacc.c:339  */

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
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
   by #include "lang.tab.h".  */
#ifndef YY_YY_LANG_TAB_H_INCLUDED
# define YY_YY_LANG_TAB_H_INCLUDED
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
    AND = 258,
    OR = 259,
    LE = 260,
    GE = 261,
    EQUALS = 262,
    NOTEQUALS = 263,
    IF = 264,
    ELSE = 265,
    WHILE = 266,
    FOR = 267,
    IN = 268,
    OUT = 269,
    INOUT = 270,
    MUL = 271,
    IDENT = 272,
    NUM_FLOAT = 273,
    NUM_INT = 274,
    ATTRIBUTE = 275,
    VARYING = 276,
    UNIFORM = 277
  };
#endif

/* Value type.  */



int yyparse (yyscan_t scanner, Ast* ast);

#endif /* !YY_YY_LANG_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 151 "lang.tab.cpp" /* yacc.c:358  */

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

#ifndef __attribute__
/* This feature is available in gcc versions 2.5 and later.  */
# if (! defined __GNUC__ || __GNUC__ < 2 \
      || (__GNUC__ == 2 && __GNUC_MINOR__ < 5))
#  define __attribute__(Spec) /* empty */
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
#define YYFINAL  14
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   303

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  36
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  16
/* YYNRULES -- Number of rules.  */
#define YYNRULES  59
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  139

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   277

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
      32,    33,    27,    25,    31,    26,     2,    28,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    29,
      23,    30,    24,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    34,     2,    35,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    50,    50,    53,    54,    59,    70,    80,    81,    82,
      91,    92,    93,    94,    95,    96,    97,    98,   103,   104,
     109,   110,   119,   120,   121,   122,   130,   138,   139,   140,
     141,   142,   143,   144,   145,   150,   151,   159,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   189,   190,   194,   195
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "AND", "OR", "LE", "GE", "EQUALS",
  "NOTEQUALS", "IF", "ELSE", "WHILE", "FOR", "IN", "OUT", "INOUT", "MUL",
  "IDENT", "NUM_FLOAT", "NUM_INT", "ATTRIBUTE", "VARYING", "UNIFORM",
  "'<'", "'>'", "'+'", "'-'", "'*'", "'/'", "';'", "'='", "','", "'('",
  "')'", "'{'", "'}'", "$accept", "program", "grammar_elem",
  "grammar_list", "shader_globals", "fndecl_vardecl_var", "fndecl_vardecl",
  "function_decl", "vardecl_var_list", "vardecl", "stmt", "stmt_list",
  "assign_stmt", "expr", "fncall_args", "expr_fncall", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,    60,    62,    43,    45,    42,    47,    59,
      61,    44,    40,    41,   123,   125
};
# endif

#define YYPACT_NINF -44

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-44)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -7,   -14,     2,    27,    36,    59,   -44,    -7,   -44,   -44,
      39,    55,    58,    61,   -44,   -44,    53,    70,   -44,   -44,
      86,    96,    98,   116,   252,   -44,    52,    47,   117,   118,
     119,    84,   115,   123,   124,   125,    28,   -44,   -44,    33,
     252,   136,   -44,   252,   137,     1,   -44,   131,   130,   -44,
     145,   147,   148,    33,    33,    33,   150,    33,   156,    33,
      73,   157,   144,    93,    45,   -44,   -44,   -44,    33,    33,
      33,    33,    33,    33,    33,    33,    33,    33,    33,    33,
     -44,   -44,   252,    33,    33,    33,   251,   104,   135,   170,
     160,   188,    33,   251,   -44,   251,    71,   173,   -44,   -44,
     275,   275,    97,    97,   267,   267,    97,    97,   -16,   -16,
     -44,   -44,   218,   251,   251,   251,   252,   252,    33,    33,
     251,    33,   -44,   167,   -44,   189,   -44,   217,   146,   251,
      33,   252,    33,   -44,   251,   -44,   177,   252,   -44
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     5,     2,     4,     3,
       0,     0,     0,     0,     1,     6,     0,     0,     8,     9,
       0,     0,     0,     0,     0,    18,     0,     0,     0,     0,
       0,    10,     0,     0,     0,     0,    39,    53,    54,     0,
       0,     0,    35,    21,     0,     0,    55,     0,     0,     7,
      12,    14,    16,     0,     0,     0,     0,     0,    22,     0,
       0,    26,    39,     0,     0,    27,    36,    29,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      28,    19,     0,     0,     0,     0,    11,     0,     0,     0,
       0,     0,     0,    37,    59,    56,     0,     0,    38,    34,
      41,    40,    44,    46,    43,    42,    45,    47,    48,    49,
      50,    51,     0,    13,    15,    17,     0,     0,     0,     0,
      23,     0,    58,    24,    20,    32,    31,     0,     0,    57,
       0,     0,     0,    52,    25,    33,     0,     0,    30
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -44,   -44,   191,   -44,   -44,   159,   -44,   -44,   -44,   151,
     -43,   -39,   -44,   -37,   -44,   -44
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     5,     6,     7,     8,    25,    26,     9,    61,    41,
      42,    43,    44,    45,    96,    46
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      66,    64,    63,    10,    68,    69,    70,    71,    72,    73,
       1,    78,    79,     2,     3,     4,    86,    87,    88,    11,
      91,    66,    93,    95,    74,    75,    76,    77,    78,    79,
      80,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,    12,    58,   113,   114,   115,    35,
      62,    37,    38,    13,    32,   120,    33,    34,    59,    14,
      60,    35,    36,    37,    38,    39,    20,    21,    22,    66,
      23,    16,    17,   125,   126,    18,    49,    39,    19,    40,
      99,   127,   128,    47,   129,    48,    24,    27,   135,    35,
      62,    37,    38,   134,   138,   136,    68,    69,    70,    71,
      72,    73,   121,    28,   122,    39,    94,    68,    69,    70,
      71,    72,    73,    29,    53,    30,    74,    75,    76,    77,
      78,    79,    76,    77,    78,    79,    98,    74,    75,    76,
      77,    78,    79,    31,    50,    51,    52,   116,    68,    69,
      70,    71,    72,    73,    20,    21,    22,    54,    23,    68,
      69,    70,    71,    72,    73,    55,    56,    57,    74,    75,
      76,    77,    78,    79,    82,    65,    67,    89,   117,    74,
      75,    76,    77,    78,    79,    83,    60,    84,    85,   133,
      68,    69,    70,    71,    72,    73,    92,    58,    97,   118,
     123,    68,    69,    70,    71,    72,    73,   130,    15,   131,
      74,    75,    76,    77,    78,    79,    81,    90,     0,     0,
     137,    74,    75,    76,    77,    78,    79,     0,     0,   119,
      68,    69,    70,    71,    72,    73,     0,    32,     0,    33,
      34,     0,     0,     0,    35,    36,    37,    38,     0,     0,
      74,    75,    76,    77,    78,    79,   132,     0,     0,     0,
      39,     0,    40,   124,    68,    69,    70,    71,    72,    73,
       0,    32,     0,    33,    34,     0,     0,     0,    35,    36,
      37,    38,    70,    71,    74,    75,    76,    77,    78,    79,
      70,    71,    72,    73,    39,     0,    40,     0,     0,     0,
      74,    75,    76,    77,    78,    79,     0,     0,    74,    75,
      76,    77,    78,    79
};

static const yytype_int16 yycheck[] =
{
      43,    40,    39,    17,     3,     4,     5,     6,     7,     8,
      17,    27,    28,    20,    21,    22,    53,    54,    55,    17,
      57,    64,    59,    60,    23,    24,    25,    26,    27,    28,
      29,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    82,    17,    17,    83,    84,    85,    16,
      17,    18,    19,    17,     9,    92,    11,    12,    30,     0,
      32,    16,    17,    18,    19,    32,    13,    14,    15,   112,
      17,    32,    17,   116,   117,    17,    29,    32,    17,    34,
      35,   118,   119,    31,   121,    33,    33,    17,   131,    16,
      17,    18,    19,   130,   137,   132,     3,     4,     5,     6,
       7,     8,    31,    17,    33,    32,    33,     3,     4,     5,
       6,     7,     8,    17,    30,    17,    23,    24,    25,    26,
      27,    28,    25,    26,    27,    28,    33,    23,    24,    25,
      26,    27,    28,    17,    17,    17,    17,    33,     3,     4,
       5,     6,     7,     8,    13,    14,    15,    32,    17,     3,
       4,     5,     6,     7,     8,    32,    32,    32,    23,    24,
      25,    26,    27,    28,    34,    29,    29,    17,    33,    23,
      24,    25,    26,    27,    28,    30,    32,    30,    30,    33,
       3,     4,     5,     6,     7,     8,    30,    17,    31,    29,
      17,     3,     4,     5,     6,     7,     8,    30,     7,    10,
      23,    24,    25,    26,    27,    28,    47,    56,    -1,    -1,
      33,    23,    24,    25,    26,    27,    28,    -1,    -1,    31,
       3,     4,     5,     6,     7,     8,    -1,     9,    -1,    11,
      12,    -1,    -1,    -1,    16,    17,    18,    19,    -1,    -1,
      23,    24,    25,    26,    27,    28,    29,    -1,    -1,    -1,
      32,    -1,    34,    35,     3,     4,     5,     6,     7,     8,
      -1,     9,    -1,    11,    12,    -1,    -1,    -1,    16,    17,
      18,    19,     5,     6,    23,    24,    25,    26,    27,    28,
       5,     6,     7,     8,    32,    -1,    34,    -1,    -1,    -1,
      23,    24,    25,    26,    27,    28,    -1,    -1,    23,    24,
      25,    26,    27,    28
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    17,    20,    21,    22,    37,    38,    39,    40,    43,
      17,    17,    17,    17,     0,    38,    32,    17,    17,    17,
      13,    14,    15,    17,    33,    41,    42,    17,    17,    17,
      17,    17,     9,    11,    12,    16,    17,    18,    19,    32,
      34,    45,    46,    47,    48,    49,    51,    31,    33,    29,
      17,    17,    17,    30,    32,    32,    32,    32,    17,    30,
      32,    44,    17,    49,    47,    29,    46,    29,     3,     4,
       5,     6,     7,     8,    23,    24,    25,    26,    27,    28,
      29,    41,    34,    30,    30,    30,    49,    49,    49,    17,
      45,    49,    30,    49,    33,    49,    50,    31,    33,    35,
      49,    49,    49,    49,    49,    49,    49,    49,    49,    49,
      49,    49,    47,    49,    49,    49,    33,    33,    29,    31,
      49,    31,    33,    17,    35,    46,    46,    49,    49,    49,
      30,    10,    29,    33,    49,    46,    49,    33,    46
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    36,    37,    38,    38,    39,    39,    40,    40,    40,
      41,    41,    41,    41,    41,    41,    41,    41,    42,    42,
      43,    43,    44,    44,    44,    44,    45,    46,    46,    46,
      46,    46,    46,    46,    46,    47,    47,    48,    49,    49,
      49,    49,    49,    49,    49,    49,    49,    49,    49,    49,
      49,    49,    49,    49,    49,    49,    50,    50,    51,    51
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     2,     5,     3,     3,
       2,     4,     3,     5,     3,     5,     3,     5,     1,     3,
       8,     5,     1,     3,     3,     5,     2,     2,     2,     2,
       9,     5,     5,     7,     3,     1,     2,     3,     3,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     6,     1,     1,     1,     1,     3,     4,     3
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
      yyerror (scanner, ast, YY_("syntax error: cannot back up")); \
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
                  Type, Value, scanner, ast); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, yyscan_t scanner, Ast* ast)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (scanner);
  YYUSE (ast);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, yyscan_t scanner, Ast* ast)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, scanner, ast);
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule, yyscan_t scanner, Ast* ast)
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
                                              , scanner, ast);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, scanner, ast); \
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, yyscan_t scanner, Ast* ast)
{
  YYUSE (yyvaluep);
  YYUSE (scanner);
  YYUSE (ast);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (yyscan_t scanner, Ast* ast)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs;

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
      yychar = yylex (&yylval, scanner);
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
#line 50 "lang.y" /* yacc.c:1646  */
    { ast->program = (yyvsp[0].node); (yyval.node) = (yyvsp[0].node); }
#line 1332 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 53 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1338 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 54 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = nullptr; }
#line 1344 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 60 "lang.y" /* yacc.c:1646  */
    { 
			// Create a list of program elements(only functions so far).
			(yyval.node) = ast->push<ProgramElem>(); 
			
			// A program element is not necessary a node. 
			// For example vertexAttribs/varyings/uniforms they just do a add themselves
			// to a container containing all the declarations.
			if((yyvsp[0].node) != nullptr) (yyval.node)->As<ProgramElem>().nodes.push_back((yyvsp[0].node)); 
		}
#line 1358 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 71 "lang.y" /* yacc.c:1646  */
    { 
			if ((yyvsp[0].node) != nullptr) (yyvsp[-1].node)->As<ProgramElem>().nodes.push_back((yyvsp[0].node)); 
			(yyval.node) = (yyvsp[-1].node);
		}
#line 1367 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 80 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = nullptr; ast->vertexAttribs.push_back({(yyvsp[-3].str_val), (yyvsp[-2].str_val), (yyvsp[-1].str_val)}); }
#line 1373 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 81 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = nullptr; ast->varyings.push_back({(yyvsp[-1].str_val), (yyvsp[0].str_val)}); }
#line 1379 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 82 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = nullptr; ast->uniforms.push_back({(yyvsp[-1].str_val), (yyvsp[0].str_val)}); }
#line 1385 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 91 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<FnDeclArgVarDecl>({(yyvsp[-1].str_val), (yyvsp[0].str_val), nullptr, FNAT_In      }); }
#line 1391 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 92 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<FnDeclArgVarDecl>({(yyvsp[-3].str_val), (yyvsp[-2].str_val), (yyvsp[0].node)     , FNAT_In      }); }
#line 1397 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 93 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<FnDeclArgVarDecl>({(yyvsp[-1].str_val), (yyvsp[0].str_val), nullptr, FNAT_In	  }); }
#line 1403 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 94 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<FnDeclArgVarDecl>({(yyvsp[-3].str_val), (yyvsp[-2].str_val), (yyvsp[0].node)     , FNAT_In	  }); }
#line 1409 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 95 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<FnDeclArgVarDecl>({(yyvsp[-1].str_val), (yyvsp[0].str_val), nullptr, FNAT_Out     }); }
#line 1415 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 96 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<FnDeclArgVarDecl>({(yyvsp[-3].str_val), (yyvsp[-2].str_val), (yyvsp[0].node)     , FNAT_Out     }); }
#line 1421 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 97 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<FnDeclArgVarDecl>({(yyvsp[-1].str_val), (yyvsp[0].str_val), nullptr, FNAT_InOut   }); }
#line 1427 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 98 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<FnDeclArgVarDecl>({(yyvsp[-3].str_val), (yyvsp[-2].str_val), (yyvsp[0].node)     , FNAT_InOut   }); }
#line 1433 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 103 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<FnDeclArgs>({{(yyvsp[0].node)}}); }
#line 1439 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 104 "lang.y" /* yacc.c:1646  */
    { (yyvsp[-2].node)->As<FnDeclArgs>().args.push_back((yyvsp[0].node)); (yyval.node) = (yyvsp[-2].node); }
#line 1445 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 109 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<FuncDecl>({(yyvsp[-7].str_val), (yyvsp[-6].str_val), (yyvsp[-4].node), (yyvsp[-1].node)}); }
#line 1451 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 110 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<FuncDecl>({(yyvsp[-4].str_val), (yyvsp[-3].str_val), nullptr, (yyvsp[0].node)}); }
#line 1457 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 119 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<VarDecl>({"unk", {(yyvsp[0].str_val)}, {nullptr}}); }
#line 1463 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 120 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<VarDecl>({"unk", {(yyvsp[-2].str_val)}, {(yyvsp[0].node)}}); }
#line 1469 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 121 "lang.y" /* yacc.c:1646  */
    { (yyval.node)->As<VarDecl>().ident.push_back((yyvsp[0].str_val));	}
#line 1475 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 122 "lang.y" /* yacc.c:1646  */
    { 
			(yyval.node) = (yyvsp[-4].node); 
			(yyval.node)->As<VarDecl>().ident.push_back((yyvsp[-2].str_val));
			(yyval.node)->As<VarDecl>().expr.push_back((yyvsp[0].node));
		}
#line 1485 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 130 "lang.y" /* yacc.c:1646  */
    { (yyvsp[0].node)->As<VarDecl>().type = (yyvsp[-1].str_val); (yyval.node) = (yyvsp[0].node); }
#line 1491 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 138 "lang.y" /* yacc.c:1646  */
    { (yyvsp[-1].node)->hasSemicolon = true; ; (yyval.node) = (yyvsp[-1].node); }
#line 1497 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 139 "lang.y" /* yacc.c:1646  */
    { (yyvsp[-1].node)->hasSemicolon = true; (yyval.node) = (yyvsp[-1].node); }
#line 1503 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 140 "lang.y" /* yacc.c:1646  */
    { (yyvsp[-1].node)->hasSemicolon = true; (yyval.node) = (yyvsp[-1].node); }
#line 1509 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 141 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push(StmtFor{(yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node)}); }
#line 1515 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 142 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push(StmtWhile{(yyvsp[-2].node), (yyvsp[0].node)}); }
#line 1521 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 143 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push(StmtIf((yyvsp[-2].node), (yyvsp[0].node), nullptr)); }
#line 1527 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 144 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push(StmtIf((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node))); }
#line 1533 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 145 "lang.y" /* yacc.c:1646  */
    { (yyvsp[-1].node)->inBlock = true; (yyval.node) = (yyvsp[-1].node); }
#line 1539 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 150 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<NodeList>({}); (yyval.node)->As<NodeList>().nodes.push_back((yyvsp[0].node)); }
#line 1545 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 151 "lang.y" /* yacc.c:1646  */
    { 
			(yyval.node) = (yyvsp[-1].node);
			(yyvsp[-1].node)->As<NodeList>().nodes.push_back( {(yyvsp[0].node)} );
		}
#line 1554 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 159 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<Assign>({(yyvsp[-2].str_val).c_str(), (yyvsp[0].node)}); }
#line 1560 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 166 "lang.y" /* yacc.c:1646  */
    { (yyvsp[-1].node)->inParens = true; (yyval.node) = (yyvsp[-1].node); }
#line 1566 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 167 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<Ident>({(yyvsp[0].str_val)}); }
#line 1572 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 168 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<ExprBin>({EBT_Or, (yyvsp[-2].node), (yyvsp[0].node)}); }
#line 1578 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 169 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<ExprBin>({EBT_And, (yyvsp[-2].node), (yyvsp[0].node)}); }
#line 1584 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 170 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<ExprBin>({EBT_NEquals, (yyvsp[-2].node), (yyvsp[0].node)}); }
#line 1590 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 171 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<ExprBin>({EBT_Equals, (yyvsp[-2].node), (yyvsp[0].node)}); }
#line 1596 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 172 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<ExprBin>({EBT_LEquals, (yyvsp[-2].node), (yyvsp[0].node)}); }
#line 1602 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 173 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<ExprBin>({EBT_Less, (yyvsp[-2].node), (yyvsp[0].node)}); }
#line 1608 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 174 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<ExprBin>({EBT_GEquals, (yyvsp[-2].node), (yyvsp[0].node)}); }
#line 1614 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 175 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<ExprBin>({EBT_Greater, (yyvsp[-2].node), (yyvsp[0].node)}); }
#line 1620 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 176 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<ExprBin>({EBT_Add, (yyvsp[-2].node), (yyvsp[0].node)}); }
#line 1626 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 177 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<ExprBin>({EBT_Sub, (yyvsp[-2].node), (yyvsp[0].node)}); }
#line 1632 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 178 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<ExprBin>({EBT_Mul, (yyvsp[-2].node), (yyvsp[0].node)}); }
#line 1638 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 179 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<ExprBin>({EBT_Div, (yyvsp[-2].node), (yyvsp[0].node)}); }
#line 1644 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 180 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push(ExprBin(EBT_MatMul, (yyvsp[-3].node), (yyvsp[-1].node))); }
#line 1650 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 181 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push(ExprLiteral((yyvsp[0].float_val))); }
#line 1656 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 182 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push(ExprLiteral((yyvsp[0].int_val))); }
#line 1662 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 183 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1668 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 189 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<FuncCallArgs>({{(yyvsp[0].node)}}); }
#line 1674 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 190 "lang.y" /* yacc.c:1646  */
    { (yyvsp[-2].node)->As<FuncCallArgs>().args.push_back((yyvsp[0].node)); (yyval.node) = (yyvsp[-2].node); }
#line 1680 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 194 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<FuncCall>({(yyvsp[-3].str_val), (yyvsp[-1].node)}); }
#line 1686 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 195 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<FuncCall>({(yyvsp[-2].str_val), nullptr}); }
#line 1692 "lang.tab.cpp" /* yacc.c:1646  */
    break;


#line 1696 "lang.tab.cpp" /* yacc.c:1646  */
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
      yyerror (scanner, ast, YY_("syntax error"));
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
        yyerror (scanner, ast, yymsgp);
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
                      yytoken, &yylval, scanner, ast);
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
                  yystos[yystate], yyvsp, scanner, ast);
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
  yyerror (scanner, ast, YY_("memory exhausted"));
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
                  yytoken, &yylval, scanner, ast);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, scanner, ast);
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
#line 201 "lang.y" /* yacc.c:1906  */


void yyerror (yyscan_t yyscanner, char const *msg){
    fprintf(stderr, "%s\n", msg);
}

void yyerror (yyscan_t yyscanner, Ast* ast, char const *msg) {
	yyerror(yyscanner, msg);
}
