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
|  File: Sphere.h                                                         |
|                                                                         |
|  Defines an abstract datatype for spheres                               |
|  uses heap allocation bje
                                                  |
\*************************************************************************/

#ifndef SPHERE_H
#define SPHERE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Vector.h"
#include "Pigment.h"
#include "Ray.h"
#include "Scalar.h"
#include "HitData.h"

#define SPHERE_EPS (double)0.001

/* pole vector defaults */
#define POLE_DEFAULT_X (scalar)0.0
#define POLE_DEFAULT_Y (scalar)1.0
#define POLE_DEFAULT_Z (scalar)0.0

/* equator vector defaults */
#define EQUATOR_DEFAULT_X (scalar)1.0
#define EQUATOR_DEFAULT_Y (scalar)0.0
#define EQUATOR_DEFAULT_Z (scalar)0.0



struct SphereStruct
{
    Vector  centre;
    scalar  radius;
    scalar  radiusSqr;
    Vector  pole;
    Vector  equator;
    Pigment pigment;
    scalar  reflection;
    scalar  diffuse;
};

typedef struct SphereStruct* Sphere;

/**************************************************************************
  Function:  Sphere_create
  Arguments: vector, scalar, 2 Vectors, Pigment, 2 scalars
  Result:    Sphere
  Procedure: creates a sphere from centre vector and radius
 *************************************************************************/

Sphere Sphere_create( Vector centre, scalar radius, Vector pole, Vector equator,
                      Pigment pigment, scalar reflection, scalar diffuse);





/**************************************************************************
  Function:  Sphere_rayHitData
  Arguments: Sphere, Ray
  Result:    Hitdata
  Procedure: returns HitData for ray
 *************************************************************************/

HitData Sphere_rayHitData( Sphere s, Ray ray );



/**************************************************************************
  Function:  Sphere_diffuse
  Arguments: Sphere
  Result:    scalar
  Procedure: returns diffuse
 *************************************************************************/

#define Sphere_diffuse( s ) (s->diffuse)


/**************************************************************************
  Function:  Sphere_reflection
  Arguments: Sphere
  Result:    scalar
  Procedure: returns reflection
 *************************************************************************/

#define Sphere_reflection( s ) (s->reflection)

#ifdef __cplusplus
};
#endif

#endif /* SPHERE_H */

