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
	     float hole_radius) :
    PlanarObject(normal, center),
    center(center), normal(normal), radius(radius), hole_radius(hole_radius)
  {
  }

  Disc*
  Disc::copy() const
  {
    Disc* disc = new Disc(center, normal, radius, hole_radius);
    
    disc->set_pigment(get_pigment().copy());
    disc->set_finish(get_finish());

    return disc;
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

  void
  Disc::translate(const Vector& v)
  {
    center += v;
    span_plane.translate(v);
  }

  void
  Disc::rotate(const Vector& rot)
  {
    center = center.rotate(rot);
    normal = normal.rotate(rot);
    span_plane.rotate(rot);
  }

  Vector
  Disc::get_max_extent() const
  {
    // calculate inclination against each axis
    float x_incl = fabs(M_PI / 2 - acos(normal.dot(Vector::unit_x())));
    float y_incl = fabs(M_PI / 2 - acos(normal.dot(Vector::unit_y())));
    float z_incl = fabs(M_PI / 2 - acos(normal.dot(Vector::unit_z())));

    return center + Vector(cos(x_incl), cos(y_incl), cos(z_incl)) * radius;
  }

  Vector
  Disc::get_min_extent() const
  {
    // calculate inclination against each axis
    float x_incl = fabs(M_PI / 2 - acos(normal.dot(Vector::unit_x())));
    float y_incl = fabs(M_PI / 2 - acos(normal.dot(Vector::unit_y())));
    float z_incl = fabs(M_PI / 2 - acos(normal.dot(Vector::unit_z())));

    return center - Vector(cos(x_incl), cos(y_incl), cos(z_incl)) * radius;
  }

}
