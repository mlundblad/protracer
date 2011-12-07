/* -*-C++-*- */

%require "2.4"

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

#include <vector>
#include <iostream>
#include <cmath>
#include <math.h>
#include "vector.h"
#include "plane.h"
#include "sphere.h"
#include "triangle.h"
#include "camera.h"
#include "color.h"
#include "object.h"
#include "light.h"

#include "finish.h"
#include "pigment.h"
#include "bitmap.h"
#include "ppm_file.h"

#include "parameters.h"
#include "declaration.h"

  Protracer::Parameters global_parameters;
  std::vector<Protracer::Object*> global_object_list;
  std::vector<Protracer::Light> global_light_list;
  Protracer::Color      global_background;
  Protracer::Camera     global_camera;
  Protracer::PPMFile    global_image_file;


extern char *yytext;
extern int linecount;
extern int yylex(void);

int yyerror(char *s);
%}

%code requires {

#include <stdlib.h>
#include <vector>
#include <list>
#include <algorithm>

#include "vector.h"
#include "plane.h"
#include "sphere.h"
#include "triangle.h"
#include "disc.h"
#include "camera.h"
#include "color.h"
#include "object.h"
#include "light.h"

#include "finish.h"
#include "pigment.h"
#include "bitmap_pigment.h"
#include "color_pigment.h"
#include "bitmap.h"
#include "ppm_file.h"

#include "parameters.h"

  int yyparse();
  extern FILE        *yyin;

  // global variables used by the parser
  extern Protracer::Parameters global_parameters;
  extern std::vector<Protracer::Object*> global_object_list;
  extern std::vector<Protracer::Light> global_light_list;
  extern Protracer::Color      global_background;
  extern Protracer::Camera     global_camera;
  extern Protracer::PPMFile    global_image_file;

  // internal structs used for parsing
  struct ObjectMods {
    Protracer::Pigment* pigment;
    Protracer::Finish finish;
  };

  struct SphereOptions {
    ~SphereOptions()
    {
      delete pole;
      delete equator;
    }

    Protracer::Vector* pole;
    Protracer::Vector* equator;
  };
}

%union {
  double	value;		        /* for numbers */
  char		*string;	/* for names */
  std::list<float>* number_list; // for scalar argument lists
  bool          logical;
  Protracer::Vector*	vector;
  Protracer::Sphere*      sphere;
  Protracer::Triangle*    triangle;
  Protracer::Plane*       plane;
  Protracer::Disc*        disc;
  Protracer::Object*      object;
  Protracer::Camera*      camera;
  Protracer::Color*       color;
  SphereOptions*   sphereOptions;
  ObjectMods*  objectMods;
  Protracer::Finish*      finish;
  Protracer::Pigment*     pigment;
  Protracer::Bitmap*      bitmap;
};

%start scene

%token LBRACE RBRACE LANGLE RANGLE LPAREN RPAREN COMMA DOT

%token <value> NUMBER
%token <string> STRING
%token <string> NAME

%token UNCAUGHT

%token KEY_SPHERE KEY_PIGMENT KEY_COLOR
%token KEY_FINISH KEY_TRIANGLE KEY_TRIANGLEPNT
%token KEY_DIFFUSE KEY_REFLECTION
%token KEY_RED KEY_GREEN KEY_BLUE
%token KEY_LOCATION KEY_LOOK KEY_BACKGROUND
%token KEY_CAMERA KEY_RGB KEY_SKY KEY_LIGHT
%token KEY_PLANE KEY_PLANEPNT KEY_IMAGE KEY_PPM
%token KEY_POLE KEY_EQUATOR KEY_DISC
%token KEY_X KEY_Y KEY_Z
%token KEY_ABS KEY_ACOS KEY_ACOSH KEY_ASIN KEY_ASINH KEY_ATAN KEY_ATANH
%token KEY_ATAN2 KEY_CEIL KEY_COS KEY_COSH KEY_DEGREES KEY_DIV KEY_EXP
%token KEY_FLOOR KEY_INT KEY_LOG KEY_LN KEY_MAX KEY_MIN KEY_MOD KEY_POW
%token KEY_RADIANS KEY_SELECT KEY_SIN KEY_SINH KEY_TAN KEY_TANH KEY_VDOT KEY_VLENGTH
%token KEY_FALSE KEY_NO KEY_ON KEY_OFF KEY_PI KEY_TRUE KEY_YES
%token KEY_VCROSS KEY_VNORMALIZE
%left QUESTION COLON
%left AND OR
%left EQ NOT_EQ LANGLE RANGLE LT_EQ GT_EQ
%left PLUS MINUS
%left TIMES DIVIDED
%left POS NEG NOT // negation, unary -, logical not

