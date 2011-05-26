/*************************************************************************\
|  File: Sphere.c                                                         |
|                                                                         |
|  Implemants the sphere ADT                                              | 
|                                                                         |
\*************************************************************************/

#include "Sphere.h"
#include "Scalar.h"
#include "HitData.h"

#include <math.h>
#include <stdlib.h>



/**************************************************************************
  Function:  Sphere_centre
  Arguments: Sphere
  Result:    Vector
  Procedure: given a sphere return it's centre
 *************************************************************************/

#define Sphere_centre( s ) (s->centre)



/**************************************************************************
  Function:  Sphere_pole
  Arguments: Sphere
  Result:    Vector
  Procedure: given a sphere return it's pole vector
 *************************************************************************/

#define Sphere_pole( s ) (s->pole)


/**************************************************************************
  Function:  Sphere_centre
  Arguments: Sphere
  Result:    Vector
  Procedure: given a sphere return it's equator vector
 *************************************************************************/

#define Sphere_equator( s ) (s->equator)


/**************************************************************************
  Function:  Sphere_radius
  Arguments: Sphere
  Result:    scalar
  Procedure: given a sphere return it's radius 
 *************************************************************************/

#define Sphere_radius( s ) (s->radius)


/**************************************************************************
  Function:  Sphere_radiusSqr
  Arguments: Sphere
  Result:    scalar
  Procedure: given a sphere return it's radius squared 
 *************************************************************************/

#define Sphere_radiusSqr( s ) (s->radiusSqr)



/**************************************************************************
  Function:  Sphere_pigment
  Arguments: Sphere
  Result:    Pigment
  Procedure: Returns the Pigment of the sphere.
 *************************************************************************/

#define Sphere_pigment( s ) (s->pigment)



Sphere Sphere_create( Vector centre, scalar radius, Vector pole, 
                      Vector equator, Pigment pigment, 
                      scalar reflection, scalar diffuse)
{
    Sphere s = malloc( sizeof( struct SphereStruct ) );
    
    s->centre = centre;
    s->radius = radius;
    s->radiusSqr = radius * radius;
    s->pole = Vector_normalize(pole); 
    s->equator = Vector_normalize(equator);
    s->pigment = pigment;
    s->reflection = reflection;
    s->diffuse = diffuse;

    return s;
}



static inline Color colorAt( Sphere s, Vector normal )
{
    scalar phi,temp;
    scalar theta;
    scalar u,v; /* Coordinates in % of bitmap. */
    Bitmap bitmap;
    /*Color retColor;*/

    if( Pigment_type( Sphere_pigment( s ) ) == PIGMENT_COLOR )
	return Pigment_color( Sphere_pigment( s ) );
    

    phi = acos( -Vector_dotProduct( 
        normal,
        Sphere_pole( s ) ) );
    v = 1 - phi / M_PI;
    
    if( v == 1.0 || v == 0.0 )
        u = 0.0;
    
    else
    {
        temp = Vector_dotProduct(
            normal,
            Sphere_equator( s ) ) / sin( phi );
        temp = temp > 1.0 ? 1.0 : temp;
	temp = temp < -1.0 ? -1.0 : temp;
        
        theta = acos( temp ) / (2*M_PI);
        
        u = Vector_dotProduct( 
            Vector_crossProduct( Sphere_equator( s ),
                                 Sphere_pole( s ) ),
            normal) > 0 ?
            theta : 1 - theta;
        
    }
    
    
    
    /* Ok, u and v are the % coordinates into the bitmap.
       Lets return the correct color for the given point. */
    bitmap = Pigment_bitmap( Sphere_pigment( s ) );
    
    /*fprintf( stderr, "w: %d h: %d u: %f v: %f\n", Bitmap_width( bitmap ),
      Bitmap_height( bitmap ),
      u, v);*/
    
    return Bitmap_colorAt( bitmap, 
                           (Bitmap_width( bitmap ) - 1) * u,
                           (Bitmap_height( bitmap ) - 1) * v );
    

}
 

HitData Sphere_rayHitData( Sphere s, Ray ray )
{
    /* Vector  oc;*/
    scalar  l2oc;
    scalar  tca;
    scalar  t2hc;
    scalar  distance;
    
    /*Vector  ri;
    Vector  rn;*/
    Vector  tempVect;
    
    /*oc = Vector_subtract( Sphere_centre( s ),
                          Ray_origin( ray ));*/
    l2oc = Vector_dotProduct( Vector_subtract( Sphere_centre( s ),
                                               Ray_origin( ray )),
                              Vector_subtract( Sphere_centre( s ),
                                               Ray_origin( ray ) )
                                  );
    tca = Vector_dotProduct( Vector_subtract( Sphere_centre( s ),
                                              Ray_origin( ray ) ), 
                             Ray_direction( ray ) );
    
    
    t2hc = Sphere_radiusSqr( s ) - l2oc + tca * tca;
    
 
    if( !( l2oc < Sphere_radiusSqr( s ) ) )
    {
	if( tca + SPHERE_EPS >= 0 && t2hc >= 0 )
	{
	    distance = tca - sqrt( t2hc );
	    
	    tempVect = Vector_add( Ray_origin( ray ),
				   Vector_multiply( distance,
						    Ray_direction( ray ) ) );
	    
	    tempVect = Vector_multiply( 1.0 / Sphere_radius( s ),
					Vector_subtract( tempVect,
							 Sphere_centre( s ) ) );
	    
	    return HitData_createHit( distance,
				      tempVect, colorAt( s, tempVect ) );

	}
	else
	    return HitData_createNoHit();
    }
    
    distance = tca + sqrt( t2hc );
    
    tempVect = Vector_add( Ray_origin( ray ),
			   Vector_multiply( distance,
					    Ray_direction( ray ) ) );
    
    tempVect = Vector_multiply( -1.0 / Sphere_radius( s ),
				Vector_subtract( tempVect,
						 Sphere_centre( s ) ) );
    
    
    return HitData_createHit( distance,
			      tempVect, colorAt( s, tempVect ) );
}










