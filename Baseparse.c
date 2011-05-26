/* A Bison parser, made by GNU Bison 1.875d.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004 Free Software Foundation, Inc.

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
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     LBRACE = 258,
     RBRACE = 259,
     LANGLE = 260,
     RANGLE = 261,
     COMMA = 262,
     NUMBER = 263,
     STRING = 264,
     NAME = 265,
     UNCAUGHT = 266,
     KEY_SPHERE = 267,
     KEY_PIGMENT = 268,
     KEY_COLOR = 269,
     KEY_FINISH = 270,
     KEY_TRIANGLE = 271,
     KEY_TRIANGLEPNT = 272,
     KEY_DIFFUSE = 273,
     KEY_REFLECTION = 274,
     KEY_RED = 275,
     KEY_GREEN = 276,
     KEY_BLUE = 277,
     KEY_LOCATION = 278,
     KEY_LOOK = 279,
     KEY_BACKGROUND = 280,
     KEY_CAMERA = 281,
     KEY_RGB = 282,
     KEY_SKY = 283,
     KEY_LIGHT = 284,
     KEY_PLANE = 285,
     KEY_PLANEPNT = 286,
     KEY_IMAGE = 287,
     KEY_PPM = 288,
     KEY_POLE = 289,
     KEY_EQUATOR = 290
   };
#endif
#define LBRACE 258
#define RBRACE 259
#define LANGLE 260
#define RANGLE 261
#define COMMA 262
#define NUMBER 263
#define STRING 264
#define NAME 265
#define UNCAUGHT 266
#define KEY_SPHERE 267
#define KEY_PIGMENT 268
#define KEY_COLOR 269
#define KEY_FINISH 270
#define KEY_TRIANGLE 271
#define KEY_TRIANGLEPNT 272
#define KEY_DIFFUSE 273
#define KEY_REFLECTION 274
#define KEY_RED 275
#define KEY_GREEN 276
#define KEY_BLUE 277
#define KEY_LOCATION 278
#define KEY_LOOK 279
#define KEY_BACKGROUND 280
#define KEY_CAMERA 281
#define KEY_RGB 282
#define KEY_SKY 283
#define KEY_LIGHT 284
#define KEY_PLANE 285
#define KEY_PLANEPNT 286
#define KEY_IMAGE 287
#define KEY_PPM 288
#define KEY_POLE 289
#define KEY_EQUATOR 290




/* Copy the first part of user declarations.  */
#line 1 "Baseparse.y"

/*************************************************************************\
|  File: Baseparse.y                                                      |
|                                                                         |
|  The pov-file parser                                                    |
|                                                                         |
\*************************************************************************/



#include <stdlib.h>


#include "Vector.h"
#include "Plane.h"
#include "Sphere.h"
#include "Triangle.h"
#include "ObjectList.h"
#include "LightList.h"
#include "Camera.h"
#include "Color.h"

#include "SphereOptions.h"
#include "ObjectMods.h"
#include "Finish.h"
#include "Pigment.h"
#include "Bitmap.h"
#include "PPMFile.h"

#include "Parameters.h"

Parameters global_parameters;
ObjectList global_objectList;
LightList  global_lightList;
Color      global_background;
Camera     global_camera;


extern char *yytext;
extern int linecount;
extern int yylex(void);


PPMFile    global_image_file;


int yyerror(char *s);


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 50 "Baseparse.y"
typedef union YYSTYPE {
    double	value;		        /* for numbers */
    char		*string;	/* for names */
    Vector	Vector;
    Sphere      Sphere;
    Triangle    Triangle;
    Plane       Plane;
    Object      Object;
    ObjectList  ObjectList;
    Camera      Camera;
    Color       Color;
    SphereOptions   SphereOptions;
    ObjectMods  ObjectMods;
    Finish      Finish;
    Pigment     Pigment;
    Bitmap      Bitmap;
    Light       Light;
} YYSTYPE;
/* Line 191 of yacc.c.  */
#line 214 "Baseparse.c"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 214 of yacc.c.  */
#line 226 "Baseparse.c"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

