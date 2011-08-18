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

#ifndef PLANE_H
#define PLANE_H

#include "object.h"
#include "HitData.h"
#include "Vector.h"
#include "Ray.h"
#include "Pigment.h"
#include "Finish.h"

namespace Protracer {

  class Plane : public Object {
  public:
    Plane(const Vector& normal, const Vector& point, const Pigment& pigment,
	  const Finish& finish);

    virtual HitData calculate_hit(const Ray& ray) const;

  private:
    Vector normal;
    Vector point;
    float d;
  };

}

#endif //PLANE_H
