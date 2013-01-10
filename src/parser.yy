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
#include <sstream>
#include <cmath>

#include "scene.h"
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

#include "parameters.h"
#include "declaration.h"

#include "object_modification.h"
#include "finish_modification.h"
#include "pigment_modification.h"
#include "transformation.h"
#include "translation.h"
#include "rotation.h"
#include "composed_transformation.h"

  Protracer::Scene*      global_scene;
  Protracer::Parameters global_parameters;
  Protracer::Color      global_background;
  Protracer::Camera     global_camera;

extern char *yytext;
extern int linecount;
extern int yylex(void);

static void error(const std::string& error);
int yyerror(char *s);

%}

%code requires {

#include <stdlib.h>
#include <cstring>
#include <vector>
#include <list>
#include <algorithm>

#include "scene.h"
#include "vector.h"
#include "plane.h"
#include "sphere.h"
#include "triangle.h"
#include "disc.h"
#include "box.h"
#include "cylinder.h"
#include "union.h"
#include "camera.h"
#include "color.h"
#include "object.h"
#include "object_modification.h"
#include "finish_modification.h"
#include "pigment_modification.h"
#include "transformation.h"
#include "translation.h"
#include "rotation.h"
#include "composed_transformation.h"
#include "light.h"
#include "exception.h"

#include "finish.h"
#include "pigment.h"
#include "bitmap_pigment.h"
#include "color_pigment.h"
#include "bitmap.h"

#include "parameters.h"

  int yyparse();
  extern FILE        *yyin;

  // global variables used by the parser
  extern Protracer::Scene*     global_scene;
  extern Protracer::Parameters global_parameters;
  extern Protracer::Color      global_background;
  extern Protracer::Camera     global_camera;

  struct SphereOptions {
    Protracer::Vector pole;
    Protracer::Vector equator;
  };

}

