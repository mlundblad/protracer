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

#ifndef FINISH_MODIFICATION_H
#define FINISH_MODIFICATION_H

#include "object_modification.h"
#include "object.h"
#include "finish.h"

namespace Protracer {
  class FinishModification : public ObjectModification {
  public:
    FinishModification(const Finish& finish) : finish(finish) {}
    
    virtual void apply(Object* object) const;
  private:
    Finish finish;
  };
}

#endif //FINISH_MODIFICATION_H