%token SEMICOLON

%token DIRECTIVE_DECLARE

%type <objectList> scene
%type <object> item
%type <plane> plane
%type <triangle> triangle
%type <sphere> sphere
%type <disc> disc
%type <vector> vector
%type <vector> vector_builtin;
%type <value> number
%type <camera> camera
%type <color> color
%type <sphereOptions> sphere_opt
%type <objectMods> object_mods  /* opt_pigment, opt_finish*/
%type <pigment> opt_pigment
%type <pigment> pigment
%type <finish> opt_finish       /* opt_diffuse, opt_reflection */
%type <finish> finish
%type <bitmap> image
%type <value> reflection
%type <value> diffuse
%type <value> opt_diffuse
%type <value> opt_reflection
%type <light> light
%type <color> background
%type <value> opt_hole
%type <number_list> numbers
%type <logical> logical;
%type <string> declaration;

%%

scene	:	
          item_or_declaration { }
        | scene item_or_declaration { }
	;

item_or_declaration:
item {}
| declaration {}
;

item:	
          sphere     { global_object_list.push_back($1); }
        | triangle   { global_object_list.push_back($1); }
        | plane      { global_object_list.push_back($1); }
        | disc       { global_object_list.push_back($1); }
        | camera     { }
        | background { }
        | light      { } 
	;

light:
	KEY_LIGHT LBRACE
	vector
	RBRACE {
	  global_light_list.push_back(Protracer::Light(*$3));
	  delete $3;
	}
	;


plane:
	KEY_PLANE LBRACE
	vector COMMA number
	object_mods
	RBRACE {
	  $$ = new Protracer::Plane(*$3, Protracer::Vector(0, 0, $5), 
				    $6->pigment, $6->finish);
	  delete $3;
	  delete $6;
	}
        ;

/* This is not POVray syntax, but is an easier way to specify a plane. */
plane:
	KEY_PLANEPNT LBRACE
	vector COMMA vector
	object_mods
	RBRACE {
	  $$ = new Protracer::Plane(*$5, *$3, $6->pigment, $6->finish);
	  delete $3;
	  delete $5;
	  delete $6;
	}
	;

sphere:
	KEY_SPHERE LBRACE vector COMMA number sphere_opt
	object_mods
	RBRACE {
	  $$ = new Protracer::Sphere(*$3, $5, *($6->pole), *($6->equator), 
				     $7->pigment, $7->finish);
	  delete $3;
	  delete $6;
	  delete $7;
	}
	;

sphere_opt:   {
  $$ = new SphereOptions;
  $$->pole = new Protracer::Vector(Protracer::Sphere::POLE_DEFAULT_X, 
				   Protracer::Sphere::POLE_DEFAULT_Y,
				   Protracer::Sphere::POLE_DEFAULT_Z);
  $$->equator = new Protracer::Vector(Protracer::Sphere::EQUATOR_DEFAULT_X,
				      Protracer::Sphere::EQUATOR_DEFAULT_Y,
				      Protracer::Sphere::EQUATOR_DEFAULT_Z); }
  |            
    KEY_POLE vector KEY_EQUATOR vector { 
      $$ = new SphereOptions;
      $$->pole = $2;
      $$->equator = $4;
    }
    ;

triangle:
	KEY_TRIANGLE LBRACE
	vector COMMA
	vector COMMA
	vector
	object_mods
	RBRACE { 
	  $$ = new Protracer::Triangle(*$3, *$5, *$7, $8->pigment, $8->finish);
	  delete $3;
	  delete $5;
	  delete $7;
	  delete $8;
	}
        ;

/* Again, this is not POVray, but provides an alternative way of
   specifying a triangle. */
