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

#include <iostream>
#include <vector>

#include "world.h"
#include "util.h"
#include "constants.h"
#include "Ray.h"
#include "Object.h"
#include "ObjectArray.h"

namespace Protracer {
  
  World::World(const std::vector<Object>& objects,
	       const std::vector<Light>& lights, 
	       const Camera& cam, const Color& background )
  {
    Vector c;
       
    this->camera =     cam;
    this->lights =     lights;
    this->objects =    objects;
    this->background = background;

    c = Vector_normalize(Vector_subtract(Camera_lookAt(camera),
					 Camera_location(camera)));
 
    this->c_right = Vector_normalize(Vector_crossProduct( 
        Camera_upVector(camera), c));
    this->c_down = Vector_normalize(Vector_crossProduct(c_right, c));

    
    this->c_corner = Vector_add( 
        Camera_location( cam ), 
        Vector_subtract( 
            Vector_multiply( 
                Camera_zoom( cam ), 
                c ),
            Vector_add( 
                Vector_multiply(Camera_worldWidth(cam) / 2, c_right),
                Vector_multiply(Camera_worldHeight(cam) / 2, c_down))));
  }

  World::~World()
  {
    for (std::vector<Object>::iterator it = objects.begin() ;
	 it != objects.end() ; it++) {
      Object o = *it;

      free(o);
    }
  }

  Color
  World::color_at_hit_point(int x, int y, const Ray& ray, int refl_depth,
			    bool no_shadow_no_reflection) const
  {
    Vector      hitPoint;

    int         j;
    int         index = 0;
    float      leastDistance = HUGE_VAL;

    float      shade = 0.0;
    
    Ray         reflRay;
    Ray         lightRay;

    bool        isLit;

    Color       col;

    HitData     hd;
    HitData     nearestHit;

    Object hit_object;

    for(std::vector<Object>::const_iterator it = objects.begin() ;
	it != objects.end() ; it++) {
      Object o = *it;
      hd = Object_rayHitData(o, ray);

        if (HitData_hit(hd)) {
            if (HitData_distance(hd) < leastDistance) {
                leastDistance = HitData_distance(hd);
                nearestHit = hd;
                hit_object = o;
            }
        }
    }

    //std::cerr << "least dist: " << leastDistance << std::endl;

    if(leastDistance == HUGE_VAL)
        return background;
  

    /* leastDistance is the distance to the nearest object hit */
    hitPoint = Vector_add( Ray_origin( ray ),
                           Vector_multiply(
                               leastDistance,
                               Ray_direction( ray ) ) );
   

    if (no_shadow_no_reflection) {
      // Simulate the camera as a light source 

       return
	 Color_shade(  
		     HitData_color( nearestHit ),
		     Util::shade_factor( Ray_origin( ray ), hitPoint,
				  HitData_normal( nearestHit) ) );

     } else {

      /* iterate over light sources */
      for (std::vector<Light>::const_iterator it = lights.begin() ;
	   it != lights.end() ; it++) {
	const Light& l = *it;
	
	lightRay = Ray_create(Vector_add(hitPoint,
					 Vector_multiply(EPS,
							 HitData_normal(nearestHit))),
			      Vector_subtract(Light_position(l),
					      Vector_add(hitPoint,
							 Vector_multiply(EPS,
									 HitData_normal(nearestHit)))));


	bool is_lit = true;
	for (std::vector<Object>::const_iterator it = objects.begin() ;
	     it != objects.end() && is_lit ; it++) {
	  Object o = *it;
	  
	  hd = Object_rayHitData(o, lightRay);
	  
	  if (HitData_hit(hd)) {
	    if (HitData_distance(hd) < 
		Vector_length(Vector_subtract(Light_position(l), hitPoint)))
		       is_lit = false;
	  }
	}

	//std::cerr << "is lit: " << isLit << std::endl;

	if (is_lit) {
	  shade += 
	    Util::shade_factor(Light_position(l),
			       hitPoint, 
			       HitData_normal(nearestHit));
	}
      }


	 /* Base case: don't take reflection into acount, 
	    but shade the accumulated light from light sources */
	 if (refl_depth == 0) {
	   return
	     Color_shade( HitData_color( nearestHit ),
			  shade *
			  Object_diffuse(hit_object));
	 } else {
	   /* calculate reflected ray */
	   /* move EPS in the normal direction, to avoid rounding errors */
	     reflRay = Ray_create( Vector_add( hitPoint,
					       Vector_multiply( 
						   EPS,
						   HitData_normal(
						       nearestHit ) ) ),
				   Vector_subtract(
				       Ray_direction( ray ),
				       Vector_multiply( 
					   2 *
					   Vector_dotProduct(
					       HitData_normal( nearestHit ),
					       Ray_direction( ray ) ) ,
					   HitData_normal( nearestHit ) ) ) );

	     refl_depth--;
	     col = color_at_hit_point(x, y, reflRay, refl_depth,
				      no_shadow_no_reflection);

	     return
		 Color_combine( 
		     Color_shade(
			 col,
			 Object_reflection(hit_object)),

		     Color_shade( 
			 HitData_color( nearestHit ),
			 shade *
			 Object_diffuse(hit_object)));
	 }

     }    

   }

   Color
   World::color_of_pixel(int x, int y, int refl_depth,
			 bool no_shadow_no_reflection) const
   {
     Ray ray;
     Vector rayDirection;

     rayDirection = 
	 Vector_normalize( 
	     Vector_subtract( 
		 Vector_add( 
		     Vector_add( 
			 Vector_multiply( ( Camera_worldWidth(camera) /  
					    Camera_pixelWidth(camera) ) 
					  * x, 
					  c_right),
			 Vector_multiply( ( Camera_worldHeight(camera) / 
					    Camera_pixelHeight(camera) ) * y, 
					  c_down) ),
		     c_corner), 
		 Camera_location(camera)));




     ray = Ray_create( Camera_location(camera), 
		       rayDirection );

     Color c = color_at_hit_point(x, y, ray, refl_depth, no_shadow_no_reflection);

     /*std::cerr << "col: r = " << int(Color_red(c)) 
	      << ", g = " << int(Color_green(c)) 
	      << ", b = " << int(Color_blue(c)) << std::endl;*/

    return c;
  }
}

