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

#ifndef CYLINDER_H
#define CYLINDER_H

#include "object.h"

namespace Protracer {

  class Cylinder : public Object {
  public:
    Cylinder(const Vector& base_point, const Vector& cap_point, float radius,
	     Pigment* pigment, const Finish& finish) :
      Object(pigment, finish), base_point(base_point), cap_point(cap_point),
      radius(radius) {}

    virtual void translate(const Vector& v);
    virtual void rotate(const Vector& r);

  private:
    Vector base_point;
    Vector cap_point;
    float radius;
    bool open;
  };

}

#endif //CYLINDER_H
