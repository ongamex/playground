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
    IDENT = 271,
    CODE_STRING = 272,
    NUM_FLOAT = 273,
    NUM_INT = 274,
    ATTRIBUTE = 275,
    VARYING = 276,
    UNIFORM = 277,
    NATIVE_CODE = 278
  };
#endif

/* Value type.  */



int yyparse (yyscan_t scanner, Ast* ast);

#endif /* !YY_YY_LANG_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 152 "lang.tab.cpp" /* yacc.c:358  */

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
#define YYLAST   190

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  39
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  17
/* YYNRULES -- Number of rules.  */
#define YYNRULES  61
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  141

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   278

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
      35,    36,    28,    26,    34,    27,    30,    29,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    31,    32,
      24,    33,    25,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    37,     2,    38,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    23
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    52,    52,    55,    56,    61,    72,    82,    83,    84,
      93,    94,    95,    96,    97,    98,    99,   100,   108,   109,
     110,   117,   133,   134,   135,   140,   148,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   169,   174,   175,   185,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   211,   212,
     219,   223
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "AND", "OR", "LE", "GE", "EQUALS",
  "NOTEQUALS", "IF", "ELSE", "WHILE", "FOR", "IN", "OUT", "INOUT", "IDENT",
  "CODE_STRING", "NUM_FLOAT", "NUM_INT", "ATTRIBUTE", "VARYING", "UNIFORM",
  "NATIVE_CODE", "'<'", "'>'", "'+'", "'-'", "'*'", "'/'", "'.'", "':'",
  "';'", "'='", "','", "'('", "')'", "'{'", "'}'", "$accept", "program",
  "grammar_elem", "grammar_list", "shader_globals", "fndecl_vardecl_var",
  "fndecl_vardecl", "function_decl", "vardecl_var_list", "vardecl", "stmt",
  "assign_stmt", "stmt_list", "expr", "expr_base", "fncall_args",
  "expr_fncall", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,    60,    62,    43,    45,    42,    47,
      46,    58,    59,    61,    44,    40,    41,   123,   125
};
# endif

