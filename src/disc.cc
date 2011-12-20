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

#include "disc.h"

namespace Protracer {

  Disc::Disc(const Vector& center, const Vector& normal, float radius,
	     float hole_radius, Pigment* pigment, const Finish& finish) :
    PlanarObject(normal, center, pigment, finish),
    center(center), normal(normal), radius(radius), hole_radius(hole_radius)
  {
  }

  Disc*
  Disc::copy() const
  {
    return new Disc(center, normal, radius, hole_radius, pigment->copy(), finish);
  }

  HitCalculation
  Disc::calculate_hit(const Ray& ray) const
  {
    HitCalculation hc = span_plane.calculate_hit(ray);

    if (hc.is_hit()) {
      Vector hit_point = ray.get_origin() + ray.get_direction() * hc.get_distance();
      float distance = Vector(hit_point - center).length();

      if (distance <= radius && distance >= hole_radius)
        return hc;
    }

    return HitCalculation(false);
  }


}
