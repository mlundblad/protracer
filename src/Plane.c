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
|  File: Plane.c                                                          |
|                                                                         |
|  Implements the plane ADT                                               | 
|                                                                         |
\*************************************************************************/

#include <stdio.h>
#include <math.h>

#include "Pigment.h"
#include "Plane.h"
#include "Scalar.h"



#define Plane_d( pl ) (pl->d)


/**************************************************************************
  Function:  Plane_normal
  Arguments: Plane
  Result:    Vector
  Procedure: given a plane , return the normal vector
 *************************************************************************/

#define Plane_normal( p ) (p->normal)


/**************************************************************************
  Function:  Plane_point
  Arguments: Plane
  Result:    Vector
  Procedure: given a plane, return a point lieing
 *************************************************************************/

#define Plane_point( p ) (p->point)


/**************************************************************************
  Function:  Plane_pigment
  Arguments: Plane
  Result:    pigment
  Procedure: given a plane, return a point lieing
 *************************************************************************/

#define Plane_pigment( p ) (p->pigment)



Plane Plane_create( Vector normal, Vector point, 
                    Pigment pigment, scalar reflection, 
                    scalar diffuse )
{
    
    Plane p = malloc( sizeof( struct PlaneStruct ) );
   
    p->normal = Vector_normalize(normal);
    p->point = point;
    p->pigment = pigment;
    p->reflection = reflection;
    p->diffuse = diffuse;
    p->d = Vector_dotProduct( point, p->normal );

    return p;
}


HitData Plane_rayHitData( Plane pl, Ray ray )
{
    Vector rn;
    scalar vd;
    scalar v0;
    scalar t;

    /*d = Vector_dotProduct( Plane_point( pl ), Plane_normal( pl ) );*/
    vd = Vector_dotProduct( Plane_normal( pl ), Ray_direction( ray ) );
    
    if( vd != 0 )
    {
        v0 = Plane_d( pl ) - 
             Vector_dotProduct( Plane_normal( pl ), Ray_origin( ray ) );
        t = v0 / vd;
        
        if( t >= 0 )
        {
            /*ri = Vector_add( Ray_origin( ray ),
                              Vector_multiply( t,
                                               Ray_direction( ray ) ) );*/

             rn = vd < 0 ? Plane_normal( pl ) :
                 Vector_negate( Plane_normal( pl ) );


             return HitData_createHit( t, rn,
                                       Pigment_color( Plane_pigment( pl ) ) );
                                                 
        }
    }

    return HitData_createNoHit();
}





