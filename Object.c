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
|  File: Object.c                                                         |
|                                                                         |
|  Implements the ADT for objects                                         |
|                                                                         |
\*************************************************************************/


#include "Object.h"
#include "Error.h"
#include "Scalar.h"


#include <stdlib.h>


/* these are static functions used by object to calculate
   hitdata */



/**************************************************************************
  Function:  Object_type
  Arguments: Object
  Result:    ObjectType
  Procedure: returns the type of an object
 *************************************************************************/

#define Object_type( o ) (o->type)

/**************************************************************************
  Function:  Object_sphere
  Arguments: Object
  Result:    Sphere
  Procedure: returns a sphere object, fails if the object is not a sphere
 *************************************************************************/

#define Object_sphere( o ) (o->object.sphere)


/**************************************************************************
  Function:  Object_triangle
  Arguments: Object
  Result:    Triangle
  Procedure: returns a triangle object, fails if the object is not a triangle
 *************************************************************************/

#define Object_triangle( o ) (o->object.triangle)


/**************************************************************************
  Function:  Object_plane
  Arguments: Object
  Result:    plane
  Procedure: returns a plane object, fails if the object is not a plane
 *************************************************************************/

#define Object_plane( o ) (o->object.plane)


static HitData Object_sphereHitData( Object o, Ray ray )
{
    return Sphere_rayHitData( Object_sphere( o ), ray );
}

static HitData Object_planeHitData( Object o, Ray ray )
{
    return Plane_rayHitData( Object_plane( o ), ray );
}

static HitData Object_triangleHitData( Object o, Ray ray )
{
    return Triangle_rayHitData( Object_triangle( o ), ray );
}



static scalar Object_sphereReflection( Object o )
{
    return Sphere_reflection( Object_sphere( o ) );
}

static scalar Object_planeReflection( Object o )
{
    return Plane_reflection( Object_plane( o ) );
}

static scalar Object_triangleReflection( Object o )
{
    return Triangle_reflection( Object_triangle( o ) );
}


static scalar Object_sphereDiffuse( Object o )
{
    return Sphere_diffuse( Object_sphere( o ) );
}

static scalar Object_planeDiffuse( Object o )
{
    return Plane_diffuse( Object_plane( o ) );
}

static scalar Object_triangleDiffuse( Object o )
{
    return Triangle_diffuse( Object_triangle( o ) );
}




Object Object_createSphere( Sphere s )
{
    Object o = malloc( sizeof( struct ObjectStruct ) );
    
    o->type = OBJECT_SPHERE;
    o->hitData = &Object_sphereHitData;
    o->reflection = &Object_sphereReflection;
    o->diffuse = &Object_sphereDiffuse;
    o->object.sphere = s;
    return o;
}

Object Object_createTriangle( Triangle t )
{
    Object o = malloc( sizeof( struct ObjectStruct ) );

    o->type = OBJECT_TRIANGLE;
    o->hitData = &Object_triangleHitData;
    o->reflection = &Object_triangleReflection;
    o->diffuse = &Object_triangleDiffuse;
    o->object.triangle = t;
    return o;
}

Object Object_createPlane( Plane p )
{
    Object o = malloc( sizeof( struct ObjectStruct ) );

    o->type = OBJECT_PLANE;
    o->hitData = &Object_planeHitData;
    o->reflection = &Object_planeReflection;
    o->diffuse = &Object_planeDiffuse;
    o->object.plane = p;
    return o;
}