%union {
  double	value;		        /* for numbers */
  double*       value_opt;      /* for optional numeric values */
  char		*string;	/* for names */
  std::list<float>* number_list; // for scalar argument lists
  bool          logical;
  Protracer::Vector	vector;
  Protracer::Sphere*      sphere;
  Protracer::Triangle*    triangle;
  Protracer::Plane*       plane;
  Protracer::Disc*        disc;
  Protracer::Box*         box;
  Protracer::Cylinder*    cylinder;
  Protracer::Union*       Union;
  Protracer::Object*      object;
  Protracer::Camera*      camera;
  Protracer::Light*       light;
  Protracer::Color       color;
  SphereOptions   sphereOptions;
  std::list<Protracer::ObjectModification*>* objectMods;
  Protracer::ObjectModification* objectMod;
  Protracer::Transformation* transformation;
  std::list<Protracer::Transformation*>* transformations;
  std::list<Protracer::Object*>* object_list;
  Protracer::Finish      finish;
  Protracer::Pigment*     pigment;
  Protracer::Bitmap*      bitmap;

  // this is a bit ugly, but needed to allow non-pointer vector members in
  // the union
  YYSTYPE() {}
  YYSTYPE& operator=(const YYSTYPE& rhs) {
    if (&rhs != this)
      std::memcpy(this, &rhs, sizeof(YYSTYPE));
    return *this;
  }
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
%token KEY_PLANE KEY_PLANEPNT KEY_IMAGE
%token KEY_GIF KEY_IFF KEY_JPEG KEY_PGM KEY_PNG KEY_PPM KEY_TIFF KEY_TGA KEY_SYS
%token KEY_OBJECT
%token KEY_POLE KEY_EQUATOR KEY_DISC KEY_BOX KEY_UNION KEY_CYLINDER
%token KEY_OPEN
%token KEY_X KEY_Y KEY_Z
%token KEY_ABS KEY_ACOS KEY_ACOSH KEY_ASIN KEY_ASINH KEY_ATAN KEY_ATANH
%token KEY_ATAN2 KEY_CEIL KEY_COS KEY_COSH KEY_DEGREES KEY_DIV KEY_EXP
%token KEY_FLOOR KEY_INT KEY_LOG KEY_LN KEY_MAX KEY_MIN KEY_MOD KEY_POW
%token KEY_RADIANS KEY_SELECT KEY_SIN KEY_SINH KEY_TAN KEY_TANH KEY_VDOT KEY_VLENGTH
%token KEY_FALSE KEY_NO KEY_ON KEY_OFF KEY_PI KEY_TRUE KEY_YES
%token KEY_VAXIS_ROTATE KEY_VCROSS KEY_VNORMALIZE KEY_VROTATE
%token KEY_MAX_EXTENT KEY_MIN_EXTENT
%token KEY_TRANSLATE KEY_ROTATE KEY_TRANSFORM KEY_INSIDE
%token KEY_IMAGE_WIDTH KEY_IMAGE_HEIGHT
%left QUESTION COLON
%left AND OR
%left EQ NOT_EQ LANGLE RANGLE LT_EQ GT_EQ
%left PLUS MINUS
%left TIMES DIVIDED
%left POS NEG NOT // negation, unary -, logical not

%token SEMICOLON

%token DIRECTIVE_DECLARE
%token DIRECTIVE_UNDEF

%type <objectList> scene
%type <object> item
%type <object> object
%type <plane> plane
%type <triangle> triangle
%type <sphere> sphere
%type <disc> disc
%type <box> box
%type <cylinder> cylinder
%type <Union> union
%type <vector> vector
%type <vector> vector_builtin;
%type <value> number
%type <value> number_constant
%type <value> number_function
%type <value> number_dot
%type <value> number_promotable_to_vector
%type <camera> camera
%type <color> color
%type <sphereOptions> sphere_opt
%type <objectMods> object_mods
%type <objectMod> object_mod
%type <transformation> transformation
%type <transformation> transformation_block
%type <transformations> transformations
%type <transformations> transformations_opt
%type <object_list> object_list
%type <pigment> pigment
%type <finish> finish
%type <bitmap> image
%type <value> reflection
%type <value> diffuse
%type <value_opt> opt_diffuse
%type <value_opt> opt_reflection
%type <light> light
%type <color> background
%type <value> opt_hole
%type <logical> opt_open
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
| undefine {}
;

item: object { global_scene->add_object($1); }
| camera     { }
| background { }
| light      {
  global_scene->add_light(*$1);
  delete $1;
} 
;

light: KEY_LIGHT LBRACE vector transformations_opt RBRACE {
  $$ = new Protracer::Light($3);

  for (auto transformation : *$4) {
    transformation->apply($$);
    delete transformation;
  }

  delete $4;
}
| KEY_LIGHT LBRACE NAME transformations_opt RBRACE {
  if (Protracer::Declaration::is_defined($3)) {
    Protracer::Declaration d = Protracer::Declaration::get_declaration($3);
    
    if (d.get_type() == Protracer::Declaration::LIGHT) {
      $$ = new Protracer::Light(d.get_light());
      
      for (auto transformation : *$4) {
	transformation->apply($$);
	delete transformation;
      }

      delete $4;
    } else {
      for (auto transformation : *$4) {
	delete transformation;
      }

      delete $4;
      error(std::string("Variable ") + $3 + " is not a camera.");
    }
  } else {
    for (auto transformation : *$4) {
      delete transformation;
    }

    delete $4;
    error(std::string("Variable ") + $3 + " is undefined.");
  }

  free($3);
}
;

object: sphere { $$ = $1; }
| triangle { $$ = $1; }
| plane { $$ = $1; }
| disc { $$ = $1; }
| box { $$ = $1; }
| cylinder { $$ = $1; }
| union { $$ = $1; }
| KEY_OBJECT LBRACE NAME object_mods RBRACE {
  if (Protracer::Declaration::is_defined($3)) {
    Protracer::Declaration d = Protracer::Declaration::get_declaration($3);

    if (d.get_type() == Protracer::Declaration::OBJECT) {
      $$ = d.get_object()->copy();
      
      for (auto object_mod : *$4) {
	object_mod->apply($$);
	delete object_mod;
      }

      delete $4;
    } else {
      for (auto object_mod : *$4) {
	delete object_mod;
      }

      delete $4;
      error(std::string("Variable ") + $3 + std::string(" is not an object."));
    }
  } else {
    for (auto object_mod : *$4) {
      delete object_mod;
    }

    delete $4;
    error(std::string("Variable ") + $3 + std::string(" is not defined."));
  }

  free($3);
}
;

plane:
	KEY_PLANE LBRACE
	vector COMMA number
	object_mods
	RBRACE {
	  $$ = new Protracer::Plane($3, Protracer::Vector(0, 0, $5));

	  for (auto object_mod : *$6) {
	    object_mod->apply($$);
	    delete object_mod;
	  }

	  delete $6;
	}
        ;

sphere:
	KEY_SPHERE LBRACE vector COMMA number sphere_opt
	object_mods
	RBRACE {
	  $$ = new Protracer::Sphere($3, $5, $6.pole, $6.equator);

	  for (auto object_mod : *$7) {
	    object_mod->apply($$);
	    delete object_mod;
	  }

	  delete $7;
	}
	;

sphere_opt:   {
  $$.pole = Protracer::Vector(Protracer::Sphere::POLE_DEFAULT_X, 
			      Protracer::Sphere::POLE_DEFAULT_Y,
			      Protracer::Sphere::POLE_DEFAULT_Z);
  $$.equator = Protracer::Vector(Protracer::Sphere::EQUATOR_DEFAULT_X,
				 Protracer::Sphere::EQUATOR_DEFAULT_Y,
				 Protracer::Sphere::EQUATOR_DEFAULT_Z); }
  |
    KEY_POLE vector KEY_EQUATOR vector { 
      $$.pole = $2;
      $$.equator = $4;
    }
    ;

triangle:
	KEY_TRIANGLE LBRACE
	vector COMMA
	vector COMMA
	vector
	object_mods
	RBRACE { 
	  $$ = new Protracer::Triangle($3, $5, $7);

	  for (auto object_mod : *$8) {
	    object_mod->apply($$);
	    delete object_mod;
	  }

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
      $$ = new Protracer::Disc($3, $5, $7, $8);

      for (auto object_mod : *$9) {
	object_mod->apply($$);
	delete object_mod;
      }

      delete $9;
    };

box:
   KEY_BOX LBRACE
   vector COMMA
   vector
   object_mods
   RBRACE {
     $$ = new Protracer::Box($3, $5);

     for (auto object_mod : *$6) {
       object_mod->apply($$);
       delete object_mod;
     }

     delete $6;
   };

cylinder:
  KEY_CYLINDER LBRACE
  vector COMMA
  vector COMMA
  number
  opt_open
  object_mods
  RBRACE {
    $$ = new Protracer::Cylinder($3, $5, $7, $8);

    for (auto object_mod : *$9) {
      object_mod->apply($$);
      delete object_mod;
    }

    delete $9;
  };

opt_open:
// empty
{
  $$ = false;
} |
KEY_OPEN {
  $$ = true;
};

union:
  KEY_UNION LBRACE
  object_list
  object_mods
  RBRACE {
    $$ = new Protracer::Union;
  
  for (auto object : *$3) {
    $$->add_object(object);
  }

  for (auto object_mod : *$4) {
    object_mod->apply($$);
    delete object_mod;
  }
  
  delete $3;
};

opt_hole: {
  // empty
  $$ = 0.0f;
}
| COMMA number {
  $$ = $2;
}

object_mods: // empty
{
  $$ = new std::list<Protracer::ObjectModification*>;
}
| object_mods object_mod {
  $1->push_back($2);
  $$ = $1;
};

object_mod: finish {
  $$ = new Protracer::FinishModification($1);
}
| pigment {
  $$ = new Protracer::PigmentModification($1);
}
| transformation {
  $$ = $1;
}
;

transformation: KEY_TRANSLATE vector {
  $$ = new Protracer::Translation($2);
}
| KEY_ROTATE vector {
  $$ = new Protracer::Rotation((M_PI / 180) * $2);
}
| KEY_TRANSFORM LBRACE transformations RBRACE {
  $$ = new Protracer::ComposedTransformation(*$3);
  delete $3;
}
;

transformation_block: NAME {
  if (Protracer::Declaration::is_defined($1)) {
    Protracer::Declaration d = Protracer::Declaration::get_declaration($1);
    
    if (d.get_type() == Protracer::Declaration::TRANSFORMATION) {
      $$ = d.get_transformation()->copy();
    } else {
      error(std::string("Variable ") + $1 + std::string(" is not a transform."));
      free($1);
    }
  } else {
    error(std::string("Variable ") + $1 + std::string(" is not defined."));
    free($1);
  }
}
| transformation {
  $$ = $1;
};


transformations: transformation_block {
  $$ = new std::list<Protracer::Transformation*>;
  $$->push_back($1);
}
| transformations transformation_block {
  $1->push_back($2);
  $$ = $1;
};

// used for instansiating light sources and cameras, need to be able to set
// an empty list of transformations, unlike for the "transformation" block
transformations_opt: /* empty */ {
  $$ = new std::list<Protracer::Transformation*>;
}
| transformations {
  $$ = $1;
};

pigment:
KEY_PIGMENT LBRACE color RBRACE {
  $$ = new Protracer::ColorPigment($3);
}
| KEY_PIGMENT LBRACE image RBRACE {
  $$ = new Protracer::BitmapPigment($3);
}
| KEY_PIGMENT LBRACE NAME RBRACE {
  if (Protracer::Declaration::is_defined($3)) {
    Protracer::Declaration d = Protracer::Declaration::get_declaration($3);

    if (d.get_type() == Protracer::Declaration::PIGMENT) {
      $$ = d.get_pigment()->copy();
    } else {
      error(std::string("Variable ") + $3 + " is not a pigment value.");
    }
  } else {
    error(std::string("Variable ") + $3 + " is not defined.");
  }

  free($3);
}
;

object_list:
// empty
{
  $$ = new std::list<Protracer::Object*>;
}
| object_list object {
  $1->push_back($2);
  $$ = $1;
};

                
image:	KEY_IMAGE LBRACE bitmap_type STRING RBRACE {
  $$ = new Protracer::Bitmap($4);
};

// bitmap type is currently ignored
bitmap_type:
// empty
| KEY_PPM | KEY_PGM | KEY_PNG | KEY_JPEG | KEY_GIF | KEY_TGA
| KEY_IFF | KEY_SYS;

finish: KEY_FINISH LBRACE opt_diffuse opt_reflection RBRACE {
  $$ = Protracer::Finish($3 ? *$3 : Protracer::Finish::DEFAULT_DIFFUSION,
			 $4 ? *$4 : Protracer::Finish::DEFAULT_REFLECTION);
  delete $3;
  delete $4;
}
| KEY_FINISH LBRACE NAME opt_diffuse opt_reflection RBRACE {
  if (Protracer::Declaration::is_defined($3)) {
    Protracer::Declaration d = Protracer::Declaration::get_declaration($3);

    if (d.get_type() == Protracer::Declaration::FINISH) {
      $$ = d.get_finish();
      
      if ($4 != nullptr)
	$$.set_diffusion(*$4);
      if ($5 != nullptr)
	$$.set_reflection(*$5);
    } else {
      error(std::string("Variable ") + $3 + " is not a finish.");
    }
  } else {
    error(std::string("Variable ") + $3 + " is not defined.");
  }
  free($3);
  delete $4;
  delete $5;
}
;

opt_diffuse:
/* empty */ { $$ = 0; }
| diffuse { $$ = new double($1); }
;

diffuse:
        KEY_DIFFUSE number { $$ = $2; }
	;

opt_reflection:
/* empty */ { $$ = 0; }
| reflection { $$ = new double($1); }
;

reflection:
KEY_REFLECTION number { $$ = $2; }
	;

color:
KEY_COLOR
KEY_RED number
KEY_GREEN number
KEY_BLUE number {
  $$ = Protracer::Color((unsigned char)($3 * Protracer::Color::COMPONENT_MAX), 
			(unsigned char)($5 * Protracer::Color::COMPONENT_MAX), 
			(unsigned char)($7 * Protracer::Color::COMPONENT_MAX));
}
|
KEY_COLOR KEY_RGB vector {
  $$ = Protracer::Color((unsigned char)($3.get_x() *
					Protracer::Color::COMPONENT_MAX),
			(unsigned char)($3.get_y() *
					Protracer::Color::COMPONENT_MAX),
			(unsigned char)($3.get_z() *
					Protracer::Color::COMPONENT_MAX));
}
| NAME {
  if (Protracer::Declaration::is_defined($1)) {
    Protracer::Declaration d = Protracer::Declaration::get_declaration($1);
    
    if (d.get_type() == Protracer::Declaration::COLOR) {
      $$ = d.get_color();
    } else {
      error(std::string("Variable ") + $1 + " is not a color value.");
    }
  } else {
    error(std::string("Variable ") + $1 + " is undefined.");
  }
  free($1);
}
;

camera: KEY_CAMERA LBRACE KEY_LOCATION vector
KEY_SKY vector
KEY_LOOK vector
transformations_opt
RBRACE {
  global_camera =
    Protracer::Camera($4, $8, $6,
		      global_parameters.get_zoom(),
		      global_parameters.get_world_width(),
		      global_parameters.get_world_height(),
		      global_parameters.get_pixel_width(),
		      global_parameters.get_pixel_height());

  for (auto transformation : *$9) {
    transformation->apply(&global_camera);
    delete transformation;
  }

  global_scene->set_camera(global_camera);
  delete $9;
}
| KEY_CAMERA LBRACE NAME transformations_opt RBRACE {
  if (Protracer::Declaration::is_defined($3)) {
    Protracer::Declaration d = Protracer::Declaration::get_declaration($3);
    
    if (d.get_type() == Protracer::Declaration::CAMERA) {
      global_camera = d.get_camera();

      for (auto transformation : *$4) {
	transformation->apply(&global_camera);
	delete transformation;
      }

      global_scene->set_camera(global_camera);
      delete $4;
    } else {
      for (auto transformation : *$4) {
	delete transformation;
      }

      delete $4;
      error(std::string("Variable ") + $3 + " is not a camera.");
    }
  } else {
    for (auto transformation : *$4) {
      delete transformation;
    }

    delete $4;
    error(std::string("Variable ") + $3 + " is undefined.");
  }

  free($3);
}
;

background:
	KEY_BACKGROUND LBRACE
	color
	RBRACE {
	  global_background = $3;
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
| number_dot { $$ = $1; }
| number_function { $$ = $1; }
| number_constant { $$ = $1; }
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
      error(std::string("Variable ") + $1 +" is not a scalar value.");
    }
  } else {
    error(std::string("Variable ") + $1 + " is undefined.");
  }
  free($1);
}
;

