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

#include "union.h"

#include <limits>

namespace Protracer {

  Union::~Union()
  {
    for (Object* o : objects) {
      delete o;
    }
  }

  void
  Union::add_object(Object* o)
  {
    objects.push_back(o);
  }

  Union*
  Union::copy() const
  {
    Union* result = new Union;
    
    for (const Object* o : objects) {
      result->add_object(o->copy());
    }
    
    if (has_custom_pigment())
      result->set_pigment(get_pigment().copy());
    if (has_custom_finish())
      result->set_finish(get_finish());

    return result;
  }

  HitCalculation
  Union::calculate_hit(const Ray& ray) const
  {
    HitCalculation hc;
    float nearest = std::numeric_limits<float>::infinity();
    const Object* hit_object = nullptr;

    for (const Object* o : objects) {
      HitCalculation hc2 = o->calculate_hit(ray);

      if (hc2.is_hit() && hc2.get_distance() <= nearest) {
	hc = hc2;
	nearest = hc2.get_distance();
	hit_object = o;
      }
    }

    // override texture with the Union's in case the hit subobject
    // doesn't have specied them
    if (hc.is_hit()) {
      if (!hit_object->has_custom_pigment()) {
	// for now, only consider single pigment color...
	hc.set_color(get_pigment().get_color());
      }
      
      if (!hit_object->has_custom_finish()) {
	hc.set_finish(get_finish());
      }
    }

    return hc;
  } 

  Vector
  Union::get_max_extent() const
  {
    float max_x = -std::numeric_limits<float>::infinity();
    float max_y = -std::numeric_limits<float>::infinity();
    float max_z = -std::numeric_limits<float>::infinity();

    for (const Object* o : objects) {
      const Vector ext = o->get_max_extent();

      if (max_x < ext.get_x())
	max_x = ext.get_x();
      if (max_y < ext.get_y())
	max_y = ext.get_y();
      if (max_z < ext.get_z())
	max_z = ext.get_z();
    }

    return Vector(max_x, max_y, max_z);
  }

  Vector
  Union::get_min_extent() const
  {
    float min_x = std::numeric_limits<float>::infinity();
    float min_y = std::numeric_limits<float>::infinity();
    float min_z = std::numeric_limits<float>::infinity();

    for (const Object* o : objects) {
      const Vector ext = o->get_min_extent();

      if (min_x > ext.get_x())
	min_x = ext.get_x();
      if (min_y > ext.get_y())
	min_y = ext.get_y();
      if (min_z < ext.get_z())
	min_z = ext.get_z();
    }

    return Vector(min_x, min_y, min_z);
  }

  bool
  Union::is_inside(const Vector& v) const
  {
    for (const Object* o : objects) {
      if (o->is_inside(v))
	return true;
    }

    return false;
  }

  void
  Union::translate(const Vector& v)
  {
    for (Object* o : objects) {
      o->translate(v);
    }
  }

  void
  Union::rotate(const Vector& r)
  {
    for (Object* o : objects) {
      o->rotate(r);
    }
  }
}
