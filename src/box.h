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

#ifndef BOX_H
#define BOX_H

#include "object.h"
#include "plane.h"

namespace Protracer {

  class Box : public Object {
  public:
    Box(const Vector& c1, const Vector& c2, Pigment* pigment,
	const Finish& finish);

    virtual HitCalculation calculate_hit(const Ray& ray) const;

    virtual void translate(const Vector& v);
    virtual void rotate(const Vector& r);

  private:
    // define enough points and side vectors to be able to efficiantly
    // calculate hits on all four side areas
    Vector bottom_front_left;
    Vector bottom_back_left;
    Vector bottom_front_right;
    Vector top_front_left;

    // sides
    Vector up;
    Vector right;
    Vector in;

    // spanning planes
    Plane front_plane;
    Plane back_plane;
    Plane top_plane;
    Plane bottom_plane;
    Plane left_plane;
    Plane right_plane;

    // calculate hit against one "side pane"
    HitCalculation calculate_hit(const Ray& ray, const Plane& span_plane,
				 const Vector& point,
				 const Vector& va, const Vector& vb) const;
    
  };
}

#endif //BOX_H
