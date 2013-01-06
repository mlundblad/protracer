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

#include <cmath>

#include "cylinder.h"

namespace Protracer {
  
  Cylinder::Cylinder(const Vector& base_point, const Vector& cap_point,
		     float radius, bool open) :
    base_point(base_point), cap_point(cap_point), radius(radius), open(open),
    base_disc(base_point, cap_point - base_point, radius, 0),
    cap_disc(cap_point, base_point - cap_point, radius, 0)
  {
  }


  HitCalculation
  Cylinder::calculate_hit(const Ray& ray) const
  {
    // ray: P(t) = o + t * v;
    Vector o = ray.get_origin();
    Vector v = ray.get_direction();

    Vector ab = cap_point - base_point;
    Vector ao = o - base_point;
    Vector aoxab = ao * ab;
    Vector vxab = v * ab;
    float ab2 = ab.dot(ab);
    float a = vxab.dot(vxab);
    float b = 2 * vxab.dot(aoxab);
    float c = aoxab.dot(aoxab) - radius * radius * ab2;

    // solve second order equation : a*t^2 + b*t + c = 0
    float t1 = (-b + std::sqrt(b * b - 4 * a * c)) / (2 * a);
    float t2 = (-b - std::sqrt(b * b - 4 * a * c)) / (2 * a);
    float t = t1 < t2 ? t1 : t2;
  }


  void
  Cylinder::translate(const Vector& v)
  {
    base_point += v;
    cap_point += v;
    base_disc.translate(v);
    cap_disc.translate(v);
  }

  void
  Cylinder::rotate(const Vector& v)
  {
    base_point = base_point.rotate(v);
    cap_point = cap_point.rotate(v);
    base_disc.rotate(v);
    cap_disc.rotate(v);
  }

  Vector
  Cylinder::get_max_extent() const
  {
    Vector max_base = base_disc.get_max_extent();
    Vector max_cap = cap_disc.get_max_extent();

    return Vector(max_base.get_x() > max_cap.get_x() ?
		  max_base.get_x() : max_cap.get_x(),
		  max_base.get_y() > max_cap.get_y() ?
		  max_base.get_y() : max_cap.get_y(),
		  max_base.get_z() > max_cap.get_z() ?
		  max_base.get_z() : max_cap.get_z());
  }

  Vector
  Cylinder::get_min_extent() const
  {
    Vector min_base = base_disc.get_min_extent();
    Vector min_cap = cap_disc.get_min_extent();

    return Vector(min_base.get_x() < min_cap.get_x() ?
		  min_base.get_x() : min_cap.get_x(),
		  min_base.get_y() < min_cap.get_y() ?
		  min_base.get_y() : min_cap.get_y(),
		  min_base.get_z() < min_cap.get_z() ?
		  min_base.get_z() : min_cap.get_z());
  }

}
