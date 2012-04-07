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

#include "vector.h"
#include <cmath>

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

  Vector
  Vector::rotate(const Vector& around, float a) const
  {
    float u = around.get_x();
    float v = around.get_y();
    float w = around.get_z();
    float ux = u * x;
    float uy = u * y;
    float uz = u * z;
    float vx = v * x;
    float vy = v * y;
    float vz = v * z;
    float wx = w * x;
    float wy = w * y;
    float wz = w * z;
    float sa = std::sin(a);
    float ca = std::cos(a);

    return Vector(u*(ux+vy+wz)+(x*(v*v+w*w)-u*(vy+wz))*ca+(-wy+vz)*sa,
                  v*(ux+vy+wz)+(y*(u*u+w*w)-v*(ux+wz))*ca+(wx-uz)*sa,
                  w*(ux+vy+wz)+(z*(u*u+v*v)-w*(ux+vy))*ca+(-vx+uy)*sa);
  }

  Vector&
  Vector::operator+=(const Vector& v)
  {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
  }

  Vector&
  Vector::operator-=(const Vector& v)
  {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
  }

}