# ifndef YYFREE
#  define YYFREE free
# endif
# ifndef YYMALLOC
#  define YYMALLOC malloc
# endif

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   define YYSTACK_ALLOC alloca
#  endif
# else
#  if defined (alloca) || defined (_ALLOCA_H)
#   define YYSTACK_ALLOC alloca
#  else
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (defined (YYSTYPE_IS_TRIVIAL) && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short int yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short int) + sizeof (YYSTYPE))			\
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined (__GNUC__) && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short int yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  25
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   101

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  36
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  23
/* YYNRULES -- Number of rules. */
#define YYNRULES  38
/* YYNRULES -- Number of states. */
#define YYNSTATES  115

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   290

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
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
      35
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned char yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    12,    14,    16,    18,
      20,    25,    33,    41,    49,    58,    59,    64,    74,    84,
      87,    88,    90,    95,   100,   106,   107,   109,   115,   116,
     118,   121,   122,   124,   127,   135,   139,   149,   154
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      37,     0,    -1,    38,    -1,    37,    38,    -1,    42,    -1,
      44,    -1,    41,    -1,    56,    -1,    57,    -1,    39,    -1,
      29,     3,    40,     4,    -1,     5,    58,     7,    58,     7,
      58,     6,    -1,    30,     3,    40,     7,    58,    45,     4,
      -1,    31,     3,    40,     7,    40,    45,     4,    -1,    12,
       3,    40,     7,    58,    43,    45,     4,    -1,    -1,    34,
      40,    35,    40,    -1,    16,     3,    40,     7,    40,     7,
      40,    45,     4,    -1,    17,     3,    40,     7,    40,     7,
      40,    45,     4,    -1,    46,    49,    -1,    -1,    47,    -1,
      13,     3,    55,     4,    -1,    13,     3,    48,     4,    -1,
      32,     3,    33,     9,     4,    -1,    -1,    50,    -1,    15,
       3,    51,    53,     4,    -1,    -1,    52,    -1,    18,    58,
      -1,    -1,    54,    -1,    19,    58,    -1,    14,    20,    58,
      21,    58,    22,    58,    -1,    14,    27,    40,    -1,    26,
       3,    23,    40,    28,    40,    24,    40,     4,    -1,    25,
       3,    55,     4,    -1,     8,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,   114,   114,   115,   119,   122,   125,   128,   129,   130,
     136,   144,   150,   165,   177,   190,   198,   203,   220,   238,
     242,   248,   252,   253,   257,   265,   267,   271,   277,   278,
     282,   285,   286,   290,   294,   301,   310,   327,   334
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "LBRACE", "RBRACE", "LANGLE", "RANGLE",
  "COMMA", "NUMBER", "STRING", "NAME", "UNCAUGHT", "KEY_SPHERE",
  "KEY_PIGMENT", "KEY_COLOR", "KEY_FINISH", "KEY_TRIANGLE",
  "KEY_TRIANGLEPNT", "KEY_DIFFUSE", "KEY_REFLECTION", "KEY_RED",
  "KEY_GREEN", "KEY_BLUE", "KEY_LOCATION", "KEY_LOOK", "KEY_BACKGROUND",
  "KEY_CAMERA", "KEY_RGB", "KEY_SKY", "KEY_LIGHT", "KEY_PLANE",
  "KEY_PLANEPNT", "KEY_IMAGE", "KEY_PPM", "KEY_POLE", "KEY_EQUATOR",
  "$accept", "scene", "item", "light", "vector", "plane", "sphere",
  "sphere_opt", "triangle", "object_mods", "opt_pigment", "pigment",
  "image", "opt_finish", "finish", "opt_diffuse", "diffuse",
  "opt_reflection", "reflection", "color", "camera", "background",
  "number", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short int yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    36,    37,    37,    38,    38,    38,    38,    38,    38,
      39,    40,    41,    41,    42,    43,    43,    44,    44,    45,
      46,    46,    47,    47,    48,    49,    49,    50,    51,    51,
      52,    53,    53,    54,    55,    55,    56,    57,    58
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       4,     7,     7,     7,     8,     0,     4,     9,     9,     2,
       0,     1,     4,     4,     5,     0,     1,     5,     0,     1,
       2,     0,     1,     2,     7,     3,     9,     4,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       2,     9,     6,     4,     5,     7,     8,     0,     0,     0,
       0,     0,     0,     0,     0,     1,     3,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    38,     0,     0,
       0,     0,     0,     0,    37,     0,    10,     0,     0,     0,
      15,     0,     0,     0,    35,     0,    20,    20,     0,     0,
      20,     0,     0,     0,     0,     0,     0,    25,    21,     0,
       0,     0,     0,    20,    20,     0,     0,     0,    12,     0,
      19,    26,    13,     0,     0,    14,     0,     0,     0,     0,
       0,     0,     0,    28,    11,    16,    17,    18,    34,    36,
       0,    23,    22,     0,    31,    29,     0,    30,     0,     0,
      32,     0,    33,    27,    24
};

