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

#ifndef HIT_CALCULATION_H
#define HIT_CALCULATION_H

#include "color.h"
#include "vector.h"

namespace Protracer {
  class HitCalculation {
  public:
    HitCalculation(bool hit = false) : hit(hit) {}
    HitCalculation(bool hit, float distance, const Vector& normal,
		   const Color& color) :
      hit(hit), distance(distance), normal(normal), color(color) {}

    bool is_hit() const { return hit; }
    float get_distance() const { return distance; }
    const Vector& get_normal() const { return normal; }
    const Color& get_color() const { return color; }

    void set_color(const Color& c) { color = c; }

  private:
    bool hit;
    float distance;
    Vector normal;
    Color color;
  };

}

#endif //HIT_CALCULATION_H
