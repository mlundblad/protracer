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

#ifndef PLANAR_OBJECT_H
#define PLANAR_OBJECT_H

#include "object.h"
#include "plane.h"

#include <iostream>

namespace Protracer {

  class PlanarObject : public Object {
  public:
    // all planar objects are without an interior volume
    virtual bool is_inside(const Vector& v) const { return false; }

  protected:
    PlanarObject(const Vector& normal, const Vector& point,
		 Pigment* pigment, const Finish& finish) :
      Object(pigment, finish), span_plane(normal, point, pigment, finish) {}
    ~PlanarObject() { pigment = 0; }

    // override to allow syncing pigment with the spanning plane
    void set_pigment(Pigment* pigment);

    Plane span_plane;
  };

}

#endif //PLANAR_OBJECT_H
