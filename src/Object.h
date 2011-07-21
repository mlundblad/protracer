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
|  File: Object.h                                                         |
|                                                                         |
|  Defines an abstract datatype for objects                               |
|                                                                         |
\*************************************************************************/


#ifndef OBJECT_H
#define OBJECT_H

#ifdef __cplusplus
extern "C" {
#endif

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


#ifdef __cplusplus
};
#endif

#endif /* OBJECT_H */





