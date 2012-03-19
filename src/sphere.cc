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

#include "sphere.h"
#include <math.h>

namespace Protracer {

  const float Sphere::POLE_DEFAULT_X = 0.0f;
  const float Sphere::POLE_DEFAULT_Y = 1.0f;
  const float Sphere::POLE_DEFAULT_Z = 0.0f;
  const float Sphere::EQUATOR_DEFAULT_X = 1.0f;
  const float Sphere::EQUATOR_DEFAULT_Y = 0.0f;
  const float Sphere::EQUATOR_DEFAULT_Z = 0.0f;
  const float Sphere::EPS = 0.001f;

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

  Sphere*
  Sphere::copy() const
  {
    return new Sphere(center, radius, pole, equator, pigment->copy(), finish);
  }

  HitCalculation
  Sphere::calculate_hit(const Ray& ray) const
  {
    Vector cmo = center - ray.get_origin();

    float l2oc = cmo.dot(cmo);
    float tca = cmo.dot(ray.get_direction());
    float t2hc = radius_sqr - l2oc + tca * tca;
 
    if (!(l2oc < radius_sqr)) {
      if (tca + EPS >= 0 && t2hc >= 0 ) {
	float distance = tca - sqrt( t2hc );
	Vector temp = ray.get_origin() + distance * ray.get_direction();
	temp = 1.0 / radius * (temp - center);
	
	return HitCalculation(true, distance, temp, color_at(temp));
      } else {
	return HitCalculation(false);
      }
    }

    float distance = tca + sqrt(t2hc);
    
    Vector temp = ray.get_origin() + distance * ray.get_direction();
    temp = -1.0 / radius * (temp - center);
    
    return HitCalculation(true, distance, temp, color_at(temp));
  }

  Color
  Sphere::color_at(const Vector& normal) const
  {
    if (pigment->is_uniform())
      return pigment->get_color();

    float phi = acos(-(normal.dot(pole)));
    float v = 1 - phi / M_PI;
    float u;

    if ( v == 1.0 || v == 0.0 ) {
      u = 0.0;
    } else {
      float temp = normal.dot(equator) / sin(phi);
      temp = temp > 1.0 ? 1.0 : temp;
      temp = temp < -1.0 ? -1.0 : temp; 
      float theta = acos(temp) / (2*M_PI);
      u = Vector(equator * pole).dot(normal) > 0 ? theta : 1 - theta;
    }

    /* Ok, u and v are the % coordinates into the bitmap.
       Lets return the correct color for the given point. */    
    return pigment->get_color(u, v);
  }

}
