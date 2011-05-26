/*************************************************************************\
|  File: Object.h                                                         |
|                                                                         |
|  Defines an abstract datatype for objects                               |
|                                                                         |
\*************************************************************************/


#ifndef OBJECT_H
#define OBJECT_H

#include "Sphere.h"
#include "Triangle.h"
#include "Plane.h"
#include "Camera.h"
#include "Light.h"
#include "Scalar.h"
#include "HitData.h"
#include "Ray.h"


typedef enum {OBJECT_SPHERE, OBJECT_TRIANGLE, OBJECT_PLANE} 
ObjectType;

struct ObjectStruct
{
    ObjectType type;
    HitData    (*hitData)();
    scalar     (*reflection)();
    scalar     (*diffuse)();
    union
    {
        Sphere   sphere;
        Triangle triangle;
        Plane    plane;
    } object;
};

typedef struct ObjectStruct* Object;








/**************************************************************************
  Function:  Object_createSphere
  Arguments: Sphere
  Result:    Object
  Procedure: creates an object which is a sphere
 *************************************************************************/

Object Object_createSphere( Sphere s );


/**************************************************************************
  Function:  Object_createTriangle
  Arguments: Triangle
  Result:    Object
  Procedure: creates an object which is a triangle
 *************************************************************************/

Object Object_createTriangle( Triangle t );


/**************************************************************************
  Function:  Object_createPlane
  Arguments: Plane
  Result:    Object
  Procedure: creates an object which is a sphere
 *************************************************************************/

Object Object_createPlane( Plane p );


/**************************************************************************
  Function:  Object_rayHitData
  Arguments: Object, Ray
  Result:    Hitdata
  Procedure: returns HitData for ray
 *************************************************************************/

#define Object_rayHitData( o, ray ) ((*o->hitData)(o,ray))



/**************************************************************************
  Function:  Object_diffuse
  Arguments: Object
  Result:    scalar
  Procedure: returns diffuse of object
 *************************************************************************/

#define Object_diffuse( o ) ((*o->diffuse)(o))


/**************************************************************************
  Function:  Object_reflection
  Arguments: Object
  Result:    scalar
  Procedure: returns reflection of object
 *************************************************************************/

#define Object_reflection( o ) ((*o->reflection)(o))






#endif /* OBJECT_H */





