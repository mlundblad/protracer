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

#include "box.h"

namespace Protracer {
  
  Box::Box(const Vector& c1, const Vector& c2, Pigment* pigment,
	   const Finish& finish) :
    Object(pigment, finish),
    front_plane(Plane(Vector::unit_z(), c1, pigment->copy(), finish)),
    back_plane(Plane(Vector::unit_z(), c2, pigment->copy(), finish)),
    bottom_plane(Plane(Vector::unit_y(), c1, pigment->copy(), finish)),
    top_plane(Plane(Vector::unit_y(), c2, pigment->copy(), finish)),
    left_plane(Plane(Vector::unit_x(), c1, pigment->copy(), finish)),
    right_plane(Plane(Vector::unit_x(), c2, pigment->copy(), finish))
  {
    bottom_front_left = c1;
    bottom_back_left = c1 + Vector(0, 0, (c2 - c1).get_z());
    bottom_front_right = c1 + Vector((c2 - c1).get_x(), 0, 0);
    top_front_left = c1 + Vector(0, (c2 - c1).get_y(), 0);

    // the side vectors are initially aligned to the coordinate axis
    up = Vector(0, (c2 - c1).get_y(), 0);
    right = Vector((c2 - c1).get_x(), 0, 0);
    in = Vector(0, 0, (c2 - c1).get_z());

    rotation = 0;

    // these are really kept as distances (ie. can be negative)
    width = c2.get_x() - c1.get_x();
    height = c2.get_y() - c1.get_y();
    depth = c2.get_z() - c1.get_z();
  }

  HitCalculation
  Box::calculate_hit(const Ray& ray) const
  {
    HitCalculation hc1 = calculate_hit(ray, front_plane, bottom_front_left,
				      up, right);
    HitCalculation hc2 = calculate_hit(ray, back_plane, bottom_back_left,
				       up, right);
    HitCalculation hc3 = calculate_hit(ray, top_plane, top_front_left,
				       in, right);
    HitCalculation hc4 = calculate_hit(ray, bottom_plane, bottom_front_left,
				       in, right);
    HitCalculation hc5 = calculate_hit(ray, left_plane, bottom_front_left,
				       in, up);
    HitCalculation hc6 = calculate_hit(ray, right_plane, bottom_front_right,
				       in, up);

    HitCalculation hc = hc1;

    if (hc2.is_hit() && hc2.get_distance() < hc.get_distance())
      hc = hc2;
    if (hc3.is_hit() && hc3.get_distance() < hc.get_distance())
      hc = hc3;
    if (hc4.is_hit() && hc4.get_distance() < hc.get_distance())
      hc = hc4;
    if (hc5.is_hit() && hc5.get_distance() < hc.get_distance())
      hc = hc5;
    if (hc6.is_hit() && hc6.get_distance() < hc.get_distance())
      hc = hc6;
 
    return hc;
  }

  HitCalculation
  Box::calculate_hit(const Ray& ray, const Plane& span_plane,
		     const Vector& point,
		     const Vector& va, const Vector& vb) const
  {
    HitCalculation hc = span_plane.calculate_hit(ray);
    
    if (hc.is_hit()) {
      // we might want to precalculate these scalar products (see Triangle)
      float aa = va.dot(va);
      float bb = vb.dot(vb);
      float ab = va.dot(vb);
      Vector ri = ray.get_origin() + hc.get_distance() * ray.get_direction();
      Vector q = ri - point;

      float u = (bb * q.dot(va) - ab * q.dot(vb)) / (aa * bb - ab * ab);
      
      if (0 < u && u < 1) {
	float v = (q.dot(vb) - u * ab) / bb;

	if (0 < v && v < 1) {
	  return hc;
	}
      }
    }

    return HitCalculation(false);
  }

  void
  Box::set_pigment(Pigment* pigment)
  {
    this->pigment = pigment;
    front_plane.set_pigment(pigment->copy());
    back_plane.set_pigment(pigment->copy());
    top_plane.set_pigment(pigment->copy());
    bottom_plane.set_pigment(pigment->copy());
    left_plane.set_pigment(pigment->copy());
    right_plane.set_pigment(pigment->copy());
  }

  void
  Box::translate(const Vector& v)
  {
    bottom_front_left += v;
    bottom_back_left += v;
    bottom_front_right += v;
    top_front_left += v;
    
    front_plane.translate(v);
    back_plane.translate(v);
    top_plane.translate(v);
    bottom_plane.translate(v);
    left_plane.translate(v);
    right_plane.translate(v);
  }

  void
  Box::rotate(const Vector& r)
  {
    bottom_front_left = bottom_front_left.rotate(r);
    bottom_back_left = bottom_back_left.rotate(r);
    bottom_front_right = bottom_front_right.rotate(r);
    top_front_left = top_front_left.rotate(r);
    
    up = up.rotate(r);
    right = right.rotate(r);
    in = in.rotate(r);

    front_plane.rotate(r);
    back_plane.rotate(r);
    top_plane.rotate(r);
    bottom_plane.rotate(r);
    left_plane.rotate(r);
    right_plane.rotate(r);

    rotation += r;
  }

  bool
  Box::is_inside(const Vector& v)
  {
    // the relative position in the box
    const Vector p = v - bottom_front_left;
    // align with the original coordinate system
    const Vector pr = p.rotate(-rotation);

    return (width > 0 ? pr.get_x() >= 0 && pr.get_x() < width :
	    pr.get_x() <= 0 && pr.get_x() > width) &&
      (height > 0 ? pr.get_y() >= 0 && pr.get_y() < height :
       pr.get_y() <= 0 && pr.get_y() > height) &&
      (depth > 0 ? pr.get_z() >= 0 && pr.get_z() < depth :
       pr.get_z() <= 0 && pr.get_x() > depth);
  }
}
