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

#include "sphere.h"
#include <math.h>

namespace Protracer {

  Sphere::Sphere(const Vector& center, float radius, const Vector& pole,
		 const Vector& equator, Pigment* pigment,
		 const Finish& finish) :
    Object(pigment, finish)
  {
    this->center = center;
    this->radius = radius;
    this->radius_sqr = radius * radius;
    this->pole = pole.normal();
    this->equator = equator.normal();
  }

  HitCalculation
  Sphere::calculate_hit(const Ray& ray) const
  {
    scalar  l2oc;
    scalar  tca;
    scalar  t2hc;
    scalar  distance;
    
    Vector cmo = center - ray.get_origin();

    l2oc = cmo.dot(cmo);
    tca = cmo.dot(ray.get_direction());
    
    t2hc = radius_sqr - l2oc + tca * tca;
 
    if (!(l2oc < radius_sqr)) {
	if (tca + EPS >= 0 && t2hc >= 0 ) {
	  distance = tca - sqrt( t2hc );
	  Vector temp = ray.get_origin() + distance * ray.get_direction();
	  temp = 1.0 / radius * (temp - center);

	  return HitCalculation(true, distance, temp, color_at(temp));
	} else {
	  return HitCalculation(false);
	}
    }
    
    distance = tca + sqrt(t2hc);
    
    Vector temp = ray.get_origin() + distance * ray.get_direction();
    temp = -1.0 / radius * (temp - center);
    
    return HitCalculation(true, distance, temp, color_at(temp));
  }

  Color
  Sphere::color_at(const Vector& normal) const
  {
    float phi,temp;
    float theta;
    float u,v; /* Coordinates in % of bitmap. */

    if (pigment->is_uniform())
      return pigment->get_color();

    phi = acos(-(normal.dot(pole)));
    v = 1 - phi / M_PI;

    if ( v == 1.0 || v == 0.0 ) {
      u = 0.0;
    } else {
      temp = normal.dot(equator) / sin(phi);
      temp = temp > 1.0 ? 1.0 : temp;
      temp = temp < -1.0 ? -1.0 : temp; 
      theta = acos(temp) / (2*M_PI);
      u = Vector(equator * pole).dot(normal) > 0 ? theta : 1 - theta;
    }

    /* Ok, u and v are the % coordinates into the bitmap.
       Lets return the correct color for the given point. */    
    return pigment->get_color(u, v);
  }

}
