/* -*- mode: C++; indent-tabs-mode: nil; c-basic-offset: 2  -*- */
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
#include <limits>

#include "scene.h"
#include "util.h"
#include "constants.h"
#include "ray.h"
#include "object.h"

namespace Protracer {

  Scene::~Scene()
  {
    for (std::vector<Object*>::iterator it = objects.begin() ;
	 it != objects.end() ; it++) {
      Object* o = *it;

      delete o;
    }
  }

  Color
  Scene::color_at_hit_point(int x, int y, const Ray& ray, int refl_depth,
			    bool no_shadow_no_reflection) const
  {
    float least_distance = std::numeric_limits<float>::infinity();
    float shade = 0.0;

    Color       col;

    HitCalculation     nearest_hit;

    for(std::vector<Object*>::const_iterator it = objects.begin() ;
	it != objects.end() ; it++) {
      Object* o = *it;

      HitCalculation hc = o->calculate_hit(ray);

      if (hc.is_hit()) {
	if (hc.get_distance() < least_distance) {
	  least_distance = hc.get_distance();
	  nearest_hit = hc;
	}
      }
    }

    if (least_distance == std::numeric_limits<float>::infinity())
        return background;

    /* leastDistance is the distance to the nearest object hit */
    Vector hit_point = ray.get_origin() + least_distance * ray.get_direction();

    if (no_shadow_no_reflection) {
      // Simulate the camera as a light source 
      
      return nearest_hit.get_color() * 
	Util::shade_factor(ray.get_origin(),
			   hit_point,
			   nearest_hit.get_normal());
     } else {
      /* iterate over light sources */
      for (std::vector<Light>::const_iterator it = lights.begin() ;
	   it != lights.end() ; it++) {
	const Light& l = *it;
	
	Ray light_ray = Ray(hit_point + EPS * nearest_hit.get_normal(),
			       l.get_position() -
			       (hit_point + EPS * nearest_hit.get_normal()));
	bool is_lit = true;

	for (std::vector<Object*>::const_iterator it = objects.begin() ;
	     it != objects.end() && is_lit ; it++) {
	  Object* o = *it;
	  
	  HitCalculation hc = o->calculate_hit(light_ray);
	  
	  if (hc.is_hit()) {
	    if (hc.get_distance() <
		Vector(l.get_position() - hit_point).length())
	      is_lit = false;
	  }
	}

	if (is_lit) {
	  shade += 
	    Util::shade_factor(l.get_position(),
			       hit_point, 
			       nearest_hit.get_normal());
	}
      }

      
      /* Base case: don't take reflection into acount, 
	 but shade the accumulated light from light sources */
      if (refl_depth == 0) {
	return nearest_hit.get_color() *
	  shade * nearest_hit.get_finish().get_diffusion();
      } else {
	/* calculate reflected ray */
	/* move EPS in the normal direction, to avoid rounding errors */
	Ray refl_ray = Ray(hit_point + EPS * nearest_hit.get_normal(),
			   ray.get_direction() -
			   2 * nearest_hit.get_normal().dot(ray.get_direction())
			   * nearest_hit.get_normal());
	
	refl_depth--;
	col = color_at_hit_point(x, y, refl_ray, refl_depth,
				 no_shadow_no_reflection);
	
	return col * nearest_hit.get_finish().get_reflection() +
	  nearest_hit.get_color() * shade *
	  nearest_hit.get_finish().get_diffusion();
      } 
    }
   }

   Color
   Scene::color_of_pixel(int x, int y, int refl_depth,
			 bool no_shadow_no_reflection) const
   {
     float ww = camera.get_world_width();
     unsigned int pw = camera.get_pixel_width();
     float wh = camera.get_world_height();
     unsigned int ph = camera.get_pixel_height();
     Vector ray_direction =
       Vector(ww / pw * x * c_right + wh / ph * y * c_down +
	c_corner - camera.get_location()).normal();

     Ray ray = Ray(camera.get_location(), ray_direction);

     Color c = color_at_hit_point(x, y, ray, refl_depth,
				  no_shadow_no_reflection);

     return c;
   }

  void
  Scene::add_object(Object* object)
  {
    objects.push_back(object);
  }

  void
  Scene::add_light(const Light& light)
  {
    lights.push_back(light);
  }

  void
  Scene::set_camera(const Camera& cam)
  {
    Vector c;
       
    this->camera =     cam;

    c = Vector(camera.get_look_at() - camera.get_location()).normal();

    this->c_right = Vector(camera.get_up() * c).normal();
    this->c_down = Vector(c_right * c).normal();

    this->c_corner = cam.get_location() + 
      (cam.get_zoom() * c) - (cam.get_world_width() / 2 * c_right +
			      cam.get_world_height() / 2 * c_down);
  }

  void
  Scene::set_background(const Color& background)
  {
    this->background = background;
  }

}

