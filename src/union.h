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

#ifndef UNION_H
#define UNION_H

#include "object.h"

#include <vector>
#include <iterator>

namespace Protracer {

  class Union : public Object {
  public:
    virtual ~Union();

    void add_object(Object* o);

    Union* copy() const;
    HitCalculation calculate_hit(const Ray& ray) const;
    Vector get_max_extent() const;
    Vector get_min_extent() const;
    bool is_inside(const Vector& v) const;

    void translate(const Vector& v);
    void rotate(const Vector& r);

  private:
    std::vector<Object*> objects;
  };

}

#endif //UNION_H
