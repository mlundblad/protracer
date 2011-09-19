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

#ifndef RAY_H
#define RAY_H

#include "Vector.h"

namespace Protracer {
  
  class Ray {
  public:
    Ray() {}
    Ray(const Vector& origin, const Vector& direction) :
      origin(origin), direction(Vector_normalize(direction)) {}

    const Vector& get_origin() const { return origin; }
    const Vector& get_direction() const { return direction; }

  private:
    Vector origin;
    Vector direction;
  };
}

#endif //RAY_H