/* YYDEFGOTO[NTERM-NUM]. */
static const yysigned_char yydefgoto[] =
{
      -1,     9,    10,    11,    28,    12,    13,    60,    14,    66,
      67,    68,    91,    80,    81,   104,   105,   109,   110,    32,
      15,    16,    38
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -52
static const yysigned_char yypact[] =
{
      58,    -2,     2,     4,     9,    12,    13,    18,    22,    51,
     -52,   -52,   -52,   -52,   -52,   -52,   -52,    21,    21,    21,
      15,     7,    21,    21,    21,   -52,   -52,    19,    25,    26,
      27,   -16,    33,    21,    35,    34,    37,   -52,    38,    19,
      21,    21,    19,    21,   -52,    14,   -52,    19,    21,    19,
       6,    39,    40,    31,   -52,    21,    42,    42,    41,    21,
      42,    21,    21,    19,    29,    55,    56,    44,   -52,    57,
      19,    30,    62,    42,    42,    50,    21,   -12,   -52,    59,
     -52,   -52,   -52,    67,    21,   -52,    74,    81,    19,    82,
      87,    88,    89,    73,   -52,   -52,   -52,   -52,   -52,   -52,
      61,   -52,   -52,    19,    76,   -52,    90,   -52,    19,    92,
     -52,    93,   -52,   -52,   -52
};

/* YYPGOTO[NTERM-NUM].  */
static const yysigned_char yypgoto[] =
{
     -52,   -52,    91,   -52,    -5,   -52,   -52,   -52,   -52,   -51,
     -52,   -52,   -52,   -52,   -52,   -52,   -52,   -52,   -52,    24,
     -52,   -52,   -39
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const unsigned char yytable[] =
{
      50,    17,    31,    53,    42,    18,    69,    19,    56,    72,
      58,    43,    20,    29,    30,    21,    22,    34,    35,    36,
      90,    23,    86,    87,    75,    24,    27,    37,    45,    31,
      33,    83,    39,    40,    41,    51,    52,    44,    54,    46,
      59,    47,    55,    57,    48,    49,    61,    62,    70,    98,
      64,    25,    63,    76,    71,    65,    73,    74,    77,    79,
      78,    82,    93,     1,   107,    84,    85,     2,     3,   112,
       1,    89,    88,    94,     2,     3,     4,     5,    96,    95,
       6,     7,     8,     4,     5,    97,    99,     6,     7,     8,
     100,   103,   101,   102,   106,   108,   113,   114,     0,   111,
      26,    92
};

static const yysigned_char yycheck[] =
{
      39,     3,    14,    42,    20,     3,    57,     3,    47,    60,
      49,    27,     3,    18,    19,     3,     3,    22,    23,    24,
      32,     3,    73,    74,    63,     3,     5,     8,    33,    14,
      23,    70,     7,     7,     7,    40,    41,     4,    43,     4,
      34,     7,    28,    48,     7,     7,     7,     7,     7,    88,
      55,     0,    21,    24,    59,    13,    61,    62,     3,    15,
       4,     4,     3,    12,   103,    35,     4,    16,    17,   108,
      12,    76,    22,     6,    16,    17,    25,    26,     4,    84,
      29,    30,    31,    25,    26,     4,     4,    29,    30,    31,
       3,    18,     4,     4,    33,    19,     4,     4,    -1,     9,
       9,    77
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    12,    16,    17,    25,    26,    29,    30,    31,    37,
      38,    39,    41,    42,    44,    56,    57,     3,     3,     3,
       3,     3,     3,     3,     3,     0,    38,     5,    40,    40,
      40,    14,    55,    23,    40,    40,    40,     8,    58,     7,
       7,     7,    20,    27,     4,    40,     4,     7,     7,     7,
      58,    40,    40,    58,    40,    28,    58,    40,    58,    34,
      43,     7,     7,    21,    40,    13,    45,    46,    47,    45,
       7,    40,    45,    40,    40,    58,    24,     3,     4,    15,
      49,    50,     4,    58,    35,     4,    45,    45,    22,    40,
      32,    48,    55,     3,     6,    40,     4,     4,    58,     4,
       3,     4,     4,    18,    51,    52,    33,    58,    19,    53,
      54,     9,    58,     4,     4
};

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)		\
   ((Current).first_line   = (Rhs)[1].first_line,	\
    (Current).first_column = (Rhs)[1].first_column,	\
    (Current).last_line    = (Rhs)[N].last_line,	\
    (Current).last_column  = (Rhs)[N].last_column)
#endif

/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (0)

# define YYDSYMPRINT(Args)			\
do {						\
  if (yydebug)					\
    yysymprint Args;				\
} while (0)

# define YYDSYMPRINTF(Title, Token, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr, 					\
                  Token, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short int *bottom, short int *top)
