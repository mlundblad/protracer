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

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "object.h"
#include "Vector.h"
#include "Pigment.h"
#include "HitData.h"
#include "plane.h"
#include "finish.h"

namespace Protracer {

  class Triangle : public Object {
  public:
    // if relative is true, c1 and c2 are taken to be vectors relative c0
    // forming two of the triangle's vertices
    Triangle(const Vector& c0, const Vector& c1, const Vector& c2,
	     const Pigment& pigment, const Finish& finish,
	     bool relative = false);

    virtual HitData calculate_hit(const Ray& ray) const;

  private:
    Vector t0;
    Vector va;
    Vector vb;
    Plane span_plane;
    float aa; // va dot va
    float bb; // vb dot vb
    float ab; // va dot vb
  };

}

#endif //TRIANGLE_H