#define YYPACT_NINF -62

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-62)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -9,   -13,     4,     7,    10,    42,   -62,    -9,   -62,   -62,
      19,    29,    47,    48,   -62,   -62,    68,    27,    39,    45,
      63,    78,    79,    85,   -62,   -26,    86,   -62,   -62,    87,
      89,    92,    76,    68,    77,    83,   100,   102,   104,     6,
     -62,   101,   -62,     6,     6,     6,    81,   -62,   -62,     6,
     -62,   124,   -62,    99,   108,   109,   -14,   110,   101,    90,
     -62,   123,    37,   125,   -62,   -62,   -62,     6,    62,     6,
       6,     6,     6,     6,     6,     6,     6,     6,     6,     6,
       6,   105,     6,     6,   140,   139,     6,    84,   156,    88,
     -62,   -62,   -62,   -62,   -62,   124,    23,   -62,   134,   134,
     -12,   -12,   141,   141,   -12,   -12,    22,    22,   144,   144,
     -62,   142,   143,   159,   145,     6,   -62,   160,   146,   -62,
       6,   -62,   101,   101,     6,   -62,   147,   149,   124,   173,
     -62,   152,     6,   -62,   101,     6,   -62,   -62,   150,   101,
     -62
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     5,     2,     4,     3,
       0,     0,     0,     0,     1,     6,    18,     0,     0,     0,
       0,     0,     0,     0,    19,     0,     0,     8,     9,     0,
       0,     0,    10,     0,     0,     0,    12,    14,    16,     0,
      20,     0,     7,     0,     0,     0,    42,    55,    56,     0,
      11,    39,    57,     0,     0,     0,    42,     0,     0,     0,
      37,     0,     0,     0,    13,    15,    17,    58,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    22,     0,    26,     0,     0,
      27,    29,    21,    38,    28,    59,     0,    40,    44,    43,
      47,    49,    46,    45,    48,    50,    51,    52,    53,    54,
      41,     0,     0,     0,     0,     0,    36,     0,     0,    34,
       0,    61,     0,     0,     0,    23,    24,     0,    60,    32,
      31,     0,     0,    35,     0,     0,    25,    33,     0,     0,
      30
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -62,   -62,   178,   -62,   -62,   154,   -62,   -62,   -62,   106,
     -61,   -62,   130,   -39,   -40,   -62,   -62
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     5,     6,     7,     8,    24,    25,     9,    87,    59,
      60,    61,    62,    63,    51,    96,    52
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      50,    93,    85,    10,    64,    65,    66,     1,    33,    68,
      34,     2,     3,     4,    77,    78,    79,    80,    81,    86,
      11,    67,    46,    12,    47,    48,    13,    95,    93,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,    49,    14,   111,   112,    17,    53,   116,    54,    55,
      79,    80,    81,    56,    16,    47,    48,   120,    26,   121,
      57,   129,   130,    18,    19,    69,    70,    71,    72,    73,
      74,    27,    49,   137,    58,    92,   125,    28,   140,    29,
     128,    20,    21,    22,    23,   131,    75,    76,    77,    78,
      79,    80,    81,   136,    30,    31,   138,    53,    97,    54,
      55,    32,    35,    36,    56,    37,    47,    48,    38,    39,
      53,    57,    54,    55,    41,    42,    67,    56,   117,    47,
      48,   110,    90,    49,    57,    58,   119,    69,    70,    71,
      72,    73,    74,    43,    82,    44,    49,    45,    58,    71,
      72,    73,    74,    83,    84,    88,    71,    72,    75,    76,
      77,    78,    79,    80,    81,    91,   113,    94,    75,    76,
      77,    78,    79,    80,    81,    75,    76,    77,    78,    79,
      80,    81,   115,   118,    81,    85,   126,   124,   122,   123,
     132,   133,   127,   134,   135,    15,   139,    40,    89,     0,
     114
};

