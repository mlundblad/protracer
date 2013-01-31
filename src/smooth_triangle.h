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

#ifndef SMOOTH_TRIANGLE_H
#define SMOOTH_TRIANGLE_H

#include "triangle.h"

namespace Protracer {

  class SmoothTriangle : public Triangle {
  public:
    SmoothTriangle(const Vector& c0, const Vector& n0,
		   const Vector& c1, const Vector& n1,
		   const Vector& c2, const Vector& n2);

    virtual SmoothTriangle* copy() const;
    virtual HitCalculation calculate_hit(const Ray& ray) const;
    virtual void rotate(const Vector& v);

  private:
    Vector n0;
    Vector n1;
    Vector n2;
  };

}

#endif //SMOOTH_TRIANGLE_H
