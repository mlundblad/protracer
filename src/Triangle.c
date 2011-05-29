/*************************************************************************\
|  File: Triangle.c                                                       |
|                                                                         |
|  Implements the triangle ADT                                            | 
|                                                                         |
\*************************************************************************/


#include "Triangle.h"
#include "Plane.h"
#include "Scalar.h"

#include <stdlib.h>






#define Triangle_spanPlane( tr ) (tr->spanPlane)


/**************************************************************************
  Function:  Triangle_origin
  Arguments: Triangle
  Result:    Vector
  Procedure: returns "origin" of a triangle (corner 0)
 *************************************************************************/

#define Triangle_origin( t ) (t->t0)


/**************************************************************************
  Function:  Triangle_vectorA
  Arguments: Triangle
  Result:    Vector
  Procedure: returns "first side" of a triangle
 *************************************************************************/

#define Triangle_vectorA( t ) (t->va)


/**************************************************************************
  Function:  Triangle_vectorB
  Arguments: Triangle
  Result:    Vector
  Procedure: returns "second side" of a triangle 
 *************************************************************************/

#define Triangle_vectorB( t ) (t->vb)


/**************************************************************************
  Function:  Triangle_pigment
  Arguments: Triangle
  Result:    Pigment
  Procedure: returns pigment of a triangle 
 *************************************************************************/

#define Triangle_pigment( t ) (t->pigment)


/**************************************************************************
  Function:  Triangle_AA
  Arguments: Triangle
  Result:    scalar
  Procedure: returns va dot va
 *************************************************************************/

#define Triangle_AA( t ) (t->AA)


/**************************************************************************
  Function:  Triangle_BB
  Arguments: Triangle
  Result:    scalar
  Procedure: returns vb dot vb
 *************************************************************************/

#define Triangle_BB( t ) (t->BB)


/**************************************************************************
  Function:  Triangle_AB
  Arguments: Triangle
  Result:    scalar
  Procedure: returns va
 *************************************************************************/

#define Triangle_AB( t ) (t->AB)


Triangle Triangle_createFromPoints( Vector c0, Vector c1, Vector c2, 
                                    Pigment pigment,
                                    scalar reflection,
                                    scalar diffuse)
{
    Triangle tr = malloc( sizeof( struct TriangleStruct ) );
    Vector   pn;

    tr->t0 = c0;
    tr->va = Vector_subtract(c1, c0);
    tr->vb = Vector_subtract(c2, c0);
    tr->pigment = pigment;
    tr->reflection = reflection;
    tr->diffuse = diffuse;

    pn = Vector_normalize( Vector_crossProduct( tr->va, tr->vb ) );

    tr->spanPlane = Plane_create( pn, c0, pigment, reflection, diffuse );
    tr->AA = Vector_dotProduct( tr->va, tr->va );   
    tr->BB = Vector_dotProduct( tr->vb, tr->vb );
    tr->AB = Vector_dotProduct( tr->va, tr->vb );

    return tr;
}

Triangle Triangle_createFromPointAndVectors( Vector t0, Vector va, Vector vb,
                                             Pigment pigment,
                                             scalar reflection,
                                             scalar diffuse)
{
    Triangle tr = malloc( sizeof( struct TriangleStruct ) );
    Vector   pn = Vector_normalize( Vector_crossProduct( va, vb ) );

    tr->t0 = t0;
    tr->va = va;
    tr->vb = vb;
    tr->pigment = pigment;
    tr->reflection = reflection;
    tr->diffuse = diffuse;
    tr->spanPlane = Plane_create( pn, t0, pigment, reflection, diffuse );
    tr->AA = Vector_dotProduct( va, va );
    tr->BB = Vector_dotProduct( vb, vb );
    tr->AB = Vector_dotProduct( va, vb );

    return tr;
}




HitData Triangle_rayHitData( Triangle tr, Ray ray )
{
    Vector q, ri;
    scalar u, v;
    HitData hd = Plane_rayHitData( Triangle_spanPlane( tr ),
                                   ray );
    Bitmap bitmap;
    

    if( HitData_hit( hd ) )
    {
        ri = Vector_add( Ray_origin( ray ),
                         Vector_multiply( 
                             HitData_distance( hd ),
                             Ray_direction( ray ) ) );
        

        q = Vector_subtract( ri, 
                             Triangle_origin( tr ) );
        
        u = (
            Triangle_BB( tr ) * Vector_dotProduct( q, 
                                                   Triangle_vectorA( tr ) )
            
            - 
            Triangle_AB( tr ) * Vector_dotProduct( q, 
                                                    Triangle_vectorB( tr ))
            
            )
            
            /
            (
                Triangle_AA( tr ) * Triangle_BB( tr ) -
                Triangle_AB( tr ) * Triangle_AB( tr )
            )
            ;
        
        if( 0 < u && u < 1 )
        {
            /*fprintf( stderr, "vector u is OK...");*/
            v = ( Vector_dotProduct( q, 
                                     Triangle_vectorB( tr ) ) 
                  -
                  u * Triangle_AB( tr )
                )     
                /
                
                Triangle_BB( tr );
             
            
            if( 0 < v && v < 1 && u+v <= 1 )
            {
                if( Pigment_type( Triangle_pigment( tr ) ) == PIGMENT_BITMAP )
                {
                    bitmap = Pigment_bitmap( Triangle_pigment( tr ) );
                    HitData_setColor( 
                        hd, 
                        Bitmap_colorAt( 
                            bitmap, 
                            (Bitmap_width( 
                                bitmap )-1) * u,
                            (Bitmap_height( 
                                bitmap )-1) * v ) );
                }

                return hd;
            }
        }
                  
    }

    return HitData_createNoHit();

}    

