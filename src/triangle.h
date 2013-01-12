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

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "planar_object.h"
#include "vector.h"
#include "hit_calculation.h"
#include "plane.h"
#include "finish.h"

namespace Protracer {

  class Triangle : public PlanarObject {
  public:
    Triangle(const Vector& c0, const Vector& c1, const Vector& c2);
    
    Triangle* copy() const;

    virtual HitCalculation calculate_hit(const Ray& ray) const;
    virtual void translate(const Vector& v);
    virtual void rotate(const Vector& rot);

    virtual Vector get_max_extent() const;
    virtual Vector get_min_extent() const;

  private:
    Vector t0;
    Vector va;
    Vector vb;
    float aa; // va dot va
    float bb; // vb dot vb
    float ab; // va dot vb
  };

}

#endif //TRIANGLE_H
