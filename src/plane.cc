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

#include <math.h>

namespace Protracer {

  Plane::Plane(const Vector& normal, const Vector& point)
  {
    this->normal = normal.normal();
    this->point = point;
    this->d = point.dot(this->normal);
  }

  Plane*
  Plane::copy() const
  {
    Plane* plane = new Plane(normal, point);

    if (has_custom_pigment())
      plane->set_pigment(get_pigment().copy());
    if (has_custom_finish())
      plane->set_finish(get_finish());

    return plane;
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

	return HitCalculation(true, t, rn, get_pigment().get_color(),
                              get_finish());
      }
    }

    return HitCalculation(false);
  }

  void
  Plane::translate(const Vector& v)
  {
    point += v;
    d = point.dot(normal);
  }

  void
  Plane::rotate(const Vector& rot)
  {
    point = point.rotate(rot);
    normal = normal.rotate(rot);
    d = point.dot(normal);
  }

  Vector
  Plane::get_max_extent() const
  {
    return Vector(HUGE_VAL);
  }

  Vector
  Plane::get_min_extent() const
  {
    return Vector(-HUGE_VAL);
  }

}
