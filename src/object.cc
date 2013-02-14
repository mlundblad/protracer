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

#include "object.h"
#include "color_pigment.h"

namespace Protracer {

  Object::Object()
  {
    // set default pigment
    pigment = new ColorPigment;
  }

  void
  Object::set_finish(const Finish& finish)
  {
    this->finish = finish;
    this->custom_finish = true;
  }
  
  void
  Object::set_pigment(Pigment* pigment)
  {
    if (pigment != this->pigment) {
      delete this->pigment;
      this->pigment = pigment;
      this->custom_pigment = true;
    }
  }

  void
  Object::copy_modifications(const Object* object)
  {
    if (object->has_custom_pigment())
      set_pigment(object->get_pigment().copy());
    if (object->has_custom_finish())
      set_finish(object->get_finish());
  }
}