number_promotable_to_vector:
NUMBER { $$ = $1; }
| number_dot { $$ = $1; }
| number_function { $$ = $1; }
| number_constant { $$ = $1; }
;


number_dot:
vector DOT KEY_X {
  $$ = $1.get_x();
}
| vector DOT KEY_Y {
  $$ = $1.get_y();
}
| vector DOT KEY_Z {
  $$ = $1.get_z();
}
| color DOT KEY_RED {
  $$ = float($1.get_red()) / Protracer::Color::COMPONENT_MAX;
}
| color DOT KEY_GREEN {
  $$ = float($1.get_green()) / Protracer::Color::COMPONENT_MAX;
}
| color DOT KEY_BLUE {
  $$ = float($1.get_blue()) / Protracer::Color::COMPONENT_MAX;
}
;

number_function:
KEY_ABS LPAREN number RPAREN { $$ = std::fabs($3); }
| KEY_ACOS LPAREN number RPAREN { $$ = std::acos($3); }
| KEY_ACOSH LPAREN number RPAREN { $$ = std::acosh($3); }
| KEY_ASIN LPAREN number RPAREN { $$ = std::asin($3); }
| KEY_ASINH LPAREN number RPAREN { $$ = std::asinhf($3); }
| KEY_ATAN LPAREN number RPAREN { $$ = std::atan($3); }
| KEY_ATANH LPAREN number RPAREN { $$ = std::atanh($3); }
| KEY_ATAN2 LPAREN number COMMA number RPAREN { $$ = std::atan2($3, $5); }
| KEY_CEIL LPAREN number RPAREN { $$ = std::ceil($3); } 
| KEY_COS LPAREN number RPAREN { $$ = std::cos($3); }
| KEY_COSH LPAREN number RPAREN { $$ = std::cosh($3); }
| KEY_DEGREES LPAREN number RPAREN { $$ = $3 / M_PI * 180; }
| KEY_DIV LPAREN number COMMA number RPAREN { $$ = std::trunc($3 / $5); }
| KEY_EXP LPAREN number RPAREN { $$ = std::exp($3); }
| KEY_FLOOR LPAREN number RPAREN { $$ = std::floor($3); }
| KEY_INT LPAREN number RPAREN { $$ = std::trunc($3); }
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
  $$ = $3.dot($5);
}
| KEY_VLENGTH LPAREN vector RPAREN {
  $$ = $3.length();
}
| KEY_INSIDE LPAREN NAME COMMA vector RPAREN {
  if (Protracer::Declaration::is_defined($3)) {
    Protracer::Declaration d = Protracer::Declaration::get_declaration($3);

    if (d.get_type() == Protracer::Declaration::OBJECT) {
      $$ = d.get_object()->is_inside($5);
    } else {
      error(std::string("Variable ") + $3 + " is not an object value.");
    }
  } else {
    error(std::string("Variable ") + $3 + " is undefined.");
  }
  free($3);
}
;

