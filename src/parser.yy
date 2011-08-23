/* -*-C++-*- */

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
#include "Vector.h"
#include "plane.h"
#include "sphere.h"
#include "triangle.h"
#include "camera.h"
#include "Color.h"
#include "object.h"
#include "light.h"

#include "SphereOptions.h"
#include "finish.h"
#include "Pigment.h"
#include "Bitmap.h"
#include "ppm_file.h"

#include "parameters.h"

  Protracer::Parameters global_parameters;
  std::vector<Protracer::Object*> global_object_list;
  std::vector<Protracer::Light> global_light_list;
  Color      global_background;
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

#include "Vector.h"
#include "plane.h"
#include "sphere.h"
#include "triangle.h"
#include "camera.h"
#include "Color.h"
#include "object.h"
#include "light.h"

#include "SphereOptions.h"
#include "finish.h"
#include "Pigment.h"
#include "Bitmap.h"
#include "ppm_file.h"

#include "parameters.h"

  // global variables used by the parser
  extern Protracer::Parameters global_parameters;
  extern std::vector<Protracer::Object*> global_object_list;
  extern std::vector<Protracer::Light> global_light_list;
  extern Color      global_background;
  extern Protracer::Camera     global_camera;
  extern Protracer::PPMFile    global_image_file;

  // internal structs used for parsing
  struct ObjectMods {
    Pigment pigment;
    Protracer::Finish finish;
  };
}

%union {
  double	value;		        /* for numbers */
  char		*string;	/* for names */
  Vector	vector;
  Protracer::Sphere*      sphere;
  Protracer::Triangle*    triangle;
  Protracer::Plane*       plane;
  Protracer::Object*      object;
  Protracer::Camera*      camera;
  Color       color;
  SphereOptions   sphereOptions;
  ObjectMods*  objectMods;
  Protracer::Finish*      finish;
  Pigment     pigment;
  Bitmap      bitmap;
};

%start scene

%token LBRACE RBRACE LANGLE RANGLE COMMA

%token <value> NUMBER
%token <string> STRING

%token NAME UNCAUGHT

%token KEY_SPHERE KEY_PIGMENT KEY_COLOR
%token KEY_FINISH KEY_TRIANGLE KEY_TRIANGLEPNT
%token KEY_DIFFUSE KEY_REFLECTION
%token KEY_RED KEY_GREEN KEY_BLUE
%token KEY_LOCATION KEY_LOOK KEY_BACKGROUND
%token KEY_CAMERA KEY_RGB KEY_SKY KEY_LIGHT
%token KEY_PLANE KEY_PLANEPNT KEY_IMAGE KEY_PPM
%token KEY_POLE KEY_EQUATOR


%type <objectList> scene
%type <object> item
%type <plane> plane
%type <triangle> triangle
%type <sphere> sphere
%type <vector> vector
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

%%

scene	:	
          item { }
        | scene item { }
	;

item:	
          sphere     { global_object_list.push_back($1); }
        | triangle   { global_object_list.push_back($1); }
        | plane      { global_object_list.push_back($1); } 
        | camera     { }
        | background { }
        | light      { } 
	;

light:
	KEY_LIGHT LBRACE
	vector
	RBRACE { /*printf("Light at "); Vector_print($3); printf("\n");*/
	         global_light_list.push_back(Protracer::Light($3));
	       }
	;

vector:
	LANGLE number COMMA
	number COMMA number RANGLE { /*printf("Vector: %f %f %f\n", $2, $4, $6 );*/
                                     $$ = Vector_createFromCartesian($2, $4, $6); }
	;

plane:
	KEY_PLANE LBRACE
	vector COMMA number
	object_mods
	RBRACE {
	  $$ = new Protracer::Plane($3, Vector_createFromCartesian(0, 0, $5), 
				    $6->pigment, $6->finish);
	  delete $6;
	}
        ;

