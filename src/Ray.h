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


/*************************************************************************\
| File: Ray.h                                                             |
|                                                                         |
| This file defines the ADT for the ray tracing module                    |
|                                                                         |
\*************************************************************************/

#ifndef _RAY_H
#define _RAY_H

#include "Vector.h"

typedef struct
{
    Vector origin;
    Vector direction;
} Ray;


/**************************************************************************
  Function:  Ray_create          
  Arguments: Vector, Vector
  Result:    Ray     
  Procedure: returns a ray given origin and direction
 *************************************************************************/

static inline Ray Ray_create( Vector origin, Vector direction )
{
    return (Ray) { origin, Vector_normalize( direction ) };
}


/**************************************************************************
  Function:  Ray_origin        
  Arguments: Ray
  Result:    Vector     
  Procedure: returns the origin of a ray
 *************************************************************************/

#define Ray_origin( ray ) (ray.origin)


/**************************************************************************
  Function:  Ray_direction            
  Arguments: Ray
  Result:    Vector     
  Procedure: returns the direction of a ray
 *************************************************************************/

#define Ray_direction( ray ) (ray.direction)

#endif