number_constant:
KEY_FALSE { $$ = 0.0; }
| KEY_NO { $$ = 0.0; }
| KEY_OFF { $$ = 0.0; }
| KEY_ON { $$ = 1.0; }
| KEY_PI { $$ = M_PI; }
| KEY_TRUE { $$ = 1.0; }
| KEY_YES { $$ = 1.0; }
| KEY_IMAGE_WIDTH { $$ = global_parameters.get_pixel_width(); }
| KEY_IMAGE_HEIGHT { $$ = global_parameters.get_pixel_height(); }
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
  $$ = Protracer::Vector($2, $4, $6);
}
| LANGLE number COMMA number RANGLE {
  $$ = Protracer::Vector($2, $4, 0);
}
| MINUS vector %prec NEG {
  $$ = -$2;
}
| PLUS vector %prec POS {
  $$ = $2;
}
| vector PLUS vector {
  $$ = $1 + $3;
}
| vector MINUS vector {
  $$ = $1 - $3;
}
| vector TIMES vector {
  $$ = $1.multiply_elements($3);
}
| vector DIVIDED vector {
  $$ = $1.divide_elements($3);
}
| vector EQ vector {
  $$ = Protracer::Vector($1.get_x() == $3.get_x(),
			 $1.get_y() == $3.get_y(),
			 $1.get_z() == $3.get_z());
}
| vector NOT_EQ vector {
  $$ = Protracer::Vector($1.get_x() != $3.get_x(),
			 $1.get_y() != $3.get_y(),
			 $1.get_z() != $3.get_z());
}
| vector LANGLE vector {
  $$ = Protracer::Vector($1.get_x() < $3.get_x(),
			 $1.get_y() < $3.get_y(),
			 $1.get_z() < $3.get_z());
}
| vector RANGLE vector {
  $$ = Protracer::Vector($1.get_x() > $3.get_x(),
			 $1.get_y() > $3.get_y(),
			 $1.get_z() > $3.get_z());
}
| vector LT_EQ vector {
  $$ = Protracer::Vector($1.get_x() <= $3.get_x(),
			 $1.get_y() <= $3.get_y(),
			 $1.get_z() <= $3.get_z());
}
| vector GT_EQ vector {
  $$ = Protracer::Vector($1.get_x() >= $3.get_x(),
			 $1.get_y() >= $3.get_y(),
			 $1.get_z() >= $3.get_z());
}
| vector AND vector {
  $$ = Protracer::Vector($1.get_x() && $3.get_x(),
			     $1.get_y() && $3.get_y(),
			     $1.get_z() && $3.get_z());
}
| vector OR vector {
  $$ = Protracer::Vector($1.get_x() || $3.get_x(),
			 $1.get_y() || $3.get_y(),
			 $1.get_z() || $3.get_z());
}
| NOT vector {
  $$ = Protracer::Vector(!$2.get_x(), !$2.get_y(), !$2.get_z());
}
| vector QUESTION vector COLON vector {
  if ($1.get_x() == 0.0 && $1.get_y() == 0.0 && $1.get_z() == 0.0) {
    $$ = $5;
  } else {
    $$ = $3;
  }
}
| LPAREN vector RPAREN {
  $$ = $2;
}
| vector_builtin {
  $$ = $1;
}
| NAME {
  if (Protracer::Declaration::is_defined($1)) {
    Protracer::Declaration d = Protracer::Declaration::get_declaration($1);

    if (d.get_type() == Protracer::Declaration::VECTOR) {
      $$ = d.get_vector();
    } else if (d.get_type() == Protracer::Declaration::SCALAR) {
      $$ = Protracer::Vector(d.get_scalar());
    } else {
      error(std::string("Variable ") + $1 + " is not a vector value.");
    }
  } else {
    error(std::string("Variable ") + $1 + " is undefined.");
  }
  free($1);
} 
| number_promotable_to_vector {
  $$ = Protracer::Vector($1);
}
| KEY_VCROSS LPAREN vector COMMA vector RPAREN {
  $$ = $3 * $5;
}
| KEY_VNORMALIZE LPAREN vector RPAREN {
  $$ = $3.normal();
}
| KEY_VAXIS_ROTATE LPAREN vector COMMA vector COMMA number RPAREN {
  $$ = $3.rotate($5, $7 * M_PI / 180);
}
| KEY_VROTATE LPAREN vector COMMA vector RPAREN {
  $$ = $3.rotate(M_PI / 180 * $5);
}
| KEY_MAX_EXTENT LPAREN NAME RPAREN {
  if (Protracer::Declaration::is_defined($3)) {
    Protracer::Declaration d = Protracer::Declaration::get_declaration($3);

    if (d.get_type() == Protracer::Declaration::OBJECT) {
      $$ = d.get_object()->get_max_extent();
    } else {
      error(std::string("Variable ") + $3 + " is not an object value.");
    }
  } else {
    error(std::string("Variable ") + $3 + " is undefined.");
  }
  free($3);
}
| KEY_MIN_EXTENT LPAREN NAME RPAREN {
  if (Protracer::Declaration::is_defined($3)) {
    Protracer::Declaration d = Protracer::Declaration::get_declaration($3);

    if (d.get_type() == Protracer::Declaration::OBJECT) {
      $$ = d.get_object()->get_min_extent();
    } else {
      error(std::string("Variable ") + $3 + " is not an object value.");
    }
  } else {
    error(std::string("Variable ") + $3 + " is undefined.");
  }
  free($3);
}
;