triangle:
	KEY_TRIANGLEPNT LBRACE
	vector COMMA
	vector COMMA
	vector
	object_mods
	RBRACE {
	  $$ = new Protracer::Triangle(*$3, *$5, *$7, $8->pigment, $8->finish,
				       true);
	  delete $3;
	  delete $5;
	  delete $7;
	  delete $8;
	}
	;
	
disc:
    KEY_DISC LBRACE 
    vector COMMA 
    vector COMMA 
    number
    opt_hole
    object_mods
    RBRACE {
      $$ = new Protracer::Disc(*$3, *$5, $7, $8, $9->pigment, $9->finish);
      delete $3;
      delete $5;
      delete $9;
    };


opt_hole: {
  // empty
  $$ = 0.0f;
}
| COMMA number {
  $$ = $2;
}

object_mods:
	opt_pigment
        opt_finish {
	  $$ = new ObjectMods;
	  $$->pigment = $1;
	  $$->finish = *$2;
	  delete $2;
	}

opt_pigment:	/* empty */
{ $$ = new Protracer::ColorPigment(); }
          
| pigment { $$ = $1; }
;

pigment:
KEY_PIGMENT LBRACE color RBRACE {
  $$ = new Protracer::ColorPigment(*$3);
  delete $3;
}
| KEY_PIGMENT LBRACE image RBRACE { $$ = new Protracer::BitmapPigment($3); }
	;

                
image:	KEY_IMAGE LBRACE KEY_PPM STRING RBRACE {
          global_image_file.open_in($4);
	  $$ = global_image_file.read_bitmap();
	  global_image_file.close();
	}
	;

opt_finish: { $$ = new Protracer::Finish(Protracer::Finish::DEFAULT_DIFFUSION,
					 Protracer::Finish::DEFAULT_REFLECTION); }
        /* empty */
        | finish { $$ = $1; } 
	;

finish:
	KEY_FINISH LBRACE 
	opt_diffuse
	opt_reflection
	RBRACE { $$ = new Protracer::Finish($3, $4); }
	;

opt_diffuse: 	{ $$ = Protracer::Finish::DEFAULT_DIFFUSION; }
          /* empty */
        | diffuse { $$ = $1; }
        ;

diffuse:
        KEY_DIFFUSE number { $$ = $2; }
	;

opt_reflection:	 { $$ = Protracer::Finish::DEFAULT_REFLECTION; }
          /* empty */
        | reflection { $$ = $1; }
	;

reflection:
KEY_REFLECTION number { $$ = $2; }
	;

color:
	KEY_COLOR
	KEY_RED number
	KEY_GREEN number
	KEY_BLUE number {
	  $$ = new Protracer::Color($3 * Protracer::Color::COMPONENT_MAX, 
				    $5 * Protracer::Color::COMPONENT_MAX, 
				    $7 * Protracer::Color::COMPONENT_MAX);
	}
	|
	KEY_COLOR KEY_RGB vector {
	  $$ = new Protracer::Color($3->get_x() *
				    Protracer::Color::COMPONENT_MAX,
				    $3->get_y() *
				    Protracer::Color::COMPONENT_MAX,
				    $3->get_z() *
				    Protracer::Color::COMPONENT_MAX);
          delete $3;
	}
	;

camera:
	KEY_CAMERA LBRACE
	KEY_LOCATION vector
	KEY_SKY vector
	KEY_LOOK vector
	RBRACE { /*printf("Camera\n");*/
	  global_camera =
	    Protracer::Camera(*$4, *$8, *$6,
			      global_parameters.get_zoom(),
			      global_parameters.get_world_width(),
			      global_parameters.get_world_height(),
			      global_parameters.get_pixel_width(),
			      global_parameters.get_pixel_height());
	  delete $4;
	  delete $6;
	  delete $8;
	}
	;

background:
	KEY_BACKGROUND LBRACE
	color
	RBRACE {
	  global_background = *$3;
	  delete $3;
	}
	;


