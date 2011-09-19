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
#include "object.h"

namespace Protracer {
  
  World::World(const std::vector<Object*>& objects,
	       const std::vector<Light>& lights, 
	       const Camera& cam, const Color& background )
  {
    Vector c;
       
    this->camera =     cam;
    this->lights =     lights;
    this->objects =    objects;
    this->background = background;

    c = Vector_normalize(Vector_subtract(camera.get_look_at(),
					 camera.get_location()));
 
    this->c_right = Vector_normalize(Vector_crossProduct(camera.get_up(), c));
    this->c_down = Vector_normalize(Vector_crossProduct(c_right, c));

    
    this->c_corner = Vector_add(cam.get_location(), 
				Vector_subtract(Vector_multiply(cam.get_zoom(), 
								c),
						Vector_add( 
							   Vector_multiply(cam.get_world_width() / 2, c_right),
							   Vector_multiply(cam.get_world_height() / 2, c_down))));
  }

  World::~World()
  {
    for (std::vector<Object*>::iterator it = objects.begin() ;
	 it != objects.end() ; it++) {
      Object* o = *it;

      delete o;
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

    Object* hit_object;

    for(std::vector<Object*>::const_iterator it = objects.begin() ;
	it != objects.end() ; it++) {
      Object* o = *it;

      hd = o->calculate_hit(ray);

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
    hitPoint = Vector_add(ray.get_origin(),
			  Vector_multiply(leastDistance,
					  ray.get_direction()));
    

    if (no_shadow_no_reflection) {
      // Simulate the camera as a light source 

       return
	 Color_shade(  
		     HitData_color(nearestHit),
		     Util::shade_factor(ray.get_origin(), hitPoint,
					HitData_normal(nearestHit)));

     } else {

      /* iterate over light sources */
      for (std::vector<Light>::const_iterator it = lights.begin() ;
	   it != lights.end() ; it++) {
	const Light& l = *it;
	
	lightRay = Ray(Vector_add(hitPoint,
				  Vector_multiply(EPS,
						  HitData_normal(nearestHit))),
		       Vector_subtract(l.get_position(),
				       Vector_add(hitPoint,
						  Vector_multiply(EPS,
								  HitData_normal(nearestHit)))));


	bool is_lit = true;
	for (std::vector<Object*>::const_iterator it = objects.begin() ;
	     it != objects.end() && is_lit ; it++) {
	  Object* o = *it;
	  
	  hd = o->calculate_hit(lightRay);
	  
	  if (HitData_hit(hd)) {
	    if (HitData_distance(hd) < 
		Vector_length(Vector_subtract(l.get_position(), hitPoint)))
		       is_lit = false;
	  }
	}

	//std::cerr << "is lit: " << isLit << std::endl;

	if (is_lit) {
	  shade += 
	    Util::shade_factor(l.get_position(),
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
			  hit_object->get_finish().get_diffusion());
	 } else {
	   /* calculate reflected ray */
	   /* move EPS in the normal direction, to avoid rounding errors */
	   reflRay = Ray(Vector_add(hitPoint,
				    Vector_multiply(EPS,
						    HitData_normal(nearestHit))),
			 Vector_subtract(ray.get_direction(),
					 Vector_multiply(2 *
							 Vector_dotProduct(
					       HitData_normal( nearestHit ),
					       ray.get_direction()) ,
							 HitData_normal( nearestHit ) ) ) );

	   refl_depth--;
	   col = color_at_hit_point(x, y, reflRay, refl_depth,
				    no_shadow_no_reflection);

	     return
		 Color_combine( 
		     Color_shade(
			 col,
			 hit_object->get_finish().get_reflection()),
		     Color_shade( 
			 HitData_color( nearestHit ),
			 shade *
			 hit_object->get_finish().get_diffusion()));
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
				Vector_multiply( ( camera.get_world_width() /  
						   camera.get_pixel_width() ) 
					  * x, 
					  c_right),
				Vector_multiply( ( camera.get_world_height() / 
						   camera.get_pixel_height() ) * y, 
					  c_down) ),
		     c_corner), 
		 camera.get_location()));




     ray = Ray(camera.get_location(), rayDirection);

     Color c = color_at_hit_point(x, y, ray, refl_depth, no_shadow_no_reflection);

     /*std::cerr << "col: r = " << int(Color_red(c)) 
	      << ", g = " << int(Color_green(c)) 
	      << ", b = " << int(Color_blue(c)) << std::endl;*/

    return c;
  }
}

