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
exponent [eE]
number	"-"?{digit}*("."{digit}+)?({exponent}("-"|"+")?{digit}+)?
alpha    [_a-zA-Z]
alphanum ({alpha}|{digit})
name	{alpha}{alphanum}*

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
box             return KEY_BOX;
camera		return KEY_CAMERA;
ceil            return KEY_CEIL;
color		return KEY_COLOR;
colour		return KEY_COLOR;
cos             return KEY_COS;
cosh            return KEY_COSH;
cylinder        return KEY_CYLINDER;
degrees         return KEY_DEGREES;
diffuse		return KEY_DIFFUSE;
disc            return KEY_DISC;
distance        return KEY_DISTANCE;
div             return KEY_DIV;
equator		return KEY_EQUATOR;
exp             return KEY_EXP;
false           return KEY_FALSE;
finish		return KEY_FINISH;
floor           return KEY_FLOOR;
fog             return KEY_FOG;
fog_type        return KEY_FOG_TYPE;
gif             return KEY_GIF;
green		return KEY_GREEN;
iff             return KEY_IFF;
int             return KEY_INT;
inside          return KEY_INSIDE;
image_map	return KEY_IMAGE;
image_width     return KEY_IMAGE_WIDTH;
image_height    return KEY_IMAGE_HEIGHT;
jpeg            return KEY_JPEG;
light_source	return KEY_LIGHT;
ln              return KEY_LN;
log             return KEY_LOG;
location	return KEY_LOCATION;
look_at		return KEY_LOOK;
max             return KEY_MAX;
max_extent      return KEY_MAX_EXTENT;
min             return KEY_MIN;
min_extent      return KEY_MIN_EXTENT;
mod             return KEY_MOD;
no              return KEY_NO;
object          return KEY_OBJECT;
off             return KEY_OFF;
on              return KEY_ON;
open            return KEY_OPEN;
pgm             return KEY_PGM;
pi              return KEY_PI;
pigment		return KEY_PIGMENT;
plane		return KEY_PLANE;
png             return KEY_PNG;
pole		return KEY_POLE;
pow             return KEY_POW;
ppm		return KEY_PPM;
radians         return KEY_RADIANS;
red		return KEY_RED;
reflection	return KEY_REFLECTION;
rgb		return KEY_RGB;
rotate          return KEY_ROTATE;
select          return KEY_SELECT;
sin             return KEY_SIN;
sinh            return KEY_SINH;
sky		return KEY_SKY;
smooth_triangle return KEY_SMOOTH_TRIANGLE;
sphere		return KEY_SPHERE;
sys             return KEY_SYS;
tan             return KEY_TAN;
tanh            return KEY_TANH;
tiff            return KEY_TIFF;
tga             return KEY_TGA;
transform       return KEY_TRANSFORM;
translate       return KEY_TRANSLATE;
triangle	return KEY_TRIANGLE;
triangle_point	return KEY_TRIANGLEPNT;
true            return KEY_TRUE;
union           return KEY_UNION;
vaxis_rotate    return KEY_VAXIS_ROTATE;
vcross          return KEY_VCROSS;
vdot            return KEY_VDOT;
vlength         return KEY_VLENGTH;
vnormalize      return KEY_VNORMALIZE;
vrotate         return KEY_VROTATE;
x               return KEY_X;
y               return KEY_Y;
yes             return KEY_YES;
z               return KEY_Z;

"{"		return LBRACE;
"}"		return RBRACE;
"<="            return LT_EQ;
">="            return GT_EQ;
"!="            return NOT_EQ;
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
"="             return EQ;
"?"             return QUESTION;
":"             return COLON;
"&"             return AND;
"|"             return OR;
"!"             return NOT;
";"             return SEMICOLON;

"#declare"      return DIRECTIVE_DECLARE;
"#undef"        return DIRECTIVE_UNDEF;

{number}	{ yylval.value = atof(yytext); return NUMBER; }
\"[^\"]*\"	{ yylval.string = strdup(yytext+1);
		  yylval.string[strlen(yytext+1)-1] = '\0';
	          return STRING;
		}

{name}		{
  yylval.string = strdup(yytext);
  return NAME;
}

\n 		{ linecount++; }
[ \t\r]		;

.		return UNCAUGHT;
%%