number:
NUMBER { $$ = $1; }
| number PLUS number { $$ = $1 + $3; }
| number MINUS number { $$ = $1 - $3; }
| number TIMES number { $$ = $1 * $3; }
| number DIVIDED number { $$ = $1 / $3; }
| MINUS number %prec NEG { $$ = -$2; }
| PLUS number %prec POS { $$ = $2; }
| LPAREN number RPAREN { $$ = $2; }
| vector DOT KEY_X {
  $$ = $1->get_x();
  delete $1;
}
| vector DOT KEY_Y {
  $$ = $1->get_y();
  delete $1;
}
| vector DOT KEY_Z {
  $$ = $1->get_z();
  delete $1;
}
| color DOT KEY_RED {
  $$ = float($1->get_red()) / Protracer::Color::COMPONENT_MAX;
  delete $1;
}
| color DOT KEY_GREEN {
  $$ = float($1->get_green()) / Protracer::Color::COMPONENT_MAX;
  delete $1;
}
| color DOT KEY_BLUE {
  $$ = float($1->get_blue()) / Protracer::Color::COMPONENT_MAX;
  delete $1;
}
| KEY_ABS LPAREN number RPAREN { $$ = std::fabs($3); }
| KEY_ACOS LPAREN number RPAREN { $$ = std::acos($3); }
| KEY_ACOSH LPAREN number RPAREN { $$ = acoshf($3); }
| KEY_ASIN LPAREN number RPAREN { $$ = std::asin($3); }
| KEY_ASINH LPAREN number RPAREN { $$ = asinhf($3); }
| KEY_ATAN LPAREN number RPAREN { $$ = std::atan($3); }
| KEY_ATANH LPAREN number RPAREN { $$ = atanhf($3); }
| KEY_ATAN2 LPAREN number COMMA number RPAREN { $$ = std::atan2($3, $5); }
| KEY_CEIL LPAREN number RPAREN { $$ = std::ceil($3); } 
| KEY_COS LPAREN number RPAREN { $$ = std::cos($3); }
| KEY_COSH LPAREN number RPAREN { $$ = std::cosh($3); }
| KEY_DEGREES LPAREN number RPAREN { $$ = $3 / M_PI * 180; }
| KEY_DIV LPAREN number COMMA number RPAREN { $$ = trunc($3 / $5); }
| KEY_EXP LPAREN number RPAREN { $$ = std::exp($3); }
| KEY_FLOOR LPAREN number RPAREN { $$ = std::floor($3); }
| KEY_INT LPAREN number RPAREN { $$ = truncf($3); }
| KEY_LOG LPAREN number RPAREN { $$ = std::log10($3); }
| KEY_LN LPAREN number RPAREN { $$ = std::log($3); }
| KEY_MAX LPAREN number COMMA numbers RPAREN {
  $5->push_front($3);
  $$ = *std::max_element($5->begin(), $5->end());
  delete $5;
}
| KEY_MIN LPAREN number COMMA numbers RPAREN {
  $5->push_front($3);
  $$ = *std::min_element($5->begin(), $5->end());
  delete $5;
}
| KEY_MOD LPAREN number COMMA number RPAREN { $$ = std::fmod($3, $5); }
| KEY_POW LPAREN number COMMA number RPAREN { $$ = std::pow($3, $5); }
| KEY_RADIANS LPAREN number RPAREN { $$ = $3 * M_PI / 180.0; }
| KEY_SELECT LPAREN number COMMA number COMMA number RPAREN {
  $$ = $3 < 0 ? $5 : $7; }
| KEY_SELECT LPAREN number COMMA number COMMA number COMMA number RPAREN {
  $$ = $3 < 0 ? $5 : $3 == 0 ? $7 : $9; }
