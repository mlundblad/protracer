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

#include "composed_transformation.h"

namespace Protracer {

  ComposedTransformation::~ComposedTransformation()
  {
    for (Transformation* t : transformations) {
      delete t;
    }
  }

  void
  ComposedTransformation::apply(Item* item) const
  {
    for (const Transformation* t : transformations) {
      t->apply(item);
    }
  }

  ComposedTransformation*
  ComposedTransformation::copy() const
  {
    std::list<Transformation*> trans;

    for (const Transformation* t : transformations) {
      trans.push_back(t->copy());
    }

    return new ComposedTransformation(trans);
  }

}
