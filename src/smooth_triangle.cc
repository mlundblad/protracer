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

#include "smooth_triangle.h"

namespace Protracer {

  SmoothTriangle::SmoothTriangle(const Vector& c0, const Vector& n0,
				 const Vector& c1, const Vector& n1,
				 const Vector& c2, const Vector& n2) :
    Triangle(c0, c1, c2), n0(n0), n1(n1), n2(n2)
  {
  }

  SmoothTriangle*
  SmoothTriangle::copy() const
  {
    SmoothTriangle* triangle =
      new SmoothTriangle(get_c0(), n0, get_c1(), n1, get_c2(), n2);

    if (has_custom_finish())
      triangle->set_pigment(get_pigment().copy());
    if (has_custom_pigment())
      triangle->set_finish(get_finish());

    return triangle;
  }

  HitCalculation
  SmoothTriangle::calculate_hit(const Ray& ray) const
  {
    HitCalculation hc;
    float u;
    float v;

    std::tie(hc, u, v) = calculate_hit_with_coords(ray);

    if (hc.is_hit()) {
      // recalculate hitpoint normal based on the vertex normals
      // using Phong normal interpolation
      // u = relative distance along the c0->c1 edge [0..1]
      // v = relative distance along the c0->c2 edge [0..1]

      if (v == 1.0) {
	// special case: avoid divide by 0
	return HitCalculation(true, hc.get_distance(),
			      n2, hc.get_color(), hc.get_finish());
      }

      float u1 = u / (1.0 - v);
      Vector na = (1.0 - v) * n0 + v * n2;
      Vector nb = (1.0 - v) * n1 + v * n2;
      Vector n = (1.0 - u1) * na + u1 * nb;

      return HitCalculation(true, hc.get_distance(), n, hc.get_color(),
			    hc.get_finish());
    }

    return hc;
  }

  void
  SmoothTriangle::rotate(const Vector& v)
  {
    Triangle::rotate(v);
    n0 = n0.rotate(v);
    n1 = n1.rotate(v);
    n2 = n2.rotate(v);
  }

}
