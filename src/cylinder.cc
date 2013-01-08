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

#include <cmath>
#include <algorithm>
#include <limits>

#include "cylinder.h"
#include "constants.h"

namespace Protracer {
  
  Cylinder::Cylinder(const Vector& base_point, const Vector& cap_point,
		     float radius, bool open) :
    base_point(base_point), cap_point(cap_point), radius(radius), open(open),
    base_disc(base_point, cap_point - base_point, radius, 0),
    cap_disc(cap_point, base_point - cap_point, radius, 0)
  {
  }


  HitCalculation
  Cylinder::calculate_hit(const Ray& ray) const
  {
    // candidate hit results
    HitCalculation results[3];

    // ray: P(t) = o + t * v;
    Vector o = ray.get_origin();
    Vector v = ray.get_direction();

    Vector ab = cap_point - base_point;
    Vector ao = o - base_point;
    Vector aoxab = ao * ab;
    Vector vxab = v * ab;
    float ab2 = ab.dot(ab);
    float a = vxab.dot(vxab);
    float b = 2 * vxab.dot(aoxab);
    float c = aoxab.dot(aoxab) - radius * radius * ab2;

    // solve second order equation : a*t^2 + b*t + c = 0
    float delta = b * b - 4 * a * c;

    if (delta >= 0.0) {
      float sqrt_delta = std::sqrt(delta);
      float t1 = (-b + sqrt_delta) / (2 * a);
      float t2 = (-b - sqrt_delta) / (2 * a);
      float tmin = std::min(t1, t2);
      float tmax = std::max(t1, t2);

      Vector near = o + tmin * v;
      Vector far = o + tmax * v;

      // check if each hit point lies within the cylinder
      // shoot a ray at each cap disc
      Ray near_base_ray(near + EPS * v, base_point - cap_point);
      HitCalculation near_base_hit = base_disc.calculate_hit(near_base_ray);
      Ray near_cap_ray(near + EPS * v, cap_point - base_point);
      HitCalculation near_cap_hit = cap_disc.calculate_hit(near_cap_ray);

      if (near_base_hit.is_hit() && near_cap_hit.is_hit()) {
	// the nearest intersection is the candidate hit for
	// the cylinder part (still need to check also the cap discs
	// if the cylinder is non-open
	
	// calculate the hit point normal using one of the cap discs
	float d = near_base_hit.get_distance();
	Vector disc_hit = near + d * Vector(base_point - cap_point).normal();
	results[0] = HitCalculation(true, tmin, disc_hit - base_point,
				    get_pigment().get_color(), get_finish());
      } else {
	// determine if the far-away hit point lies on the cylinder
	Ray far_base_ray(far - EPS * v, base_point - cap_point);
	HitCalculation far_base_hit = base_disc.calculate_hit(far_base_ray);
	Ray far_cap_ray(far - EPS * v, cap_point - base_point);
	HitCalculation far_cap_hit = cap_disc.calculate_hit(far_cap_ray);
	
	if (far_base_hit.is_hit() && far_cap_hit.is_hit()) {
	  float d = far_base_hit.get_distance();
	  Vector disc_hit = far + d * Vector(base_point - cap_point).normal();
	  // the hit point normal is negated compared to the above case
	  // for the nearest hit
	  results[0] = HitCalculation(true, tmax, base_point - disc_hit,
				    get_pigment().get_color(), get_finish());
	  
	}
      }
    }

    // calculate hits on the cap discs
    if (!open) {
      results[1] = base_disc.calculate_hit(ray);
      results[2] = cap_disc.calculate_hit(ray);
    }
    
    HitCalculation nearest_hit;
    float nearest = std::numeric_limits<float>::infinity();
    
    for (auto h : results) {
      if (h.is_hit()) {
	float d = h.get_distance();
	if (d < nearest) {
	  nearest_hit = h;
	  nearest = d;
	}
      }
    }

    return nearest_hit;
  }


  void
  Cylinder::translate(const Vector& v)
  {
    base_point += v;
    cap_point += v;
    base_disc.translate(v);
    cap_disc.translate(v);
  }

  void
  Cylinder::rotate(const Vector& v)
  {
    base_point = base_point.rotate(v);
    cap_point = cap_point.rotate(v);
    base_disc.rotate(v);
    cap_disc.rotate(v);
  }

  Vector
  Cylinder::get_max_extent() const
  {
    Vector max_base = base_disc.get_max_extent();
    Vector max_cap = cap_disc.get_max_extent();

    return Vector(max_base.get_x() > max_cap.get_x() ?
		  max_base.get_x() : max_cap.get_x(),
		  max_base.get_y() > max_cap.get_y() ?
		  max_base.get_y() : max_cap.get_y(),
		  max_base.get_z() > max_cap.get_z() ?
		  max_base.get_z() : max_cap.get_z());
  }

  Vector
  Cylinder::get_min_extent() const
  {
    Vector min_base = base_disc.get_min_extent();
    Vector min_cap = cap_disc.get_min_extent();

    return Vector(min_base.get_x() < min_cap.get_x() ?
		  min_base.get_x() : min_cap.get_x(),
		  min_base.get_y() < min_cap.get_y() ?
		  min_base.get_y() : min_cap.get_y(),
		  min_base.get_z() < min_cap.get_z() ?
		  min_base.get_z() : min_cap.get_z());
  }

  bool
  Cylinder::is_inside(const Vector& v) const
  {
    HitCalculation base_hit =
      base_disc.calculate_hit(Ray(v, base_point - cap_point));
    HitCalculation cap_hit =
      cap_disc.calculate_hit(Ray(v, cap_point - base_point));

    return base_hit.is_hit() && cap_hit.is_hit();
  }
  
}
