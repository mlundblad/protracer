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

#include <algorithm>
#include <limits>

using std::max;
using std::min;

namespace Protracer {
  
  Box::Box(const Vector& c1, const Vector& c2) :
    front_plane(Plane(Vector::unit_z(), c1)),
    back_plane(Plane(Vector::unit_z(), c2)),
    bottom_plane(Plane(Vector::unit_y(), c1)),
    top_plane(Plane(Vector::unit_y(), c2)),
    left_plane(Plane(Vector::unit_x(), c1)),
    right_plane(Plane(Vector::unit_x(), c2))
  {
    bottom_front_left = c1;
    bottom_back_left = c1 + Vector(0, 0, (c2 - c1).get_z());
    bottom_front_right = c1 + Vector((c2 - c1).get_x(), 0, 0);
    bottom_back_right = c1 + Vector((c2 - c1).get_x(), 0, (c2 - c1).get_z());
    top_front_left = c1 + Vector(0, (c2 - c1).get_y(), 0);
    top_back_left = c1 + Vector(0, (c2 - c1).get_y(), (c2 - c1).get_z());
    top_front_right = c1 + Vector((c2 - c1).get_x(), (c2 - c1).get_y(), 0);
    top_back_right = c2;

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
    // calculate hits for each surface
    HitCalculation hcs[6] = {calculate_hit(ray, front_plane, bottom_front_left,
                                           up, right),
                             calculate_hit(ray, back_plane, bottom_back_left,
                                           up, right),
                             calculate_hit(ray, top_plane, top_front_left,
                                           in, right),
                             calculate_hit(ray, bottom_plane, bottom_front_left,
                                           in, right),
                             calculate_hit(ray, left_plane, bottom_front_left,
                                           in, up),
                             calculate_hit(ray, right_plane, bottom_front_right,
                                           in, up)};
    HitCalculation hc;

    float nearest = std::numeric_limits<float>::infinity();

    // collect the nearest hit
    for (int i = 0 ; i < 6 ; i++) {
      if (hcs[i].is_hit() && hcs[i].get_distance() < nearest) {
        nearest = hcs[i].get_distance();
        hc = hcs[i];
      }
    } 

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

  Box*
  Box::copy() const
  {
    Box* box = new Box(Vector(0, 0, 0), Vector(0, 0, 0));

    if (has_custom_pigment())
      box->set_pigment(get_pigment().copy());
    if (has_custom_finish())
      box->set_finish(get_finish());

    box->front_plane = *(front_plane.copy());
    box->back_plane = *(back_plane.copy());
    box->bottom_plane = *(bottom_plane.copy());
    box->top_plane = *(top_plane.copy());
    box->left_plane = *(left_plane.copy());
    box->right_plane = *(right_plane.copy());

    box->bottom_front_left = bottom_front_left;
    box->bottom_back_left = bottom_back_left;
    box->bottom_front_right = bottom_front_right;
    box->bottom_back_right = bottom_back_right;
    box->top_front_left = top_front_left;
    box->top_back_left = top_back_left;
    box->top_front_right = top_front_right;
    box->top_back_right = top_back_right;
    box->up = up;
    box->right = right;
    box->in = in;
    box->rotation = rotation;
    box->width = width;
    box->height = height;
    box->depth = depth;

    return box;
  }

  void
  Box::set_pigment(Pigment* pigment)
  {
    Object::set_pigment(pigment);
    front_plane.set_pigment(pigment->copy());
    back_plane.set_pigment(pigment->copy());
    top_plane.set_pigment(pigment->copy());
    bottom_plane.set_pigment(pigment->copy());
    left_plane.set_pigment(pigment->copy());
    right_plane.set_pigment(pigment->copy());
  }

  void
  Box::set_finish(const Finish& finish)
  {
    Object::set_finish(finish);
    front_plane.set_finish(finish);
    back_plane.set_finish(finish);
    top_plane.set_finish(finish);
    bottom_plane.set_finish(finish);
    left_plane.set_finish(finish);
    right_plane.set_finish(finish);
  }


  void
  Box::translate(const Vector& v)
  {
    bottom_front_left += v;
    bottom_back_left += v;
    bottom_front_right += v;
    bottom_back_right += v;
    top_front_left += v;
    top_back_left += v;
    top_front_right += v;
    top_back_right += v;

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
    bottom_back_right = bottom_back_right.rotate(r);
    top_front_left = top_front_left.rotate(r);
    top_back_left = top_back_left.rotate(r);
    top_front_right = top_front_right.rotate(r);
    top_back_right = top_back_right.rotate(r);
    
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

  Vector
  Box::get_max_extent() const
  {
    float max_x =
      max(bottom_front_left.get_x(),
          max(bottom_back_left.get_x(),
              max(bottom_front_right.get_x(),
                  max(bottom_back_right.get_x(),
                      max(top_front_left.get_x(),
                          max(top_back_left.get_x(),
                              max(top_front_right.get_x(),
                                  top_back_right.get_x())))))));
    float max_y =
      max(bottom_front_left.get_y(),
          max(bottom_back_left.get_y(),
              max(bottom_front_right.get_y(),
                  max(bottom_back_right.get_y(),
                      max(top_front_left.get_y(),
                          max(top_back_left.get_y(),
                              max(top_front_right.get_y(),
                                  top_back_right.get_y())))))));
    float max_z =
      max(bottom_front_left.get_z(),
          max(bottom_back_left.get_z(),
              max(bottom_front_right.get_z(),
                  max(bottom_back_right.get_z(),
                      max(top_front_left.get_z(),
                          max(top_back_left.get_z(),
                              max(top_front_right.get_z(),
                                  top_back_right.get_z())))))));
    
                 
    return Vector(max_x, max_y, max_z);
  }

  Vector
  Box::get_min_extent() const
  {
    float min_x =
      min(bottom_front_left.get_x(),
          min(bottom_back_left.get_x(),
              min(bottom_front_right.get_x(),
                  min(bottom_back_right.get_x(),
                      min(top_front_left.get_x(),
                          min(top_back_left.get_x(),
                              min(top_front_right.get_x(),
                                  top_back_right.get_x())))))));
    float min_y =
      min(bottom_front_left.get_y(),
          min(bottom_back_left.get_y(),
              min(bottom_front_right.get_y(),
                  min(bottom_back_right.get_y(),
                      min(top_front_left.get_y(),
                          min(top_back_left.get_y(),
                              min(top_front_right.get_y(),
                                  top_back_right.get_y())))))));
    float min_z =
      min(bottom_front_left.get_z(),
          min(bottom_back_left.get_z(),
              min(bottom_front_right.get_z(),
                  min(bottom_back_right.get_z(),
                      min(top_front_left.get_z(),
                          min(top_back_left.get_z(),
                              min(top_front_right.get_z(),
                                  top_back_right.get_z())))))));
    
                 
    return Vector(min_x, min_y, min_z);
  }

  bool
  Box::is_inside(const Vector& v) const
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