static const yytype_int16 yycheck[] =
{
      39,    62,    16,    16,    43,    44,    45,    16,    34,    49,
      36,    20,    21,    22,    26,    27,    28,    29,    30,    33,
      16,    35,    16,    16,    18,    19,    16,    67,    89,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    35,     0,    82,    83,    16,     9,    86,    11,    12,
      28,    29,    30,    16,    35,    18,    19,    34,    31,    36,
      23,   122,   123,    16,    16,     3,     4,     5,     6,     7,
       8,    32,    35,   134,    37,    38,   115,    32,   139,    16,
     120,    13,    14,    15,    16,   124,    24,    25,    26,    27,
      28,    29,    30,   132,    16,    16,   135,     9,    36,    11,
      12,    16,    16,    16,    16,    16,    18,    19,    16,    33,
       9,    23,    11,    12,    37,    32,    35,    16,    34,    18,
      19,    16,    32,    35,    23,    37,    38,     3,     4,     5,
       6,     7,     8,    33,    35,    33,    35,    33,    37,     5,
       6,     7,     8,    35,    35,    35,     5,     6,    24,    25,
      26,    27,    28,    29,    30,    32,    16,    32,    24,    25,
      26,    27,    28,    29,    30,    24,    25,    26,    27,    28,
      29,    30,    33,    17,    30,    16,    16,    32,    36,    36,
      33,    32,    36,    10,    32,     7,    36,    33,    58,    -1,
      84
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    16,    20,    21,    22,    40,    41,    42,    43,    46,
      16,    16,    16,    16,     0,    41,    35,    16,    16,    16,
      13,    14,    15,    16,    44,    45,    31,    32,    32,    16,
      16,    16,    16,    34,    36,    16,    16,    16,    16,    33,
      44,    37,    32,    33,    33,    33,    16,    18,    19,    35,
      52,    53,    55,     9,    11,    12,    16,    23,    37,    48,
      49,    50,    51,    52,    52,    52,    52,    35,    53,     3,
       4,     5,     6,     7,     8,    24,    25,    26,    27,    28,
      29,    30,    35,    35,    35,    16,    33,    47,    35,    51,
      32,    32,    38,    49,    32,    53,    54,    36,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      16,    52,    52,    16,    48,    33,    52,    34,    17,    38,
      34,    36,    36,    36,    32,    52,    16,    36,    53,    49,
      49,    52,    33,    32,    10,    32,    52,    49,    52,    36,
      49
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    39,    40,    41,    41,    42,    42,    43,    43,    43,
      44,    44,    44,    44,    44,    44,    44,    44,    45,    45,
      45,    46,    47,    47,    47,    47,    48,    49,    49,    49,
      49,    49,    49,    49,    49,    49,    50,    51,    51,    52,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    54,    54,
      54,    55
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     2,     6,     4,     4,
       2,     4,     3,     5,     3,     5,     3,     5,     0,     1,
       3,     8,     1,     3,     3,     5,     2,     2,     2,     2,
       9,     5,     5,     7,     3,     5,     3,     1,     2,     1,
       3,     3,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     1,     1,     1,     0,     1,
       3,     4
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
#line 52 "lang.y" /* yacc.c:1646  */
    { ast->program = (yyvsp[0].node); (yyval.node) = (yyvsp[0].node); }
#line 1318 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 55 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1324 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 56 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = nullptr; }
#line 1330 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 62 "lang.y" /* yacc.c:1646  */
    { 
			// Create a list of program elements(only functions so far).
			(yyval.node) = ast->push<ProgramElem>(); 
			
			// A program element is not necessary a node. 
			// For example vertexAttribs/varyings/uniforms they just do a add themselves
			// to a container containing all the declarations.
			if((yyvsp[0].node) != nullptr) (yyval.node)->As<ProgramElem>().nodes.push_back((yyvsp[0].node)); 
		}
#line 1344 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 73 "lang.y" /* yacc.c:1646  */
    { 
			if ((yyvsp[0].node) != nullptr) (yyvsp[-1].node)->As<ProgramElem>().nodes.push_back((yyvsp[0].node)); 
			(yyval.node) = (yyvsp[-1].node);
		}
#line 1353 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 82 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = nullptr; ast->vertexAttribs.push_back({TypeDesc((yyvsp[-4].str_val)), (yyvsp[-3].str_val), (yyvsp[-1].str_val)}); }
#line 1359 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 83 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = nullptr; ast->varyings.push_back({TypeDesc((yyvsp[-2].str_val)), (yyvsp[-1].str_val)}); }
#line 1365 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 84 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = nullptr; ast->uniforms.push_back({TypeDesc((yyvsp[-2].str_val)), (yyvsp[-1].str_val)}); }
#line 1371 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 93 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push(FnDeclArgVarDecl(TypeDesc((yyvsp[-1].str_val)), (yyvsp[0].str_val), nullptr, FNAT_In      )); }
#line 1377 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 94 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push(FnDeclArgVarDecl(TypeDesc((yyvsp[-3].str_val)), (yyvsp[-2].str_val), (yyvsp[0].node)     , FNAT_In      )); }
#line 1383 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 95 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push(FnDeclArgVarDecl(TypeDesc((yyvsp[-1].str_val)), (yyvsp[0].str_val), nullptr, FNAT_In	  )); }
#line 1389 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 96 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push(FnDeclArgVarDecl(TypeDesc((yyvsp[-3].str_val)), (yyvsp[-2].str_val), (yyvsp[0].node)     , FNAT_In	  )); }
#line 1395 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 97 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push(FnDeclArgVarDecl(TypeDesc((yyvsp[-1].str_val)), (yyvsp[0].str_val), nullptr, FNAT_Out     )); }
#line 1401 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 98 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push(FnDeclArgVarDecl(TypeDesc((yyvsp[-3].str_val)), (yyvsp[-2].str_val), (yyvsp[0].node)     , FNAT_Out     )); }
#line 1407 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 99 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push(FnDeclArgVarDecl(TypeDesc((yyvsp[-1].str_val)), (yyvsp[0].str_val), nullptr, FNAT_InOut   )); }
#line 1413 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 100 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push(FnDeclArgVarDecl(TypeDesc((yyvsp[-3].str_val)), (yyvsp[-2].str_val), (yyvsp[0].node)     , FNAT_InOut   )); }
#line 1419 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 108 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<FuncDecl>(); }
#line 1425 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 109 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<FuncDecl>({{(yyvsp[0].node)}}); }
#line 1431 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 110 "lang.y" /* yacc.c:1646  */
    { (yyvsp[-2].node)->As<FuncDecl>().args.push_back((yyvsp[0].node)); (yyval.node) = (yyvsp[-2].node); }
#line 1437 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 117 "lang.y" /* yacc.c:1646  */
    { 
		auto& funcDecl = (yyvsp[-4].node)->As<FuncDecl>();
		funcDecl.retType = TypeDesc((yyvsp[-7].str_val));
		funcDecl.name = (yyvsp[-6].str_val);
		funcDecl.stmt = (yyvsp[-1].node);
		(yyval.node) = (yyvsp[-4].node);
	}
#line 1449 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 133 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push(VarDecl(TypeDesc(), (yyvsp[0].str_val), nullptr)); }
#line 1455 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 134 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push(VarDecl(TypeDesc(), (yyvsp[-2].str_val), (yyvsp[0].node))); }
#line 1461 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 135 "lang.y" /* yacc.c:1646  */
    { 
			(yyvsp[-2].node)->As<VarDecl>().ident.push_back((yyvsp[0].str_val));
			(yyvsp[-2].node)->As<VarDecl>().expr.push_back(nullptr);
			(yyval.node) = (yyvsp[-2].node);
		}
#line 1471 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 140 "lang.y" /* yacc.c:1646  */
    { 
			(yyval.node) = (yyvsp[-4].node); 
			(yyval.node)->As<VarDecl>().ident.push_back((yyvsp[-2].str_val));
			(yyval.node)->As<VarDecl>().expr.push_back((yyvsp[0].node));
		}
#line 1481 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 148 "lang.y" /* yacc.c:1646  */
    { (yyvsp[0].node)->As<VarDecl>().type = TypeDesc((yyvsp[-1].str_val)); (yyval.node) = (yyvsp[0].node); }
#line 1487 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 156 "lang.y" /* yacc.c:1646  */
    { (yyvsp[-1].node)->hasSemicolon = true; ; (yyval.node) = (yyvsp[-1].node); }
#line 1493 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 157 "lang.y" /* yacc.c:1646  */
    { (yyvsp[-1].node)->hasSemicolon = true; (yyval.node) = (yyvsp[-1].node); }
#line 1499 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 158 "lang.y" /* yacc.c:1646  */
    { (yyvsp[-1].node)->hasSemicolon = true; (yyval.node) = (yyvsp[-1].node); }
#line 1505 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 159 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push(StmtFor{(yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node)}); }
#line 1511 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 160 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push(StmtWhile{(yyvsp[-2].node), (yyvsp[0].node)}); }
#line 1517 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 161 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push(StmtIf((yyvsp[-2].node), (yyvsp[0].node), nullptr)); }
#line 1523 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 162 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push(StmtIf((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node))); }
#line 1529 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 163 "lang.y" /* yacc.c:1646  */
    { (yyvsp[-1].node)->inBlock = true; (yyval.node) = (yyvsp[-1].node); }
#line 1535 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 164 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push(StmtNativeCode((yyvsp[-2].str_val))); }
#line 1541 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 169 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<Assign>({(yyvsp[-2].str_val).c_str(), (yyvsp[0].node)}); }
#line 1547 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 174 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<StmtList>({}); (yyval.node)->As<StmtList>().nodes.push_back((yyvsp[0].node)); }
#line 1553 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 175 "lang.y" /* yacc.c:1646  */
    { 
			(yyval.node) = (yyvsp[-1].node);
			(yyvsp[-1].node)->As<StmtList>().nodes.push_back( {(yyvsp[0].node)} );
		}
#line 1562 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 185 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); ast->addDeduct((yyvsp[0].node)); }
#line 1568 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 188 "lang.y" /* yacc.c:1646  */
    { (yyvsp[-1].node)->inParens = true; (yyval.node) = (yyvsp[-1].node); }
#line 1574 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 189 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push(ExprMemberAccess((yyvsp[-2].node), (yyvsp[0].str_val)));}
#line 1580 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 190 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<Ident>({(yyvsp[0].str_val)}); }
#line 1586 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 191 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push(ExprBin(EBT_Or, (yyvsp[-2].node), (yyvsp[0].node))); }
#line 1592 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 192 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push(ExprBin(EBT_And, (yyvsp[-2].node), (yyvsp[0].node))); }
#line 1598 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 193 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push(ExprBin(EBT_NEquals, (yyvsp[-2].node), (yyvsp[0].node))); }
#line 1604 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 194 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push(ExprBin(EBT_Equals, (yyvsp[-2].node), (yyvsp[0].node))); }
#line 1610 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 195 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push(ExprBin(EBT_LEquals, (yyvsp[-2].node), (yyvsp[0].node))); }
#line 1616 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 196 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push(ExprBin(EBT_Less, (yyvsp[-2].node), (yyvsp[0].node))); }
#line 1622 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 197 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push(ExprBin(EBT_GEquals, (yyvsp[-2].node), (yyvsp[0].node))); }
#line 1628 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 198 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push(ExprBin(EBT_Greater, (yyvsp[-2].node), (yyvsp[0].node))); }
#line 1634 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 199 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push(ExprBin(EBT_Add, (yyvsp[-2].node), (yyvsp[0].node))); }
#line 1640 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 200 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push(ExprBin(EBT_Sub, (yyvsp[-2].node), (yyvsp[0].node))); }
#line 1646 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 201 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push(ExprBin(EBT_Mul, (yyvsp[-2].node), (yyvsp[0].node))); }
#line 1652 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 202 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push(ExprBin(EBT_Div, (yyvsp[-2].node), (yyvsp[0].node))); }
#line 1658 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 203 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push(ExprLiteral((yyvsp[0].float_val))); }
#line 1664 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 204 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push(ExprLiteral((yyvsp[0].int_val))); }
#line 1670 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 205 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1676 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 211 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<FuncCall>(); }
#line 1682 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 213 "lang.y" /* yacc.c:1646  */
    { 
				Node* fnCall = ast->push<FuncCall>();
				fnCall->As<FuncCall>().args.push_back((yyvsp[0].node)); 
				(yyval.node) = fnCall;
			}
#line 1692 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 219 "lang.y" /* yacc.c:1646  */
    { (yyvsp[-2].node)->As<FuncCall>().args.push_back((yyvsp[0].node)); (yyval.node) = (yyvsp[-2].node); }
#line 1698 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 223 "lang.y" /* yacc.c:1646  */
    { 
			(yyvsp[-1].node)->As<FuncCall>().fnName = (yyvsp[-3].str_val);
			(yyval.node) = (yyvsp[-1].node); 
		}
#line 1707 "lang.tab.cpp" /* yacc.c:1646  */
    break;


#line 1711 "lang.tab.cpp" /* yacc.c:1646  */
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
#line 232 "lang.y" /* yacc.c:1906  */


void yyerror (yyscan_t yyscanner, char const *msg){
    fprintf(stderr, "%s\n", msg);
}

void yyerror (yyscan_t yyscanner, Ast* ast, char const *msg) {
	yyerror(yyscanner, msg);
}