#else
static void
yy_stack_print (bottom, top)
    short int *bottom;
    short int *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
             yyrule - 1, yylno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname [yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname [yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (Rule);		\
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YYDSYMPRINT(Args)
# define YYDSYMPRINTF(Title, Token, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if defined (YYMAXDEPTH) && YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

#endif /* !YYERROR_VERBOSE */



#if YYDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (yytype < YYNTOKENS)
    {
      YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
# ifdef YYPRINT
      YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
    }
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yydestruct (int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yytype, yyvaluep)
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  switch (yytype)
    {

      default:
        break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short int yyssa[YYINITDEPTH];
  short int *yyss = yyssa;
  register short int *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;



#define YYPOPSTACK   (yyvsp--, yyssp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;


  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short int *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	short int *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YYDSYMPRINTF ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %s, ", yytname[yytoken]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;


  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
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
     `$$ = $1'.

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
#line 114 "Baseparse.y"
    { ;}
    break;

  case 3:
#line 115 "Baseparse.y"
    { ;}
    break;

  case 4:
#line 119 "Baseparse.y"
    { global_objectList = 
                           ObjectList_insert( Object_createSphere( yyvsp[0].Sphere ),
                                              global_objectList); ;}
    break;

  case 5:
#line 122 "Baseparse.y"
    { global_objectList  = 
                           ObjectList_insert( Object_createTriangle( yyvsp[0].Triangle ),
                                              global_objectList); ;}
    break;

  case 6:
#line 125 "Baseparse.y"
    { global_objectList = 
                           ObjectList_insert( Object_createPlane( yyvsp[0].Plane ),
                                              global_objectList); ;}
    break;

  case 7:
#line 128 "Baseparse.y"
    { ;}
    break;

  case 8:
#line 129 "Baseparse.y"
    { ;}
    break;

  case 9:
#line 130 "Baseparse.y"
    { global_lightList = 
                           LightList_insert(  yyvsp[0].Light,
                                              global_lightList); ;}
    break;

  case 10:
#line 138 "Baseparse.y"
    { /*printf("Light at "); Vector_print($3); printf("\n");*/
                 yyval.Light = Light_create( yyvsp[-1].Vector );
	       ;}
    break;

  case 11:
#line 145 "Baseparse.y"
    { /*printf("Vector: %f %f %f\n", $2, $4, $6 );*/
                                     yyval.Vector = Vector_createFromCartesian(yyvsp[-5].value, yyvsp[-3].value, yyvsp[-1].value); ;}
    break;

  case 12:
#line 153 "Baseparse.y"
    { /*printf("Plane with normal=");
		 Vector_print($3);
		 printf(", dist=%.2f\n", $5);*/
                 yyval.Plane = Plane_create(yyvsp[-4].Vector, Vector_createFromCartesian(0, 0, yyvsp[-2].value), 
				   ObjectMods_pigment( yyvsp[-1].ObjectMods ),
                                   Finish_reflection( ObjectMods_finish( yyvsp[-1].ObjectMods )),
                                   Finish_diffuse( ObjectMods_finish( yyvsp[-1].ObjectMods )) );
	       ;}
    break;

  case 13:
#line 168 "Baseparse.y"
    { /*printf("Plane with normal="); Vector_print($3);
		   printf(" at "); Vector_print($5); printf("\n");*/
                 yyval.Plane = Plane_create(yyvsp[-2].Vector, yyvsp[-4].Vector, ObjectMods_pigment( yyvsp[-1].ObjectMods ),
                                   Finish_reflection( ObjectMods_finish(yyvsp[-1].ObjectMods) ),
                                   Finish_diffuse( ObjectMods_finish(yyvsp[-1].ObjectMods)) );
	       ;}
    break;

  case 14:
#line 179 "Baseparse.y"
    { /*fprintf(stderr, "Sphere at ");
		   Vector_print($3);
		 printf(", radius %.2f\n", $5);*/
                 yyval.Sphere = Sphere_create(yyvsp[-5].Vector, yyvsp[-3].value, SphereOptions_pole(yyvsp[-2].SphereOptions), 
                                    SphereOptions_equator(yyvsp[-2].SphereOptions), 
                                    ObjectMods_pigment( yyvsp[-1].ObjectMods ), 
                                    Finish_reflection(ObjectMods_finish( yyvsp[-1].ObjectMods )),
                                    Finish_diffuse(ObjectMods_finish( yyvsp[-1].ObjectMods )));
	       ;}
    break;

  case 15:
#line 190 "Baseparse.y"
    { yyval.SphereOptions = SphereOptions_create(
                     Vector_createFromCartesian(POLE_DEFAULT_X, 
                                                POLE_DEFAULT_Y,
                                                POLE_DEFAULT_Z), 
                     Vector_createFromCartesian(EQUATOR_DEFAULT_X,
                                                EQUATOR_DEFAULT_Y,
                                                EQUATOR_DEFAULT_Z) ); ;}
    break;

  case 16:
#line 198 "Baseparse.y"
    { yyval.SphereOptions = 
                                                SphereOptions_create( yyvsp[-2].Vector, yyvsp[0].Vector );;}
    break;

  case 17:
#line 208 "Baseparse.y"
    { /*printf("Triangle\n"); */
                 yyval.Triangle = Triangle_createFromPoints(
                     yyvsp[-6].Vector, yyvsp[-4].Vector, yyvsp[-2].Vector,
                     ObjectMods_pigment(yyvsp[-1].ObjectMods),
                     Finish_reflection( ObjectMods_finish(yyvsp[-1].ObjectMods) ),
                     Finish_diffuse( ObjectMods_finish(yyvsp[-1].ObjectMods)) );
               ;}
    break;

  case 18:
#line 225 "Baseparse.y"
    { /*printf("Triangle(p)\n");*/ 
                 yyval.Triangle = 
                     Triangle_createFromPointAndVectors(
                         yyvsp[-6].Vector, yyvsp[-4].Vector, yyvsp[-2].Vector, 
                         ObjectMods_pigment(yyvsp[-1].ObjectMods),
                         Finish_reflection(
                             ObjectMods_finish(yyvsp[-1].ObjectMods)),
                         Finish_diffuse(
                             ObjectMods_finish(yyvsp[-1].ObjectMods)));
               ;}
    break;

  case 19:
#line 239 "Baseparse.y"
    { yyval.ObjectMods = ObjectMods_create( yyvsp[-1].Pigment, yyvsp[0].Finish); ;}
    break;

  case 20:
#line 242 "Baseparse.y"
    { yyval.Pigment = 
                  Pigment_createColor( Color_createFromRGB( PIGMENT_DEFAULT_RED,
                                                            PIGMENT_DEFAULT_GREEN, 
                                                            PIGMENT_DEFAULT_BLUE));
                ;}
    break;

  case 21:
#line 248 "Baseparse.y"
    { yyval.Pigment = yyvsp[0].Pigment ;}
    break;

  case 22:
#line 252 "Baseparse.y"
    { yyval.Pigment = Pigment_createColor( yyvsp[-1].Color );;}
    break;

  case 23:
#line 253 "Baseparse.y"
    { yyval.Pigment = Pigment_createBitmap( yyvsp[-1].Bitmap ); ;}
    break;

  case 24:
#line 257 "Baseparse.y"
    { global_image_file = 
                                                     PPMFile_openIn( yyvsp[-1].string );
                                                 yyval.Bitmap = PPMFile_readBitmap( 
                                                     global_image_file );
                                                 PPMFile_close( 
                                                     global_image_file ); ;}
    break;

  case 25:
#line 265 "Baseparse.y"
    { yyval.Finish = Finish_create( DIFFUSE_DEFAULT, REFLECTION_DEFAULT ); ;}
    break;

  case 26:
#line 267 "Baseparse.y"
    { yyval.Finish = yyvsp[0].Finish ;}
    break;

  case 27:
#line 274 "Baseparse.y"
    { yyval.Finish = Finish_create( yyvsp[-2].value, yyvsp[-1].value ); ;}
    break;

  case 28:
#line 277 "Baseparse.y"
    { yyval.value = DIFFUSE_DEFAULT ;}
    break;

  case 29:
#line 278 "Baseparse.y"
    { yyval.value = yyvsp[0].value ;}
    break;

  case 30:
#line 282 "Baseparse.y"
    { yyval.value = yyvsp[0].value ;}
    break;

  case 31:
#line 285 "Baseparse.y"
    { yyval.value = REFLECTION_DEFAULT ;}
    break;

  case 32:
#line 286 "Baseparse.y"
    { yyval.value = yyvsp[0].value ;}
    break;

  case 33:
#line 290 "Baseparse.y"
    { yyval.value = yyvsp[0].value ;}
    break;

  case 34:
#line 297 "Baseparse.y"
    { yyval.Color = Color_createFromRGB( yyvsp[-4].value * COLOR_COMPONENT_MAX, 
                                                    yyvsp[-2].value * COLOR_COMPONENT_MAX, 
                                                    yyvsp[0].value * COLOR_COMPONENT_MAX); ;}
    break;

  case 35:
#line 301 "Baseparse.y"
    { yyval.Color = Color_createFromRGB( Vector_x( yyvsp[0].Vector ) * 
                                                             COLOR_COMPONENT_MAX,
                                                             Vector_y( yyvsp[0].Vector ) * 
                                                             COLOR_COMPONENT_MAX,
                                                             Vector_z( yyvsp[0].Vector ) * 
                                                             COLOR_COMPONENT_MAX); ;}
    break;

  case 36:
#line 314 "Baseparse.y"
    { /*printf("Camera\n");*/
                 global_camera = 
                     Camera_create( yyvsp[-5].Vector, yyvsp[-1].Vector, yyvsp[-3].Vector, 
                                    Parameters_zoom( global_parameters ),
                                    Parameters_worldWidth( global_parameters),
                                    Parameters_worldHeight( global_parameters ),
                                    Parameters_pixelWidth( global_parameters ),
                                    Parameters_pixelHeight( global_parameters )
                     ); 
		 /*printf("camera created\n");*/ ;}
    break;

  case 37:
#line 329 "Baseparse.y"
    { /*printf("Background\n"); */
                 global_background = yyvsp[-1].Color; ;}
    break;

  case 38:
#line 334 "Baseparse.y"
    { yyval.value = yyvsp[0].value; ;}
    break;


    }

/* Line 1010 of yacc.c.  */
#line 1460 "Baseparse.c"

  yyvsp -= yylen;
  yyssp -= yylen;


  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  int yytype = YYTRANSLATE (yychar);
	  const char* yyprefix;
	  char *yymsg;
	  int yyx;

	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  int yyxbegin = yyn < 0 ? -yyn : 0;

	  /* Stay within bounds of both yycheck and yytname.  */
	  int yychecklim = YYLAST - yyn;
	  int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
	  int yycount = 0;

	  yyprefix = ", expecting ";
	  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      {
		yysize += yystrlen (yyprefix) + yystrlen (yytname [yyx]);
		yycount += 1;
		if (yycount == 5)
		  {
		    yysize = 0;
		    break;
		  }
	      }
	  yysize += (sizeof ("syntax error, unexpected ")
		     + yystrlen (yytname[yytype]));
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yyprefix = ", expecting ";
		  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			yyp = yystpcpy (yyp, yyprefix);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yyprefix = " or ";
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("syntax error; also virtual memory exhausted");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror ("syntax error");
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* If at end of input, pop the error token,
	     then the rest of the stack, then return failure.  */
	  if (yychar == YYEOF)
	     for (;;)
	       {
		 YYPOPSTACK;
		 if (yyssp == yyss)
		   YYABORT;
		 YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
		 yydestruct (yystos[*yyssp], yyvsp);
	       }
        }
      else
	{
	  YYDSYMPRINTF ("Error: discarding", yytoken, &yylval, &yylloc);
	  yydestruct (yytoken, &yylval);
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

#ifdef __GNUC__
  /* Pacify GCC when the user code never invokes YYERROR and the label
     yyerrorlab therefore never appears in user code.  */
  if (0)
     goto yyerrorlab;
#endif

  yyvsp -= yylen;
  yyssp -= yylen;
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
      yydestruct (yystos[yystate], yyvsp);
      YYPOPSTACK;
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;


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

#ifndef yyoverflow
/*----------------------------------------------.
| yyoverflowlab -- parser overflow comes here.  |
`----------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 337 "Baseparse.y"


int
yyerror(char *s) {
  fprintf(stderr, "** line %d:%s\n", linecount, s);
  return 1;
}

