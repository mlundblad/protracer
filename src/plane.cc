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

#include "plane.h"

namespace Protracer {

  Plane::Plane(const Vector& normal, const Vector& point,
	       Pigment* pigment, const Finish& finish) :
    Object(pigment, finish)
  {
    this->normal = normal.normal();
    this->point = point;
    this->d = point.dot(this->normal);
  }

  HitCalculation
  Plane::calculate_hit(const Ray& ray) const
  {
    float vd = normal.dot(ray.get_direction());
    
    if (vd != 0) {
      float v0 = d - normal.dot(ray.get_origin());
      float t = v0 / vd;

      if(t >= 0) {
	Vector rn = (vd < 0 ? 1.0 : -1.0) * normal;

	return HitCalculation(true, t, rn, pigment->get_color());
      }
    }

    return HitCalculation(false);
  }
}
