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

#ifndef FOG_H
#define FOG_H

#include "color.h"
#include "ray.h"

namespace Protracer {

  class Fog {
  public:
    Fog(const Color& color, float distance) :
      color(color), distance(distance) {}

    const Color& get_color() const { return color; }
    virtual float calculate_contribution(const Ray& ray,
					 float distance) const = 0;

  protected:
    Color color;
    float distance;
  };
}

#endif //FOG_H