/* This is not POVray syntax, but is an easier way to specify a plane. */
plane:
	KEY_PLANEPNT LBRACE
	vector COMMA vector
	object_mods
	RBRACE {
	  $$ = new Protracer::Plane($5, $3, $6->pigment, $6->finish);
	  delete $6;
	}
	;

sphere:
	KEY_SPHERE LBRACE vector COMMA number sphere_opt
	object_mods
	RBRACE {
	  $$ = new Protracer::Sphere($3, $5, SphereOptions_pole($6), 
				     SphereOptions_equator($6), 
				     $7->pigment, $7->finish);
	  delete $7;
	}
	;

sphere_opt:   {
  $$ = SphereOptions_create(
	Vector_createFromCartesian(
          Protracer::Sphere::POLE_DEFAULT_X, 
	  Protracer::Sphere::POLE_DEFAULT_Y,
	  Protracer::Sphere::POLE_DEFAULT_Z), 
	Vector_createFromCartesian(
	  Protracer::Sphere::EQUATOR_DEFAULT_X,
	  Protracer::Sphere::EQUATOR_DEFAULT_Y,
	  Protracer::Sphere::EQUATOR_DEFAULT_Z) ); }
	|            
           KEY_POLE vector KEY_EQUATOR vector { $$ = 
                                                SphereOptions_create( $2, $4 );}
	;

triangle:
	KEY_TRIANGLE LBRACE
	vector COMMA
	vector COMMA
	vector
	object_mods
	RBRACE { 
	  $$ = new Protracer::Triangle($3, $5, $7, $8->pigment, $8->finish);
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
	  $$ = new Protracer::Triangle($3, $5, $7, $8->pigment, $8->finish,
				       true);
	  delete $8;
	}
	;
	
object_mods:
	opt_pigment
        opt_finish {
	  $$ = new ObjectMods;
	  $$->pigment = $1;
	  $$->finish = *$2;
	  delete $2;
	}

opt_pigment:	/* empty */
                { $$ = 
                  Pigment_createColor( Color_createFromRGB( PIGMENT_DEFAULT_RED,
                                                            PIGMENT_DEFAULT_GREEN, 
                                                            PIGMENT_DEFAULT_BLUE));
                }
          
        | pigment { $$ = $1; }
	;

pigment:
	KEY_PIGMENT LBRACE color RBRACE { $$ = Pigment_createColor( $3 );}
      | KEY_PIGMENT LBRACE image RBRACE { $$ = Pigment_createBitmap( $3 ); }
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
	KEY_BLUE number { $$ = Color_createFromRGB( $3 * COLOR_COMPONENT_MAX, 
                                                    $5 * COLOR_COMPONENT_MAX, 
                                                    $7 * COLOR_COMPONENT_MAX); }
	|
	KEY_COLOR KEY_RGB vector { $$ = Color_createFromRGB( Vector_x( $3 ) * 
                                                             COLOR_COMPONENT_MAX,
                                                             Vector_y( $3 ) * 
                                                             COLOR_COMPONENT_MAX,
                                                             Vector_z( $3 ) * 
                                                             COLOR_COMPONENT_MAX); }
	;

camera:
	KEY_CAMERA LBRACE
	KEY_LOCATION vector
	KEY_SKY vector
	KEY_LOOK vector
	RBRACE { /*printf("Camera\n");*/
	  global_camera =
	    Protracer::Camera($4, $8, $6,
			      global_parameters.get_zoom(),
			      global_parameters.get_world_width(),
			      global_parameters.get_world_height(),
			      global_parameters.get_pixel_width(),
			      global_parameters.get_pixel_height());
	  /*printf("camera created\n");*/ }
	;

background:
	KEY_BACKGROUND LBRACE
	color
	RBRACE { /*printf("Background\n"); */
                 global_background = $3; }
	;

number:
	NUMBER { $$ = $1; }
;

%%

int
yyerror(char *s) {
  fprintf(stderr, "** line %d:%s\n", linecount, s);
  return 1;
}

int 
yywrap() {
	return 1;
}
