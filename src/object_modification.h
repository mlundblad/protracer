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

#ifndef OBJECT_MODIFICATION_H
#define OBJECT_MODIFICATION_H

#include "object.h"

#include <iterator>

namespace Protracer {
  class ObjectModification {
  public:
    virtual void apply(Object* object) const = 0;

    // implement an std::for_each functor
    class Applier {
    public:
      Applier(Object* object) : object(object) {}

      void operator() (const ObjectModification* om) { om->apply(object); }

    private:
      Object* object;
    };

    class Deleter {
    public:
      void operator() (ObjectModification* om) { delete om; }
    };
  };
}  

#endif //MODIFY_H
