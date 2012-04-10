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

#include "triangle.h"

namespace Protracer {

  Triangle::Triangle(const Vector& c0, const Vector& c1, const Vector& c2,
	   Pigment* pigment, const Finish& finish,
	   bool relative) :
    va(relative ? c1 : c1 - c0),
    vb(relative ? c2 : c2 - c0),
    PlanarObject(Vector((relative ? c1 : c1 - c0) * (relative ? c2 : c2 - c0)).normal(),
                 c0, pigment, finish)
  {
    t0 = c0;
    aa = va.dot(va);
    bb = vb.dot(vb);
    ab = va.dot(vb);
  }


  Triangle*
  Triangle::copy() const
  {
    return new Triangle(t0, va, vb, pigment->copy(), finish, true);
  }

  HitCalculation
  Triangle::calculate_hit(const Ray& ray) const
  {
    HitCalculation hc = span_plane.calculate_hit(ray);

    if (hc.is_hit()) {
      Vector ri = ray.get_origin() + hc.get_distance() * ray.get_direction(); 
      Vector q = ri - t0;

      float u = (bb * q.dot(va) - ab * q.dot(vb)) / (aa * bb - ab * ab);
      
      if (0 < u && u < 1) {
	float v = (q.dot(vb) - u * ab) / bb;
	
	if (0 < v && v < 1 && u + v <= 1) {
	  if (!pigment->is_uniform())
	    hc.set_color(pigment->get_color(u, v));

	  return hc;
	}
      }
    }

    return HitCalculation(false);
  }

  void
  Triangle::translate(const Vector& v)
  {
    t0 += v;
    span_plane.translate(v);
  }

  void
  Triangle::rotate(const Vector& rot)
  {
    t0 = t0.rotate(rot);
    va = va.rotate(rot);
    vb = vb.rotate(rot);
    span_plane.rotate(rot);
  }

}
