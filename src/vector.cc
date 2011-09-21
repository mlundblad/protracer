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

  float
  Vector::dot(const Vector& u) const
  {
    return x * u.x + y * u.y + z * u.z;
  }

  Vector
  Vector::operator*(const Vector& u) const
  {
    return Vector(y * u.z - z * u.y, z * u.x - x * u.z, x * u.y - y * u.x);
  }

  Vector
  Vector::operator-() const
  {
    return Vector(-x, -y, -z);
  }

  Vector
  Vector::operator+(const Vector& u) const
  {
    return Vector(x + u.x, y + u.y, z + u.z);
  }

  Vector
  Vector::operator-(const Vector& u) const
  {
    return Vector(x - u.x, y - u.y, z - u.z);
  }

  Vector
  Vector::operator*(float s) const
  {
    return Vector(x * s, y * s, z * s);
  }

  float
  Vector::length() const
  {
    return sqrt(x * x + y * y + z * z);
  }

  Vector
  Vector::normal() const
  {
    const Vector& v = *this;
    float len = length();

    return v * (1.0 / len);
  }

  Vector
  operator*(float s, const Vector& v)
  {
    return v * s;
  }

}
