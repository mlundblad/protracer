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

#ifndef SPHERE_H
#define SPHERE_H

#include "Vector.h"
#include "ray.h"
#include "HitData.h"
#include "object.h"

namespace Protracer {

  class Sphere : public Object {
  public:

    static const float POLE_DEFAULT_X = 0.0f;
    static const float POLE_DEFAULT_Y = 1.0f;
    static const float POLE_DEFAULT_Z = 0.0f;
    static const float EQUATOR_DEFAULT_X = 1.0f;
    static const float EQUATOR_DEFAULT_Y = 0.0f;
    static const float EQUATOR_DEFAULT_Z = 0.0f;

    Sphere(const Vector& center, float radius, const Vector& pole,
	   const Vector& equator, Pigment* pigment,
	   const Finish& finish);

    virtual HitData calculate_hit(const Ray& ray) const;

  private:
    Vector center;
    float radius;
    float radius_sqr;
    Vector pole;
    Vector equator;

    Color color_at(const Vector& normal) const;

    static const float EPS = 0.001f;
  };
}

#endif //SPHERE_H
