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

#ifndef LIGHT_H
#define LIGHT_H

#include "item.h"
#include "vector.h"

namespace Protracer {
  class Light : public Item {
  public:
    Light(const Vector& position);
    
    const Vector& get_position() const { return position; }

    virtual void translate(const Vector& v);
    virtual void rotate(const Vector& v);

  private:
    Vector position;
  };

}

#endif //LIGHT_H
