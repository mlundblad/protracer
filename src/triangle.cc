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

#include "triangle.h"
#include "Bitmap.h"

namespace Protracer {

  Triangle::Triangle(const Vector& c0, const Vector& c1, const Vector& c2,
	   Pigment* pigment, const Finish& finish,
	   bool relative) :
    Object(pigment, finish),
    va(relative ? c1 : Vector_subtract(c1, c0)),
    vb(relative ? c2 : Vector_subtract(c2, c0)),
    span_plane(Vector_normalize(Vector_crossProduct(va, vb)), c0, pigment,
	       finish)
  {
    t0 = c0;
    aa = Vector_dotProduct(va, va);
    bb = Vector_dotProduct(vb, vb);
    ab = Vector_dotProduct(va, vb);
  }

  Triangle::~Triangle()
  {
    // let the span plane delete the pigment
    pigment = 0;
  }

  HitData
  Triangle::calculate_hit(const Ray& ray) const
  {
    HitData hd = span_plane.calculate_hit(ray);

    if (HitData_hit(hd)) {
      Vector ri = Vector_add(Ray_origin(ray),
			     Vector_multiply(HitData_distance(hd),
					     Ray_direction(ray)));
      Vector q = Vector_subtract(ri, t0);
      float u = (bb * Vector_dotProduct(q, va) - 
		 ab * Vector_dotProduct(q, vb)) / (aa * bb - ab * ab);
      
      if (0 < u && u < 1) {
	float v = (Vector_dotProduct(q, vb) - u * ab) / bb;
	
	if (0 < v && v < 1 && u + v <= 1) {
	  if (!pigment->is_uniform())
	    HitData_setColor(hd, pigment->get_color(u, v));
	  
	  return hd;
	}
      }
    }

    return HitData_createNoHit();
  }

}
