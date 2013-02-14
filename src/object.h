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

#ifndef OBJECT_H
#define OBJECT_H

#include "item.h"
#include "finish.h"
#include "pigment.h"
#include "hit_calculation.h"
#include "ray.h"

namespace Protracer {
  class Object : public Item {
  public:
    Object();
    virtual ~Object() { delete pigment; }

    virtual Object* copy() const = 0;

    virtual HitCalculation calculate_hit(const Ray& ray) const = 0;
    const Finish& get_finish() const { return finish; }
    const Pigment& get_pigment() const { return *pigment; }

    // theese will need to be polymorphically overridable for extending classes
    // like PlanarObject which needs to sync the pigment with a spanning plane
    virtual void set_finish(const Finish& finish);
    virtual void set_pigment(Pigment* pigment);

    // determines whether a specific finish and pigment has been set for the
    // object (to be used to be able to override a "higher" texture f.ex. for
    // unions
    bool has_custom_finish() const { return custom_finish; }
    bool has_custom_pigment() const { return custom_pigment; }

    // get bounding box extents
    virtual Vector get_max_extent() const = 0;
    virtual Vector get_min_extent() const = 0;

    // determine if a vector is located inside an object
    virtual bool is_inside(const Vector& v) const = 0;

  protected:
    void copy_modifications(const Object* object);

  private:
    Finish finish;
    Pigment* pigment;
    bool custom_finish;
    bool custom_pigment;
  };
}

#endif //OBJECT_H
