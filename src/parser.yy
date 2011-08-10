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

#include <stdlib.h>
#include <vector>

#include "Vector.h"
#include "Plane.h"
#include "Sphere.h"
#include "Triangle.h"
#include "camera.h"
#include "Color.h"
#include "Object.h"
#include "light.h"

#include "SphereOptions.h"
#include "ObjectMods.h"
#include "Finish.h"
#include "Pigment.h"
#include "Bitmap.h"
#include "PPMFile.h"

#include "Parameters.h"

Parameters global_parameters;
std::vector<Object> global_object_list;
std::vector<Protracer::Light> global_light_list;
Color      global_background;
Protracer::Camera     global_camera;


extern char *yytext;
extern int linecount;
extern int yylex(void);


PPMFile    global_image_file;


int yyerror(char *s);
%}

%union {
    double	value;		        /* for numbers */
    char		*string;	/* for names */
    Vector	vector;
    Sphere      sphere;
    Triangle    triangle;
    Plane       plane;
    Object      object;
    Protracer::Camera*      camera;
    Color       color;
    SphereOptions   sphereOptions;
    ObjectMods  objectMods;
    Finish      finish;
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
          sphere     { global_object_list.push_back(Object_createSphere($1));
	  	     /* global_objectList = 
                           ObjectList_insert( Object_createSphere( $1 ),
                                              global_objectList);*/ } 
	| triangle   { global_object_list.push_back(Object_createTriangle($1));
	  	       /*global_objectList  = 
                           ObjectList_insert( Object_createTriangle( $1 ),
                                              global_objectList);*/ }
        | plane      { global_object_list.push_back(Object_createPlane($1));
	  	       /*global_objectList = 
                           ObjectList_insert( Object_createPlane( $1 ),
                                              global_objectList);*/ } 
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
	RBRACE { /*printf("Plane with normal=");
		 Vector_print($3);
		 printf(", dist=%.2f\n", $5);*/
                 $$ = Plane_create($3, Vector_createFromCartesian(0, 0, $5), 
				   ObjectMods_pigment( $6 ),
                                   Finish_reflection( ObjectMods_finish( $6 )),
                                   Finish_diffuse( ObjectMods_finish( $6 )) );
	       }
;

/* This is not POVray syntax, but is an easier way to specify a plane. */
plane:
	KEY_PLANEPNT LBRACE
	vector COMMA vector
	object_mods
	RBRACE { /*printf("Plane with normal="); Vector_print($3);
		   printf(" at "); Vector_print($5); printf("\n");*/
                 $$ = Plane_create($5, $3, ObjectMods_pigment( $6 ),
                                   Finish_reflection( ObjectMods_finish($6) ),
                                   Finish_diffuse( ObjectMods_finish($6)) );
	       }
	;

sphere:
	KEY_SPHERE LBRACE vector COMMA number sphere_opt
	object_mods
	RBRACE { /*fprintf(stderr, "Sphere at ");
		   Vector_print($3);
		 printf(", radius %.2f\n", $5);*/
                 $$ = Sphere_create($3, $5, SphereOptions_pole($6), 
                                    SphereOptions_equator($6), 
                                    ObjectMods_pigment( $7 ), 
                                    Finish_reflection(ObjectMods_finish( $7 )),
                                    Finish_diffuse(ObjectMods_finish( $7 )));
	       }
	;

sphere_opt:   { $$ = SphereOptions_create(
                     Vector_createFromCartesian(POLE_DEFAULT_X, 
                                                POLE_DEFAULT_Y,
                                                POLE_DEFAULT_Z), 
                     Vector_createFromCartesian(EQUATOR_DEFAULT_X,
                                                EQUATOR_DEFAULT_Y,
                                                EQUATOR_DEFAULT_Z) ); }
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
	RBRACE { /*printf("Triangle\n"); */
                 $$ = Triangle_createFromPoints(
                     $3, $5, $7,
                     ObjectMods_pigment($8),
                     Finish_reflection( ObjectMods_finish($8) ),
                     Finish_diffuse( ObjectMods_finish($8)) );
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
	RBRACE { /*printf("Triangle(p)\n");*/ 
                 $$ = 
                     Triangle_createFromPointAndVectors(
                         $3, $5, $7, 
                         ObjectMods_pigment($8),
                         Finish_reflection(
                             ObjectMods_finish($8)),
                         Finish_diffuse(
                             ObjectMods_finish($8)));
               }
	;
	
object_mods:
	opt_pigment
        opt_finish { $$ = ObjectMods_create( $1, $2); }

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

                
image:	KEY_IMAGE LBRACE KEY_PPM STRING RBRACE { global_image_file = 
                                                     PPMFile_openIn( $4 );
                                                 $$ = PPMFile_readBitmap( 
                                                     global_image_file );
                                                 PPMFile_close( 
                                                     global_image_file ); }
	;

opt_finish: { $$ = Finish_create( DIFFUSE_DEFAULT, REFLECTION_DEFAULT ); }
        /* empty */
        | finish { $$ = $1; } 
	;

finish:
	KEY_FINISH LBRACE 
	opt_diffuse
	opt_reflection
	RBRACE { $$ = Finish_create( $3, $4 ); }
	;

opt_diffuse: 	{ $$ = DIFFUSE_DEFAULT; }		/* empty */
        | diffuse { $$ = $1; }
        ;

diffuse:
        KEY_DIFFUSE number { $$ = $2; }
	;

opt_reflection:	 { $$ = REFLECTION_DEFAULT; }		/* empty */
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
                 global_camera = Protracer::Camera($4, $8, $6, 
                                    Parameters_zoom( global_parameters ),
                                    Parameters_worldWidth( global_parameters),
                                    Parameters_worldHeight( global_parameters ),
                                    Parameters_pixelWidth( global_parameters ),
                                    Parameters_pixelHeight( global_parameters)); 
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
