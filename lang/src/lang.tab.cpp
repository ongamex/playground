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
    WHILE = 264,
    FOR = 265,
    IN = 266,
    OUT = 267,
    INOUT = 268,
    IF = 269,
    NONASSOC_IF = 270,
    ELSE = 271,
    IDENT = 272,
    CODE_STRING = 273,
    RETURN = 274,
    NUM_FLOAT = 275,
    NUM_INT = 276,
    ATTRIBUTE = 277,
    VARYING = 278,
    UNIFORM = 279,
    NATIVE_CODE = 280,
    NONASSOC_UNARY = 281
  };
#endif

/* Value type.  */



int yyparse (yyscan_t scanner, Ast* ast);

#endif /* !YY_YY_LANG_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 155 "lang.tab.cpp" /* yacc.c:358  */

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
#define YYLAST   242

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  17
/* YYNRULES -- Number of rules.  */
#define YYNRULES  65
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  149

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   281

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
      38,    39,    30,    28,    37,    29,    32,    31,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    34,    35,
      26,    36,    27,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    40,     2,    41,     2,     2,     2,     2,
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
      25,    33
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    63,    63,    66,    67,    72,    83,    93,    94,    95,
     104,   105,   106,   107,   108,   109,   110,   111,   119,   120,
     121,   128,   144,   145,   146,   151,   159,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   182,   187,
     188,   198,   201,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   226,   227,   234,   238
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "AND", "OR", "LE", "GE", "EQUALS",
  "NOTEQUALS", "WHILE", "FOR", "IN", "OUT", "INOUT", "IF", "NONASSOC_IF",
  "ELSE", "IDENT", "CODE_STRING", "RETURN", "NUM_FLOAT", "NUM_INT",
  "ATTRIBUTE", "VARYING", "UNIFORM", "NATIVE_CODE", "'<'", "'>'", "'+'",
  "'-'", "'*'", "'/'", "'.'", "NONASSOC_UNARY", "':'", "';'", "'='", "','",
  "'('", "')'", "'{'", "'}'", "$accept", "program", "grammar_elem",
  "grammar_list", "shader_globals", "fndecl_vardecl_var", "fndecl_vardecl",
  "function_decl", "vardecl_var_list", "vardecl", "stmt", "assign_stmt",
  "stmt_list", "expr", "expr_base", "fncall_args", "expr_fncall", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,    60,    62,    43,    45,
      42,    47,    46,   281,    58,    59,    61,    44,    40,    41,
     123,   125
};
# endif

