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

#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>

namespace Protracer {

  // CRTP base class for vector expressions
  template <typename E>
  class VectorExpression {
  public:
    float get_x() const { static_cast<const E&>(*this).get_x(); }
    float get_y() const { static_cast<const E&>(*this).get_y(); }
    float get_z() const { static_cast<const E&>(*this).get_z(); }

    operator E&() { return static_cast<E&>(*this); }
    operator const E&() const { return static_cast<const E&>(*this); }
  };

  class Vector : public VectorExpression<Vector> {
  public:
    Vector() : x(0), y(0), z(0) {}
    Vector(float x, float y, float z) : x(x), y(y), z(z) {}

    template <typename E>
    Vector(const VectorExpression<E>& expr) {
      const E& v = expr;
      
      x = v.get_x();
      y = v.get_y();
      z = v.get_z();
    }

    float get_x() const { return x; }
    float get_y() const { return y; }
    float get_z() const { return z; }

    Vector& operator=(const Vector& u);

    float dot(const Vector& u) const { return x * u.x + y * u.y + z * u.z; }

    float length() const { return sqrt(x * x + y * y + z * z); }
    Vector normal() const;

  private:
    float x;
    float y;
    float z;
  };

  template <typename E1, typename E2>
  class VectorCross : public VectorExpression<VectorCross<E1, E2> > {
    const E1& u;
    const E2& v;
  public:
    VectorCross(const VectorExpression<E1>& u, const VectorExpression<E2>& v) :
      u(u), v(v) {}
    
    float get_x() const { return u.get_y() * v.get_z() -
	                         u.get_z() * v.get_y(); }
    float get_y() const { return u.get_z() * v.get_x() -
	                         u.get_x() * v.get_z(); }
    float get_z() const { return u.get_x() * v.get_y() -
	                         u.get_y() * v.get_x(); }
  };

  template <typename E>
  class VectorNegation : public VectorExpression<VectorNegation<E> > {
    const E& u;
  public:
    VectorNegation(const VectorExpression<E>& u) : u(u) {}

    float get_x() const { return -u.get_x(); }
    float get_y() const { return -u.get_y(); }
    float get_z() const { return -u.get_z(); }
  };

  template <typename E1, typename E2>
  class VectorAddition : public VectorExpression<VectorAddition<E1, E2> > {
    const E1& u;
    const E2& v;
  public:
    VectorAddition(const VectorExpression<E1>& u,
		   const VectorExpression<E2>& v) : u(u), v(v) {}
    
    float get_x() const { return u.get_x() + v.get_x(); }
    float get_y() const { return u.get_y() + v.get_y(); }
    float get_z() const { return u.get_z() + v.get_z(); }
  };

  template <typename E1, typename E2>
  class VectorDifference : public VectorExpression<VectorDifference<E1, E2> > {
    const E1& u;
    const E2& v;
  public:
    VectorDifference(const VectorExpression<E1>& u,
		     const VectorExpression<E2>& v) : u(u), v(v) {}
    
    float get_x() const { return u.get_x() - v.get_x(); }
    float get_y() const { return u.get_y() - v.get_y(); }
    float get_z() const { return u.get_z() - v.get_z(); }
  };

  template <typename E>
  class VectorScale : public VectorExpression<VectorScale<E> > {
    float s;
    const E& u;
  public:
    VectorScale(float s, const VectorExpression<E>& u) : s(s), u(u) {}

    float get_x() const { return s * u.get_x(); }
    float get_y() const { return s * u.get_y(); }
    float get_z() const { return s * u.get_z(); }
  };

  template <typename E1, typename E2>
  const VectorCross<E1, E2>
  operator*(const VectorExpression<E1>& u, const VectorExpression<E2>& v)
  {
    return VectorCross<E1, E2>(u, v);
  }

  template <typename E>
  const VectorNegation<E>
  operator-(const VectorExpression<E>& u)
  {
    return VectorNegation<E>(u);
  }

  template <typename E1, typename E2>
  const VectorAddition<E1, E2>
  operator+(const VectorExpression<E1>& u, const VectorExpression<E2>& v)
  {
    return VectorAddition<E1, E2>(u, v);
  }

  template <typename E1, typename E2>
  const VectorDifference<E1, E2>
  operator-(const VectorExpression<E1>& u, const VectorExpression<E2>& v)
  {
    return VectorDifference<E1, E2>(u, v);
  }

  template <typename E>
  const VectorScale<E>
  operator*(float s, const VectorExpression<E>& v)
  {
    return VectorScale<E>(s, v);
  }

  template <typename E>
  const VectorScale<E>
  operator*(const VectorExpression<E>& v, float s)
  {
    return VectorScale<E>(s, v);
  }

}

#endif //VECTOR_H
