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

#include "vector.h"
#include <math.h>

namespace Protracer {
  
  Vector&
  Vector::operator=(const Vector& u)
  {
    x = u.x;
    y = u.y;
    z = u.z;
    
    return *this;
  }

  Vector
  Vector::normal() const
  {
    float len_inv = 1.0 / length();

    return Vector(len_inv * x, len_inv * y, len_inv * z);
  }

}
