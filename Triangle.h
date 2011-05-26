/*************************************************************************\
|  File: Triangle.h                                                       |
|                                                                         |
|  Defines an abstract datatype for triangles                             |
|  uses heap allocation                                                   |
\*************************************************************************/

#ifndef _TRIANGLE_H
#define _TRIANGLE_H

#include "Scalar.h"

#include "Vector.h"
#include "Pigment.h"
#include "Ray.h"
#include "Plane.h"

struct TriangleStruct
{
    Vector  t0;
    Vector  va;
    Vector  vb;
    Pigment pigment;
    scalar  reflection;
    scalar  diffuse;
    Plane   spanPlane;
    scalar  AA;        /* va dot vb */
    scalar  BB;        /* vb dot vb */
    scalar  AB;        /* va dot vb */
};

typedef struct TriangleStruct* Triangle;



/**************************************************************************
  Function:  Triangle_createFromPoints
  Arguments: 3 vectors
  Result:    Triangle
  Procedure: creates a trianlge from 3 vectors repr. the 3 corners
 *************************************************************************/

Triangle Triangle_createFromPoints( Vector c0, Vector c1, Vector c2, 
                                    Pigment pigment,
                                    scalar reflection,
                                    scalar diffuse);

/**************************************************************************
  Function:  Triangle_createFromPointAndVectors
  Arguments: 3 vectors
  Result:    Triangle
  Procedure: creates a triangle from 3 vecors repr. one corner and 2 "legs"
 *************************************************************************/

Triangle Triangle_createFromPointAndVectors( Vector t0, Vector va, Vector vb, 
                                             Pigment pigment,
                                             scalar reflection,
                                             scalar diffuse);


/**************************************************************************
  Function:  Triangle_rayHitData
  Arguments: Triangle, Ray
  Result:    Hitdata
  Procedure: returns HitData for ray
 *************************************************************************/

HitData Triangle_rayHitData( Triangle tr, Ray ray );


/**************************************************************************
  Function:  Triangle_rayHitPointDistance
  Arguments: Triangle, Vector, Vector
  Result:    scalar
  Procedure: given a triangle and ray, returns hitpoint distance, undefined
             if ray doesn't hit triangle
 *************************************************************************/
/*
#define Triangle_rayHitPointDistance( tr, ray ) \
(Plane_rayHitPointDistance( Triangle_spanPlane( tr ), (ray) ) ) */

/**************************************************************************
  Function:  Triangle_rayColorAtHitPoint
  Arguments: Triangle, Ray
  Result:    Color
  Procedure: given a triangle and ray give color at hipoint, undefined if ray
             doesn't hit triangle
 *************************************************************************/

/*Color Triangle_rayColorAtHitPoint( Triangle t, Ray ray );*/


/**************************************************************************
  Function:  Triangle_hitPointNormal
  Arguments: Triangle, Ray
  Result:    Vector
  Procedure: given a triangle and ray give normal vector at hipoint.
 *************************************************************************/

/*#define Triangle_hitPointNormal( tr, ray ) \
(Plane_hitPointNormal( Triangle_spanPlane( tr ), (ray) ))*/



/**************************************************************************
  Function:  Triangle_isRayHitting
  Arguments: Triangle, Vector, Vector
  Result:    bool
  Procedure: given a triangle and a ray, returns TRUE if ray is hittnig,
             otherwise return FALSE
 *************************************************************************/

/*bool Triangle_isRayHitting( Triangle tr , Ray ray );*/


/**************************************************************************
  Function:  Triangle_diffuse
  Arguments: Triangle
  Result:    scalar
  Procedure: returns diffuse
 *************************************************************************/

#define Triangle_diffuse( t ) (t->diffuse)


/**************************************************************************
  Function:  Triangle_reflection
  Arguments: Triangle
  Result:    scalar
  Procedure: returns reflection
 *************************************************************************/

#define Triangle_reflection( t ) (t->reflection)

#endif /* _TRIANGLE_H */

