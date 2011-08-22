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

#include "sphere.h"
#include <math.h>

namespace Protracer {

  Sphere::Sphere(const Vector& center, float radius, const Vector& pole,
		 const Vector& equator, const Pigment& pigment,
		 const Finish& finish) :
    Object(pigment, finish)
  {
    this->center = center;
    this->radius = radius;
    this->radius_sqr = radius * radius;
    this->pole = Vector_normalize(pole);
    this->equator = Vector_normalize(equator);
  }

  HitData
  Sphere::calculate_hit(const Ray& ray) const
  {
    /* Vector  oc;*/
    scalar  l2oc;
    scalar  tca;
    scalar  t2hc;
    scalar  distance;
    
    /*Vector  ri;
    Vector  rn;*/
    Vector  tempVect;
    
    /*oc = Vector_subtract( center,
                          Ray_origin( ray ));*/
    l2oc = Vector_dotProduct(Vector_subtract(center, Ray_origin(ray)),
			     Vector_subtract(center, Ray_origin(ray)));
    tca = Vector_dotProduct(Vector_subtract(center, Ray_origin(ray)), 
			    Ray_direction(ray));
    
    
    t2hc = radius_sqr - l2oc + tca * tca;
    
 
    if (!(l2oc < radius_sqr)) {
	if (tca + EPS >= 0 && t2hc >= 0 ) {
	    distance = tca - sqrt( t2hc );
	    
	    tempVect = Vector_add( Ray_origin( ray ),
				   Vector_multiply( distance,
						    Ray_direction( ray ) ) );
	    
	    tempVect = Vector_multiply(1.0 / radius,
				       Vector_subtract(tempVect, center));
	    
	    return HitData_createHit(distance,
				     tempVect, color_at(tempVect));

	}
	else
	    return HitData_createNoHit();
    }
    
    distance = tca + sqrt(t2hc);
    
    tempVect = Vector_add(Ray_origin(ray),
			   Vector_multiply(distance,
					   Ray_direction(ray)));
    
    tempVect = Vector_multiply(-1.0 / radius,
			       Vector_subtract(tempVect, center));
    
    
    return HitData_createHit(distance,
			     tempVect, color_at(tempVect));
  }

  Color
  Sphere::color_at(const Vector& normal) const
  {
    float phi,temp;
    float theta;
    float u,v; /* Coordinates in % of bitmap. */
    Bitmap bitmap;
    /*Color retColor;*/

    if (Pigment_type(pigment) == PIGMENT_COLOR)
      return Pigment_color(pigment);
    

    phi = acos( -Vector_dotProduct(normal, pole));
    v = 1 - phi / M_PI;
     
    if ( v == 1.0 || v == 0.0 ) {
      u = 0.0;
    } else {
        temp = Vector_dotProduct(normal, equator) / sin(phi);
        temp = temp > 1.0 ? 1.0 : temp;
	temp = temp < -1.0 ? -1.0 : temp;
        
        theta = acos(temp) / (2*M_PI);
        
        u = Vector_dotProduct(Vector_crossProduct(equator, pole),
			      normal) > 0 ?
	  theta : 1 - theta;
        
    }
    
    
    
    /* Ok, u and v are the % coordinates into the bitmap.
       Lets return the correct color for the given point. */
    bitmap = Pigment_bitmap(pigment);
    
    /*fprintf( stderr, "w: %d h: %d u: %f v: %f\n", Bitmap_width( bitmap ),
      Bitmap_height( bitmap ),
      u, v);*/
    
    return Bitmap_colorAt( bitmap, 
                           (Bitmap_width( bitmap ) - 1) * u,
                           (Bitmap_height( bitmap ) - 1) * v );

  }

}
