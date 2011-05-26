/*************************************************************************\
|  File: Plane.h                                                          |
|                                                                         |
|  Defines an abstract datatype for planes                                |
|  uses heap allocation                                                   |
\*************************************************************************/

#ifndef PLANE_H
#define PLANE_H

#include "Pigment.h"
#include "Vector.h"
#include "Ray.h"
#include "Scalar.h"
#include "HitData.h"

#include <stdlib.h> 

#define PLANE_EPS (scalar)0.001

struct PlaneStruct
{
    Vector  normal;
    Vector  point;
    Pigment pigment;
    scalar  reflection;
    scalar  diffuse;
    scalar  d;
};

typedef struct PlaneStruct* Plane;

/**************************************************************************
  Function:  Plane_create
  Arguments: 2 vectors, Pigment, 2 scalars
  Result:    Plane
  Procedure: creates a plane from a normal vector and a vector spec. a point
             in the plane, pigemnt, reflection, diffuse,
             the normal vector is normalized
 *************************************************************************/

Plane Plane_create( Vector normal, Vector point, 
                    Pigment pigment, scalar reflection, 
                    scalar diffuse );



/**************************************************************************
  Function:  Plane_rayHitData
  Arguments: Plane, Ray
  Result:    Hitdata
  Procedure: returns HitData for ray
 *************************************************************************/

HitData Plane_rayHitData( Plane pl, Ray ray );



/**************************************************************************
  Function:  Plane_rayHitPointDistance
  Arguments: Plane, Ray
  Result:    scalar
  Procedure: given a plane, and a ray return distance
             to hit point
 *************************************************************************/

/*scalar Plane_rayHitPointDistance( Plane pl, Ray ray );*/


/**************************************************************************
  Function:  Plane_rayColorAtHitPoint
  Arguments: Plane, Ray
  Result:    Color
  Procedure: given a plane and a ray return color at hitpoint, undefined
             if ray doesn't hit the plane
 *************************************************************************/

/*Color Plane_rayColorAtHitPoint( Plane pl, Ray ray );*/


/**************************************************************************
  Function:  Plane_hitPointNormal( Plane pl, Ray ray )
  Arguments: Plane, Ray
  Result:    Vector
  Procedure: given a plane and a ray return normal vector at hitpoint
 *************************************************************************/

/*Vector Plane_hitPointNormal( Plane pl, Ray ray );*/




/**************************************************************************
  Function:  Plane_isRayHitting
  Arguments: Plane, Vector, Vector
  Result:    bool
  Procedure: given a plane, and a ray origin and ray direct. returns TRUE
             if ray hits plane, otherwaise FALSE
 *************************************************************************/

/*bool Plane_isRayHitting( Plane pl, Ray ray );*/


/**************************************************************************
  Function:  Plane_diffuse
  Arguments: Plane
  Result:    scalar
  Procedure: returns diffuse
 *************************************************************************/

#define Plane_diffuse( p ) (p->diffuse)



/**************************************************************************
  Function:  Plane_reflection
  Arguments: Plane
  Result:    scalar
  Procedure: returns reflection
 *************************************************************************/

#define Plane_reflection( p ) (p->reflection)


#endif /* PLANE_H */
