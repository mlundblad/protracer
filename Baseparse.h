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
/* Line 1285 of yacc.c.  */
#line 126 "Baseparse.h"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;