#define YYPACT_NINF -64

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-64)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -10,   -16,    -9,     1,     2,    31,   -64,   -10,   -64,   -64,
     -15,    15,    29,    34,   -64,   -64,     4,    25,    22,    26,
      43,    45,    46,    47,   -64,    10,    48,   -64,   -64,    49,
      51,    59,    41,     4,    38,    44,    50,    53,    54,   204,
     -64,   145,   -64,   204,   204,   204,    62,   -64,   -64,   204,
     204,   204,   -64,   172,   -64,    64,    70,    75,   -14,    90,
      79,   145,    52,   -64,    56,    95,    86,   -64,   -64,   -64,
     204,   -64,   -64,    67,   204,   204,   204,   204,   204,   204,
     204,   204,   204,   204,   204,   204,    65,   204,    68,   204,
      91,   204,    85,   -64,    96,    63,   120,   -64,   -64,   -64,
     -64,   -64,   172,    19,   -64,   181,   181,    -3,    -3,   188,
     188,    -3,    -3,    23,    23,    94,    94,   -64,    93,   121,
     107,   104,   204,   -64,   127,   -64,   108,   -64,   204,   -64,
     145,   204,   145,   -64,   110,   115,   172,   -64,   116,   136,
     204,   -64,   204,   145,   -64,   114,   -64,   145,   -64
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
      20,     0,     7,     0,     0,     0,    44,    57,    58,     0,
       0,     0,    11,    41,    59,     0,     0,     0,    44,     0,
       0,     0,     0,    39,     0,     0,     0,    13,    15,    17,
      62,    61,    60,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      22,     0,    26,    37,     0,     0,     0,    27,    29,    21,
      40,    28,    63,     0,    42,    46,    45,    49,    51,    48,
      47,    50,    52,    53,    54,    55,    56,    43,     0,     0,
       0,     0,     0,    38,     0,    36,     0,    34,     0,    65,
       0,     0,     0,    23,    24,     0,    64,    31,     0,    32,
       0,    35,     0,     0,    25,     0,    33,     0,    30
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -64,   -64,   149,   -64,   -64,   124,   -64,   -64,   -64,    80,
     -63,   -64,   102,   -39,   -40,   -64,   -64
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     5,     6,     7,     8,    24,    25,     9,    92,    62,
      63,    64,    65,    66,    53,   103,    54
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      52,    10,   100,    90,    67,    68,    69,     1,    11,    71,
      72,    73,     2,     3,     4,    20,    21,    22,    12,    13,
      94,    23,    91,    16,    70,    82,    83,    84,    85,    86,
     102,    14,    17,   100,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,    18,    33,   118,    34,
     121,    19,   123,    84,    85,    86,   128,    27,   129,    26,
      29,    28,    30,    31,    32,    35,    36,   137,    37,   139,
      74,    75,    76,    77,    78,    79,    38,    39,    41,    42,
     146,   126,   117,   133,   148,   119,    43,    97,   136,    44,
      45,    98,   138,    80,    81,    82,    83,    84,    85,    86,
      70,   144,    87,   145,    55,    56,   104,    46,    88,    57,
      47,    48,    58,    89,    59,    47,    48,    95,    49,    50,
      60,   101,   124,    49,    50,    93,    86,   122,    51,    55,
      56,   125,   130,    51,    57,    61,    99,    58,    90,    59,
      47,    48,   131,   132,   134,    60,   140,   135,    49,    50,
     141,   142,   143,   147,    55,    56,    15,    40,    51,    57,
      61,   127,    58,    96,    59,    47,    48,     0,   120,     0,
      60,     0,     0,    49,    50,    74,    75,    76,    77,    78,
      79,     0,     0,    51,     0,    61,    76,    77,    78,    79,
       0,     0,     0,    76,    77,     0,     0,     0,    80,    81,
      82,    83,    84,    85,    86,     0,     0,    80,    81,    82,
      83,    84,    85,    86,    80,    81,    82,    83,    84,    85,
      86,    46,     0,     0,    47,    48,     0,     0,     0,     0,
       0,     0,    49,    50,     0,     0,     0,     0,     0,     0,
       0,     0,    51
};

