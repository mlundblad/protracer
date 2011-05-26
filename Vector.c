/*************************************************************************\
|  File: Vector.c                                                         |
|                                                                         |
|  Implements functions for 3D vectors                                    |
|                                                                         |
\*************************************************************************/

#include <math.h>
#include <stdio.h>

#include "Vector.h"
#include "Error.h"
#include "Scalar.h"


/*Vector Vector_createFromCartesian( double x, double y, double z )
{
    Vector v;

    v.x = x;
    v.y = y;
    v.z = z;

    return v;
}*/

/*double Vector_dotProduct( Vector u, Vector v )
{
    return Vector_x(u) * Vector_x(v) + 
           Vector_y(u) * Vector_y(v) + 
           Vector_z(u) * Vector_z(v);
}*/

/*Vector Vector_crossProduct( Vector u, Vector v )
{
    return Vector_createFromCartesian( Vector_y(u) * Vector_z(v) - 
                                       Vector_z(u) * Vector_y(v),
                                       Vector_z(u) * Vector_x(v) - 
                                       Vector_x(u) * Vector_z(v),
                                       Vector_x(u) * Vector_y(v) - 
                                       Vector_y(u) * Vector_x(v));
}*/

/*Vector Vector_add( Vector u, Vector v )
{
   return Vector_createFromCartesian( Vector_x(u) + Vector_x(v),
                                      Vector_y(u) + Vector_y(v),
                                      Vector_z(u) + Vector_z(v));
}*/

/*Vector Vector_subtract( Vector u, Vector v )
{
   return Vector_createFromCartesian( Vector_x(u) - Vector_x(v),
                                      Vector_y(u) - Vector_y(v),
                                      Vector_z(u) - Vector_z(v));
}*/


/*Vector Vector_multiply( scalar s, Vector u )
{
   return Vector_createFromCartesian( s * Vector_x(u), 
				      s * Vector_y(u), 
				      s * Vector_z(u)); 
}*/

/*Vector Vector_negate( Vector vect )
{
    return( Vector_createFromCartesian( -Vector_x( vect ), 
					-Vector_y( vect ), 
					-Vector_z( vect ) ) );
}*/

/*scalar Vector_length( Vector u )
{
    return sqrt( Vector_dotProduct( u, u ) );
}*/

/*Vector Vector_normalize( Vector u )
{
    scalar len = Vector_length( u );

    if( len == 0.0 ) 
        Error_printErrorAndExit( "Can't normalize zero vector" );
        
    return Vector_multiply( 1 / len, u );
}*/

/*scalar Vector_x( Vector u )
{
    return u.x;
}*/

/*scalar Vector_y( Vector u )
{
    return u.y;
}*/

/*scalar Vector_z( Vector u )
{
    return u.z;
}*/


/*void Vector_print( Vector u)
{
    fprintf( stderr, "(%f %f %f)", u.x, u.y , u.z );
}*/