vector_builtin:
KEY_X {
  $$ = Protracer::Vector::unit_x();
}
| KEY_Y {
  $$ = Protracer::Vector::unit_y();
  }
| KEY_Z {
  $$ = Protracer::Vector::unit_z();
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
  Protracer::Declaration::add_global_declaration(Protracer::Declaration($2, $4));
  free($2);
}
| DIRECTIVE_DECLARE NAME EQ vector SEMICOLON {
  Protracer::Declaration::add_global_declaration(Protracer::Declaration($2, $4));
  free($2);
}
| DIRECTIVE_DECLARE NAME EQ color SEMICOLON {
  Protracer::Declaration::add_global_declaration(Protracer::Declaration($2, $4));
  free($2);
}
| DIRECTIVE_DECLARE NAME EQ finish opt_semicolon {
  Protracer::Declaration::add_global_declaration(Protracer::Declaration($2, $4));
  free($2);
}
| DIRECTIVE_DECLARE NAME EQ pigment opt_semicolon {
  Protracer::Declaration::add_global_declaration(Protracer::Declaration($2, $4));
  free($2);
}
| DIRECTIVE_DECLARE NAME EQ camera opt_semicolon {
  Protracer::Declaration::add_global_declaration(
			  Protracer::Declaration($2,
						 global_camera));
  free($2);
}
| DIRECTIVE_DECLARE NAME EQ light opt_semicolon {
  Protracer::Declaration::add_global_declaration(
			  Protracer::Declaration($2, *$4));
  free($2);
  delete $4;
}
| DIRECTIVE_DECLARE NAME EQ object opt_semicolon {
  Protracer::Declaration::add_global_declaration(Protracer::Declaration($2, $4));
  free($2);
}
| DIRECTIVE_DECLARE NAME EQ KEY_TRANSFORM LBRACE transformations RBRACE 
  opt_semicolon {
  Protracer::Declaration::add_global_declaration(Protracer::Declaration($2,
				  new Protracer::ComposedTransformation(*$6)));
  free($2);
  delete $6;
}
;

opt_semicolon:
// empty
| SEMICOLON;

undefine:
DIRECTIVE_UNDEF NAME {
  if (Protracer::Declaration::is_defined($2)) {
    Protracer::Declaration::remove_global_declaration($2);
  } else {
    error("variable " + std::string($2) + " is not defined.");
  }
}
;

%%

static void error(const std::string& error)
{
  yyerror((char*)error.c_str());
}

int
yyerror(char *s)
{
  std::stringstream ss;

  ss << linecount;
  throw new Protracer::Exception("Syntax error at line " + ss.str() + ": " +
			     std::string(s));
  return 1;
}