static const yytype_int16 yycheck[] =
{
      39,    17,    65,    17,    43,    44,    45,    17,    17,    49,
      50,    51,    22,    23,    24,    11,    12,    13,    17,    17,
      59,    17,    36,    38,    38,    28,    29,    30,    31,    32,
      70,     0,    17,    96,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    17,    37,    87,    39,
      89,    17,    91,    30,    31,    32,    37,    35,    39,    34,
      17,    35,    17,    17,    17,    17,    17,   130,    17,   132,
       3,     4,     5,     6,     7,     8,    17,    36,    40,    35,
     143,    18,    17,   122,   147,    17,    36,    35,   128,    36,
      36,    35,   131,    26,    27,    28,    29,    30,    31,    32,
      38,   140,    38,   142,     9,    10,    39,    17,    38,    14,
      20,    21,    17,    38,    19,    20,    21,    38,    28,    29,
      25,    35,    37,    28,    29,    35,    32,    36,    38,     9,
      10,    35,    39,    38,    14,    40,    41,    17,    17,    19,
      20,    21,    35,    39,    17,    25,    36,    39,    28,    29,
      35,    35,    16,    39,     9,    10,     7,    33,    38,    14,
      40,    41,    17,    61,    19,    20,    21,    -1,    88,    -1,
      25,    -1,    -1,    28,    29,     3,     4,     5,     6,     7,
       8,    -1,    -1,    38,    -1,    40,     5,     6,     7,     8,
      -1,    -1,    -1,     5,     6,    -1,    -1,    -1,    26,    27,
      28,    29,    30,    31,    32,    -1,    -1,    26,    27,    28,
      29,    30,    31,    32,    26,    27,    28,    29,    30,    31,
      32,    17,    -1,    -1,    20,    21,    -1,    -1,    -1,    -1,
      -1,    -1,    28,    29,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    38
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    17,    22,    23,    24,    43,    44,    45,    46,    49,
      17,    17,    17,    17,     0,    44,    38,    17,    17,    17,
      11,    12,    13,    17,    47,    48,    34,    35,    35,    17,
      17,    17,    17,    37,    39,    17,    17,    17,    17,    36,
      47,    40,    35,    36,    36,    36,    17,    20,    21,    28,
      29,    38,    55,    56,    58,     9,    10,    14,    17,    19,
      25,    40,    51,    52,    53,    54,    55,    55,    55,    55,
      38,    56,    56,    56,     3,     4,     5,     6,     7,     8,
      26,    27,    28,    29,    30,    31,    32,    38,    38,    38,
      17,    36,    50,    35,    55,    38,    54,    35,    35,    41,
      52,    35,    56,    57,    39,    56,    56,    56,    56,    56,
      56,    56,    56,    56,    56,    56,    56,    17,    55,    17,
      51,    55,    36,    55,    37,    35,    18,    41,    37,    39,
      39,    35,    39,    55,    17,    39,    56,    52,    55,    52,
      36,    35,    35,    16,    55,    55,    52,    39,    52
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    42,    43,    44,    44,    45,    45,    46,    46,    46,
      47,    47,    47,    47,    47,    47,    47,    47,    48,    48,
      48,    49,    50,    50,    50,    50,    51,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    53,    54,
      54,    55,    56,    56,    56,    56,    56,    56,    56,    56,
      56,    56,    56,    56,    56,    56,    56,    56,    56,    56,
      56,    56,    57,    57,    57,    58
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     2,     6,     4,     4,
       2,     4,     3,     5,     3,     5,     3,     5,     0,     1,
       3,     8,     1,     3,     3,     5,     2,     2,     2,     2,
       9,     5,     5,     7,     3,     5,     3,     2,     3,     1,
       2,     1,     3,     3,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     1,     1,     1,
       2,     2,     0,     1,     3,     4
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
#line 63 "lang.y" /* yacc.c:1646  */
    { ast->program = (yyvsp[0].node); (yyval.node) = (yyvsp[0].node); }
#line 1333 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 66 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1339 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 67 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = nullptr; }
#line 1345 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 73 "lang.y" /* yacc.c:1646  */
    { 
			// Create a list of program elements(only functions so far).
			(yyval.node) = ast->push<ProgramElem>(); 
			
			// A program element is not necessary a node. 
			// For example vertexAttribs/varyings/uniforms they just do a add themselves
			// to a container containing all the declarations.
			if((yyvsp[0].node) != nullptr) (yyval.node)->As<ProgramElem>().nodes.push_back((yyvsp[0].node)); 
		}
#line 1359 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 84 "lang.y" /* yacc.c:1646  */
    { 
			if ((yyvsp[0].node) != nullptr) (yyvsp[-1].node)->As<ProgramElem>().nodes.push_back((yyvsp[0].node)); 
			(yyval.node) = (yyvsp[-1].node);
		}
#line 1368 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 93 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = nullptr; ast->vertexAttribs.push_back({TypeDesc((yyvsp[-4].str_val)), (yyvsp[-3].str_val), (yyvsp[-1].str_val)}); }
#line 1374 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 94 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = nullptr; ast->varyings.push_back({TypeDesc((yyvsp[-2].str_val)), (yyvsp[-1].str_val)}); }
#line 1380 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 95 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = nullptr; ast->uniforms.push_back({TypeDesc((yyvsp[-2].str_val)), (yyvsp[-1].str_val)}); }
#line 1386 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 104 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<FnDeclArgVarDecl>(TypeDesc((yyvsp[-1].str_val)), (yyvsp[0].str_val), nullptr, FNAT_In   ); }
#line 1392 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 105 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<FnDeclArgVarDecl>(TypeDesc((yyvsp[-3].str_val)), (yyvsp[-2].str_val), (yyvsp[0].node)     , FNAT_In   ); }
#line 1398 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 106 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<FnDeclArgVarDecl>(TypeDesc((yyvsp[-1].str_val)), (yyvsp[0].str_val), nullptr, FNAT_In	); }
#line 1404 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 107 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<FnDeclArgVarDecl>(TypeDesc((yyvsp[-3].str_val)), (yyvsp[-2].str_val), (yyvsp[0].node)     , FNAT_In	); }
#line 1410 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 108 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<FnDeclArgVarDecl>(TypeDesc((yyvsp[-1].str_val)), (yyvsp[0].str_val), nullptr, FNAT_Out  ); }
#line 1416 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 109 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<FnDeclArgVarDecl>(TypeDesc((yyvsp[-3].str_val)), (yyvsp[-2].str_val), (yyvsp[0].node)     , FNAT_Out  ); }
#line 1422 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 110 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<FnDeclArgVarDecl>(TypeDesc((yyvsp[-1].str_val)), (yyvsp[0].str_val), nullptr, FNAT_InOut); }
#line 1428 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 111 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<FnDeclArgVarDecl>(TypeDesc((yyvsp[-3].str_val)), (yyvsp[-2].str_val), (yyvsp[0].node)     , FNAT_InOut); }
#line 1434 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 119 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<FuncDecl>(); }
#line 1440 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 120 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<FuncDecl>(); ((FuncDecl*)(yyval.node))->args.push_back((yyvsp[0].node)); }
#line 1446 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 121 "lang.y" /* yacc.c:1646  */
    { (yyvsp[-2].node)->As<FuncDecl>().args.push_back((yyvsp[0].node)); (yyval.node) = (yyvsp[-2].node); }
#line 1452 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 128 "lang.y" /* yacc.c:1646  */
    { 
		auto& funcDecl = (yyvsp[-4].node)->As<FuncDecl>();
		funcDecl.retType = TypeDesc((yyvsp[-7].str_val));
		funcDecl.name = (yyvsp[-6].str_val);
		funcDecl.stmt = (yyvsp[-1].node);
		(yyval.node) = (yyvsp[-4].node);
	}
#line 1464 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 144 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<VarDecl>(TypeDesc(), (yyvsp[0].str_val), nullptr); }
#line 1470 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 145 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<VarDecl>(TypeDesc(), (yyvsp[-2].str_val), (yyvsp[0].node)); }
#line 1476 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 146 "lang.y" /* yacc.c:1646  */
    { 
			(yyvsp[-2].node)->As<VarDecl>().ident.push_back((yyvsp[0].str_val));
			(yyvsp[-2].node)->As<VarDecl>().expr.push_back(nullptr);
			(yyval.node) = (yyvsp[-2].node);
		}
#line 1486 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 151 "lang.y" /* yacc.c:1646  */
    { 
			(yyval.node) = (yyvsp[-4].node); 
			(yyval.node)->As<VarDecl>().ident.push_back((yyvsp[-2].str_val));
			(yyval.node)->As<VarDecl>().expr.push_back((yyvsp[0].node));
		}
#line 1496 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 159 "lang.y" /* yacc.c:1646  */
    { (yyvsp[0].node)->As<VarDecl>().type = TypeDesc((yyvsp[-1].str_val)); (yyval.node) = (yyvsp[0].node); }
#line 1502 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 167 "lang.y" /* yacc.c:1646  */
    { (yyvsp[-1].node)->hasSemicolon = true; ; (yyval.node) = (yyvsp[-1].node); }
#line 1508 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 168 "lang.y" /* yacc.c:1646  */
    { (yyvsp[-1].node)->hasSemicolon = true; (yyval.node) = (yyvsp[-1].node); }
#line 1514 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 169 "lang.y" /* yacc.c:1646  */
    { (yyvsp[-1].node)->hasSemicolon = true; (yyval.node) = (yyvsp[-1].node); }
#line 1520 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 170 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<StmtFor>((yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1526 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 171 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<StmtWhile>((yyvsp[-2].node), (yyvsp[0].node)); }
#line 1532 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 172 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<StmtIf>((yyvsp[-2].node), (yyvsp[0].node), nullptr); }
#line 1538 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 173 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<StmtIf>((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1544 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 174 "lang.y" /* yacc.c:1646  */
    { (yyvsp[-1].node)->inBlock = true; (yyval.node) = (yyvsp[-1].node); }
#line 1550 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 175 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<StmtNativeCode>((yyvsp[-2].str_val)); }
#line 1556 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 176 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<StmtReturn>((yyvsp[-1].node)); }
#line 1562 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 177 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<StmtReturn>(); }
#line 1568 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 182 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<Assign>((yyvsp[-2].str_val).c_str(), (yyvsp[0].node)); }
#line 1574 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 187 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<StmtList>(); (yyval.node)->As<StmtList>().nodes.push_back((yyvsp[0].node)); }
#line 1580 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 188 "lang.y" /* yacc.c:1646  */
    { 
			(yyval.node) = (yyvsp[-1].node);
			(yyvsp[-1].node)->As<StmtList>().nodes.push_back( {(yyvsp[0].node)} );
		}
#line 1589 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 198 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); ast->addDeduct((yyvsp[0].node)); }
#line 1595 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 201 "lang.y" /* yacc.c:1646  */
    { (yyvsp[-1].node)->inParens = true; (yyval.node) = (yyvsp[-1].node); }
#line 1601 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 202 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<ExprMemberAccess>((yyvsp[-2].node), (yyvsp[0].str_val)); }
#line 1607 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 203 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<Ident>((yyvsp[0].str_val)); }
#line 1613 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 204 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<ExprBin>(EBT_Or, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1619 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 205 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<ExprBin>(EBT_And, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1625 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 206 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<ExprBin>(EBT_NEquals, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1631 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 207 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<ExprBin>(EBT_Equals, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1637 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 208 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<ExprBin>(EBT_LEquals, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1643 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 209 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<ExprBin>(EBT_Less, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1649 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 210 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<ExprBin>(EBT_GEquals, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1655 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 211 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<ExprBin>(EBT_Greater, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1661 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 212 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<ExprBin>(EBT_Add, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1667 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 213 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<ExprBin>(EBT_Sub, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1673 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 214 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<ExprBin>(EBT_Mul, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1679 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 215 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<ExprBin>(EBT_Div, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1685 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 216 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<ExprLiteral>((yyvsp[0].float_val)); }
#line 1691 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 217 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<ExprLiteral>((yyvsp[0].int_val)); }
#line 1697 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 218 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1703 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 219 "lang.y" /* yacc.c:1646  */
    { (yyvsp[0].node)->exprSign *= -1; (yyval.node) = (yyvsp[0].node); }
#line 1709 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 220 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1715 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 226 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<FuncCall>(); }
#line 1721 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 228 "lang.y" /* yacc.c:1646  */
    { 
				Node* fnCall = ast->push<FuncCall>();
				fnCall->As<FuncCall>().args.push_back((yyvsp[0].node)); 
				(yyval.node) = fnCall;
			}
#line 1731 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 234 "lang.y" /* yacc.c:1646  */
    { (yyvsp[-2].node)->As<FuncCall>().args.push_back((yyvsp[0].node)); (yyval.node) = (yyvsp[-2].node); }
#line 1737 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 238 "lang.y" /* yacc.c:1646  */
    { 
			(yyvsp[-1].node)->As<FuncCall>().fnName = (yyvsp[-3].str_val);
			(yyval.node) = (yyvsp[-1].node); 
		}
#line 1746 "lang.tab.cpp" /* yacc.c:1646  */
    break;


#line 1750 "lang.tab.cpp" /* yacc.c:1646  */
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
#line 247 "lang.y" /* yacc.c:1906  */


void yyerror (yyscan_t yyscanner, char const *msg){
    fprintf(stderr, "%s\n", msg);
}

void yyerror (yyscan_t yyscanner, Ast* ast, char const *msg) {
	yyerror(yyscanner, msg);
}
