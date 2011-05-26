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