| KEY_SIN LPAREN number RPAREN { $$ = std::sin($3); }
| KEY_SINH LPAREN number RPAREN { $$ = std::sinh($3); }
| KEY_TAN LPAREN number RPAREN { $$ = std::tan($3); }
| KEY_TANH LPAREN number RPAREN { $$ = std::tanh($3); }
| KEY_VDOT LPAREN vector COMMA vector RPAREN {
  $$ = $3->dot(*$5);
  delete $3;
  delete $5;
}
| KEY_VLENGTH LPAREN vector RPAREN {
  $$ = $3->length();
  delete $3;
}
| KEY_FALSE { $$ = 0.0; }
| KEY_NO { $$ = 0.0; }
| KEY_OFF { $$ = 0.0; }
| KEY_ON { $$ = 1.0; }
| KEY_PI { $$ = M_PI; }
| KEY_TRUE { $$ = 1.0; }
| KEY_YES { $$ = 1.0; }
| logical QUESTION number COLON number { $$ = $1 ? $3 : $5; }
// need to allow define the following rules here as well as as for logical
// to allow treating float values as logical values
| number AND number { $$ = ($1 != 0.0) && ($3 != 0.0); }
| number OR number { $$ = ($1 != 0.0) || ($3 != 0.0); }
| NOT number { $$ = $2 == 0.0; }
| NAME {
  if (Protracer::Declaration::is_defined($1)) {
    Protracer::Declaration d = Protracer::Declaration::get_declaration($1);

    if (d.get_type() == Protracer::Declaration::SCALAR) {
      $$ = d.get_scalar();
    } else {
      std::cerr << "Variable " << $1 << " is not a scalar value." << std::endl;
      // TODO: trigger a parser error...
    }
  } else {
    std::cerr << "Variable " << $1 << " is undefined." << std::endl;
    // TODO: trigger a parser error...
  }
}
;

numbers: number {
  $$ = new std::list<float>;
  $$->push_back($1);
}
| number COMMA numbers { $3->push_front($1); $$ = $3;}
;

// the rules for vector expression needs to come after the ones for scalar
// expressions above to avoid misparsing of scalar expressions
vector:
LANGLE number COMMA
number COMMA number RANGLE {
  $$ = new Protracer::Vector($2, $4, $6); }
| MINUS vector %prec NEG {
  $$ = new Protracer::Vector(-(*$2));
  delete $2;
}
| PLUS vector %prec POS {
  $$ = $2;
}
| vector PLUS vector {
  $$ = new Protracer::Vector((*$1) + (*$3));
  delete $1;
  delete $3;
}
| vector MINUS vector {
  $$ = new Protracer::Vector((*$1) - (*$3));
  delete $1;
  delete $3;
}
| number TIMES vector {
  $$ = new Protracer::Vector($1 * (*$3));
  delete $3;
  }
| vector TIMES number {
  $$ = new Protracer::Vector((*$1) * $3);
  delete $1;
  }
| logical QUESTION vector COLON vector {
  if ($1) {
    $$ = $3;
    delete $5;
  } else {
    $$ = $5;
    delete $3;
  }
}
| LPAREN vector RPAREN {
  $$ = $2;
}
| vector_builtin {
  $$ = $1;
}
| number {
  $$ = new Protracer::Vector($1);
}
| KEY_VCROSS LPAREN vector COMMA vector RPAREN {
  $$ = new Protracer::Vector(*$3 * *$5);
  delete $3;
  delete $5;
}
| KEY_VNORMALIZE LPAREN vector RPAREN {
  $$ = new Protracer::Vector($3->normal());
  delete $3;
}
;

vector_builtin:
KEY_X {
  $$ = new Protracer::Vector(Protracer::Vector::unit_x());
}
| KEY_Y {
  $$ = new Protracer::Vector(Protracer::Vector::unit_y());
  }
| KEY_Z {
  $$ = new Protracer::Vector(Protracer::Vector::unit_z());
  };

logical: number EQ number { $$ = $1 == $3; }
| number NOT_EQ number { $$ = $1 != $3; }
| number LANGLE number { $$ = $1 < $3; }
| number RANGLE number { $$ = $1 > $3; }
| number LT_EQ number { $$ = $1 <= $3; }
| number GT_EQ number { $$ = $1 >= $3; }
| logical AND logical { $$ = $1 && $3; }
| logical OR logical { $$ = $1 || $3; }
| NOT logical { $$ = !$2; }
| LPAREN logical RPAREN { $$ = $2; }
| number { $$ = $1 != 0.0; }
;

// variable declarations
declaration:
DIRECTIVE_DECLARE NAME EQ number SEMICOLON {
  std::cerr << "Declaring " << $2 << " = " << $4 << std::endl;
  Protracer::Declaration::add_declaration(Protracer::Declaration($2, $4));
  free($2);
}
;


%%

int
yyerror(char *s)
{
  std::cerr << "** line " << linecount << ":" << s << std::endl;
  return 1;
}

