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

#ifndef DISC_H
#define DISC_H

#include "planar_object.h"

namespace Protracer {

  class Disc : public PlanarObject {
  public:
    Disc(const Vector& center, const Vector& normal, float radius,
	 float hole_radius, Pigment* pigment, const Finish& finish);
    
    HitCalculation calculate_hit(const Ray& ray) const;

  private:
    Vector center;
    Vector normal;
    float radius;
    float hole_radius;
  };

}

#endif //DISC_H
