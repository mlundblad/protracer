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
|  File: Vector.h                                                         |
|                                                                         |
|  Defines an abstract datatype  for 3D vectors                           |
|  uses stack allocation                                                  |
\*************************************************************************/

#ifndef VECTOR_H
#define VECTOR_H

#include "Scalar.h"

#include <stdio.h>
#include <math.h>
#include "Error.h"

#ifdef __cplusplus
extern "C" {
#endif

struct _Vector
{
    scalar x;
    scalar y;
    scalar z;
};

typedef struct _Vector Vector;

/**************************************************************************
 Function:  Vector_createFromCartesian          
 Arguments: 3 scalars         
 Result:    vector            
 Procedure: creates a vector from 3 cartesian components 
**************************************************************************/

#define Vector_createFromCartesian( x, y, z ) ((Vector){x, y, z })

/*static inline Vector Vector_createFromCartesian( scalar x, scalar y, scalar z )
{
    Vector v;

    Vector_x( v ) = x;
    Vector_y( v ) = y;
    Vector_z( v ) = z;

    return v;
}*/


/**************************************************************************
 Function:  Vector_getCartesianX      
 Arguments: Vector            
 Result:    scalar   
 Procedure: returns the cartesian x coordinate of a vector
 *************************************************************************/

#define Vector_x( u ) ( u.x )

/*static inline scalar Vector_x( Vector u )
{
    return Vector_x( u );
}*/

/**************************************************************************
 Function:  Vector_getCartesianY   
 Arguments: Vector            
 Result:    scalar   
 Procedure: returns the cartesian y coordinate of a vector
 *************************************************************************/

#define Vector_y( u ) ( u.y )

/*static inline scalar Vector_y( Vector u )
{
    return Vector_y( u );
}*/

/**************************************************************************
 Function:  Vector_getCartesianZ   
 Arguments: Vector            
 Result:    scalar   
 Procedure: returns the cartesian z coordinate of a vector
 *************************************************************************/

#define Vector_z( u ) ( u.z )

/*static inline scalar Vector_z( Vector u )
{
    return Vector_z( u );
}*/


/**************************************************************************
  Function:  Vector_dotProduct         
  Arguments: 2 vectors         
  Result:    scalar            
  Procedure: computes the dot product
 *************************************************************************/

#define Vector_dotProduct( u, v ) ( Vector_x( u ) * Vector_x( v ) + \
                                    Vector_y( u ) * Vector_y( v ) + \
                                    Vector_z( u ) * Vector_z( v ) ) 

/*static inline scalar Vector_dotProduct(Vector u, Vector v)
{
    return Vector_x( u )*Vector_x( v ) + 
           Vector_y( u )*Vector_y( v ) + 
           Vector_z( u )*Vector_z( v );
}*/


/**************************************************************************
  Function:  Vector_crossProduct       
  Arguments: 2 Vectors         
  Result:    Vector            
  Procedure: computes the cross product
 *************************************************************************/

#define Vector_crossProduct( u, v ) ((Vector){ \
    Vector_y( u )*Vector_z( v ) - Vector_z( u )*Vector_y( v ), \
    Vector_z( u )*Vector_x( v ) - Vector_x( u )*Vector_z( v ), \
    Vector_x( u )*Vector_y( v ) - Vector_y( u )*Vector_x( v ) } )

/*static inline Vector Vector_crossProduct(Vector u, Vector v)
{
    Vector vect;
    
    vect.x = Vector_y( u )*Vector_z( v ) - Vector_z( u )*Vector_y( v );
    vect.y = Vector_z( u )*Vector_x( v ) - Vector_x( u )*Vector_z( v );
    vect.z = Vector_x( u )*Vector_y( v ) - Vector_y( u )*Vector_x( v );

    return vect;
}*/


/**************************************************************************
  Function:  Vector_negate       
  Arguments: Vector         
  Result:    Vector            
  Procedure: computes the negation.
 *************************************************************************/

#define Vector_negate( v ) ((Vector){-Vector_x( v ), -Vector_y( v ), -Vector_z( v )})

/*static inline Vector Vector_negate( Vector vect )
{
    Vector v;
    
    Vector_x( v ) = -vect.x;
    Vector_y( v ) = -vect.y;
    Vector_z( v ) = -vect.z;

    return v;
}*/


/**************************************************************************
  Function:  Vector_add             
  Arguments: 2 Vectors         
  Result:    Vector          
  Procedure: computes the sum of 2 Vectors
 *************************************************************************/

#define Vector_add( u, v ) ((Vector){Vector_x( u )+Vector_x( v ), \
                                     Vector_y( u )+Vector_y( v ), \
                                     Vector_z( u )+Vector_z( v )})

/*static inline Vector Vector_add(Vector u, Vector v)
{
    Vector vect;
    

    vect.x = Vector_x( u ) + Vector_x( v );
    vect.y = Vector_y( u ) + Vector_y( v );
    vect.z = Vector_z( u ) + Vector_z( v );

    return vect;
}*/

/**************************************************************************
  Function:  Vector_subtract             
  Arguments: 2 Vectors         
  Result:    Vector          
  Procedure: computes the difference of 2 Vectors
 *************************************************************************/

#define Vector_subtract( u, v ) ((Vector){Vector_x( u )-Vector_x( v ), \
                                          Vector_y( u )-Vector_y( v ), \
                                          Vector_z( u )-Vector_z( v )})


/**************************************************************************
  Function:  Vector_multiply            
  Arguments: scalar, Vector
  Result:    Vector            
  Procedure: computes multiplication of a vector and a scalar
 *************************************************************************/

#define Vector_multiply( s, u ) ((Vector) { s*Vector_x( u ), \
                                            s*Vector_y( u ), \
                                            s*Vector_z( u ) })


/**************************************************************************
  Function:  Vector_length          
  Arguments: Vector            
  Result:    scalar            
  Procedure: computes the length of a Vector
 *************************************************************************/

#define Vector_length( u ) (sqrt( Vector_dotProduct( u,u ) ) )


/**************************************************************************
 Function:  Vector_normalize       
 Arguments: Vector            
 Result:    Vector            
 Procedure: computes the normalization of a Vector
 *************************************************************************/

static inline Vector Vector_normalize(Vector u)
{
  scalar len = Vector_length( u );

    if( len == 0.0 )
	Error_printErrorAndExit( "0" ); /* Cant normalize zero vector */

    return Vector_multiply( 1 / len , u );
}

#ifdef __cplusplus
}
#endif

#endif /* VECTOR_H */
