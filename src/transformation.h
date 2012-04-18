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

#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "object_modification.h"
#include "item.h"

namespace Protracer {

  class Transformation : public ObjectModification {
  public:
    virtual void apply(Item* item) const = 0;
    virtual void apply(Object* o) const { apply(static_cast<Item*> (o)); }
    virtual Transformation* copy() const = 0;

    class Applier {
    public:
      Applier(Item* item) : item(item) {}
      
      void operator() (const Transformation* t) { t->apply(item); }
      
    private:
      Item* item;
    };

    class Deleter {
    public:
      void operator() (Transformation* t) { delete t; }
    };

  };
}

#endif //TRANSFORMATION_H
