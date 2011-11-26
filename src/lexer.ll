/* -*-C++-*- */

%option noyywrap

%{

/*
 * This file is part of Protracer
 *
 * Protracer is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Protracer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Protracer.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <string.h>

#include "parser.h"

#define YY_NO_UNPUT

int linecount = 1;
%}

digit	[0-9]
number	"-"?{digit}+("."{digit}+)?
name	[_a-zA-Z]+

%%
"//"[^\n]*\n 	{ linecount++; } /* ignore comments, but count line */

abs             return KEY_ABS;
acos            return KEY_ACOS;
acosh           return KEY_ACOSH;
asin            return KEY_ASIN;
asinh           return KEY_ASINH;
atan            return KEY_ATAN;
atanh           return KEY_ATANH;
atan2           return KEY_ATAN2;
background	return KEY_BACKGROUND;
blue		return KEY_BLUE;
camera		return KEY_CAMERA;
ceil            return KEY_CEIL;
color		return KEY_COLOR;
colour		return KEY_COLOR;
cos             return KEY_COS;
cosh            return KEY_COSH;
degrees         return KEY_DEGREES;
diffuse		return KEY_DIFFUSE;
disc            return KEY_DISC;
div             return KEY_DIV;
equator		return KEY_EQUATOR;
exp             return KEY_EXP;
false           return KEY_FALSE;
finish		return KEY_FINISH;
floor           return KEY_FLOOR;
green		return KEY_GREEN;
image_map	return KEY_IMAGE;
int             return KEY_INT;
light_source	return KEY_LIGHT;
ln              return KEY_LN;
log             return KEY_LOG;
location	return KEY_LOCATION;
look_at		return KEY_LOOK;
max             return KEY_MAX;
min             return KEY_MIN;
mod             return KEY_MOD;
no              return KEY_NO;
off             return KEY_OFF;
on              return KEY_ON;
pi              return KEY_PI;
pigment		return KEY_PIGMENT;
plane		return KEY_PLANE;
plane_point	return KEY_PLANEPNT;
pole		return KEY_POLE;
pow             return KEY_POW;
ppm		return KEY_PPM;
radians         return KEY_RADIANS;
red		return KEY_RED;
reflection	return KEY_REFLECTION;
rgb		return KEY_RGB;
select          return KEY_SELECT;
sin             return KEY_SIN;
sinh            return KEY_SINH;
sky		return KEY_SKY;
sphere		return KEY_SPHERE;
tan             return KEY_TAN;
tanh            return KEY_TANH;
triangle	return KEY_TRIANGLE;
triangle_point	return KEY_TRIANGLEPNT;
true            return KEY_TRUE;
vdot            return KEY_VDOT;
vlength         return KEY_VLENGTH;
x               return KEY_X;
y               return KEY_Y;
yes             return KEY_YES;
z               return KEY_Z;

"{"		return LBRACE;
"}"		return RBRACE;
"<"		return LANGLE;
">"		return RANGLE;
"("             return LPAREN;
")"             return RPAREN;
","		return COMMA;
"+"             return PLUS;
"-"             return MINUS;
"*"             return TIMES;
"/"             return DIVIDED;
"."             return DOT;

{number}	{ yylval.value = atof(yytext); return NUMBER; }
\"[^\"]*\"	{ yylval.string = strdup(yytext+1);
		  yylval.string[strlen(yytext+1)-1] = '\0';
	          return STRING;
		}

{name}		return NAME;
\n 		{ linecount++; }
[ \t\r]		;

.		return UNCAUGHT;
%%
