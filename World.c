/*************************************************************************\
|  File: World.c                                                          |
|                                                                         |
|  Implements the ADT world                                               |
\*************************************************************************/

#include "World.h"
#include "Ray.h"
#include "Scalar.h"
#include "HitData.h"

#include <math.h>


/**************************************************************************
  Function:  World_shade
  Arguments: Vector, Vector, Vector
  Result:    scalar
  Procedure: given light origin, hit point and hit normal,
             give shade factor
 *************************************************************************/

static scalar World_shade( Vector l0, Vector ri, Vector rn )
{
    /*Vector s0;
      Vector sd;*/
    
    ri = Vector_add( ri,
                     Vector_multiply( EPS,
                                      rn ) );
    l0 = Vector_normalize( Vector_subtract( l0, ri ) );

    return fabs( Vector_dotProduct( rn, l0 ) );
}


/**************************************************************************
  Function:  World_camera
  Arguments: World
  Result:    Camera
  Procedure: returns the camera of a world
 *************************************************************************/

#define World_camera( w ) (w->camera)


/**************************************************************************
  Function:  World_objects
  Arguments: World
  Result:    ObjectArray
  Procedure: returns the objects in a world
 *************************************************************************/

#define World_objects( w ) (w->objects)


/**************************************************************************
  Function:  World_background
  Arguments: World
  Result:    Color
  Procedure: returns the background colorof a world
 *************************************************************************/

#define World_background( w ) (w->background)


/*************************************************************************
  Function:  World_lights
  Arguments: World
  Result:    LightArray
  Procedure: returns the ligts in a world
 *************************************************************************/

#define World_lights( w ) (w->lights)


/**************************************************************************
  Function:  World_colorAtHitPoint
  Arguments: World, int, int, int
  Result:    Color
  Procedure: returns the color of the spec pixel given coords and
             reflection depth
 *************************************************************************/

Color World_colorAtHitPoint( World world, int x, int y, Ray ray,
                                          int reflDepth, 
                                          bool noShadowNoReflection )
{
    Vector      hitPoint;
  
    int         numItems = ObjectArray_numObjects( World_objects( world ) );
    int         numLights = LightArray_numLights( World_lights( world ) );

    int         i,j;
    int         index = 0;
    /*scalar      distance = HUGE_VAL;*/
    scalar      leastDistance = HUGE_VAL;

    scalar      shade = 0.0;
    
    Ray         reflRay;
    Ray         lightRay;

    bool        isLit;

    Color       col;

    HitData     hd;
    HitData     nearestHit;
  
    for( i = 0 ; i < numItems ; i++)
    {
        /*fprintf( stderr, "About to check #%d for hit\n", i );*/
        
        hd = Object_rayHitData( ObjectArray_objectAt( World_objects( world ),
                                                      i ), ray );

        if( HitData_hit( hd ) )
        {
            if( HitData_distance( hd ) < leastDistance )
            {
                leastDistance = HitData_distance( hd );
                nearestHit = hd;
                index = i;
            }
        }
                

    }

    if( leastDistance == HUGE_VAL )
    { 
        return World_background( world );
    }
   
  

    /* leastDistance is the distance to the nearest object hit */
    hitPoint = Vector_add( Ray_origin( ray ),
                           Vector_multiply(
                               leastDistance,
                               Ray_direction( ray ) ) );
   

    /*hitNormal = Object_hitPointNormal( ObjectArray_objectAt(
                                          World_objects( world ), 
                                          index ), 
                                       ray );*/
    
    if( noShadowNoReflection ) /* Simulate the camera as a light source */
    {  
                /*fprintf( stderr, "%d %f\n", index,
                 World_shade( Ray_origin( ray ), hitPoint, hitNormal ) );*/
        
        return
             Color_shade(  
                HitData_color( nearestHit ),
                World_shade( Ray_origin( ray ), hitPoint,
                             HitData_normal( nearestHit) ) );
           
    }
    else
    {
        
        /* iterate over light sources */
        for( i = 0 ; i < numLights ; i++ )
        {
            /* create a ray from the hit point to a light */
            lightRay = Ray_create( Vector_add( hitPoint,
                                               Vector_multiply(
                                                   EPS,
                                                   HitData_normal( nearestHit ) ) ),
                                   Vector_subtract(
                                       Light_position(LightArray_lightAt(
                                           World_lights( world ), i ) ),
                                       Vector_add( 
                                           hitPoint,
                                           Vector_multiply(
                                               EPS,
                                               HitData_normal( nearestHit ) ) ) ) );
                                                          
            
            isLit = TRUE;
            j = 0;
            while( ( j < numItems ) && isLit )
            {
                
                hd = Object_rayHitData( ObjectArray_objectAt(
                    World_objects( world ), j ), lightRay );

                if( HitData_hit( hd ) )
                    
                {
                    if( HitData_distance( hd ) < Vector_length( 
                        Vector_subtract( 
                            Light_position(LightArray_lightAt(
                                World_lights( world ), i ) ),
                            hitPoint ) ) )
                    {
                        isLit = FALSE;
                    }
                }
                j++;
            }

            
            /*if(!isLit) fprintf( stderr, "dark\n" );
            else fprintf( stderr, "light on me\n" );*/
            
            if( isLit )
            {
                /*fprintf( stderr, "a" );*/
                shade += 
                    World_shade( 
                        Light_position( 
                            LightArray_lightAt(
                                World_lights( world ), i ) ),
                        hitPoint, 
                        HitData_normal( nearestHit ) );
            }
            
        }
        
        
        /*if( shade > 0.0 )
        {
            fprintf( stderr, "Pixel: %d %d is lit at refl.depth %d\n",
                     x,y,reflDepth );
        }*/
        /*fprintf( stderr, "shade: %f\n", shade );*/

        
        /* Base case: don't take reflection into acount, 
           but shade the accumulated light from light sources */
        if( reflDepth == 0 )
        {
            return
                Color_shade( HitData_color( nearestHit ),
                             shade *
                             Object_diffuse(
                                 ObjectArray_objectAt(
                                     World_objects( world ), index ) ) );
        }
        else
        {

            /* calculate reflected ray */
            /* move EPS in the normal direction, to avoid rounding errors */
            reflRay = Ray_create( Vector_add( hitPoint,
                                              Vector_multiply( 
                                                  EPS,
                                                  HitData_normal(
                                                      nearestHit ) ) ),
                                  Vector_subtract(
                                      Ray_direction( ray ),
                                      Vector_multiply( 
                                          2 *
                                          Vector_dotProduct(
                                              HitData_normal( nearestHit ),
                                              Ray_direction( ray ) ) ,
                                          HitData_normal( nearestHit ) ) ) );

            reflDepth--;
            col = World_colorAtHitPoint(
                world, x, y, reflRay, reflDepth, noShadowNoReflection );

            
                                                     
            return
                Color_combine( 
                    Color_shade(
                        col,
                        Object_reflection(
                            ObjectArray_objectAt(
                                World_objects( world ), 
                                index ) ) ),
                    
                    Color_shade( 
                        HitData_color( nearestHit ),
                        shade *
                        Object_diffuse(
                            ObjectArray_objectAt(
                                World_objects( world ), 
                                index ) ) ) );
               
            
        }
       
    }
}





World World_create( ObjectList objects, LightList lights, 
                    Camera cam, Color background )
{
    Vector c;
    World  world = malloc( sizeof( struct WorldStruct ) );
       
    world->camera =     cam;
    world->lights =     LightArray_createFromList( lights );
    world->objects =    ObjectArray_createFromList( objects );
    world->background = background;

    c = Vector_normalize( Vector_subtract(
                                 Camera_lookAt( World_camera( world ) ),
                                 Camera_location( World_camera( world ) ) ) );
 
    world->cRight = Vector_normalize( Vector_crossProduct( 
        Camera_upVector( World_camera( world ) ), c ) );
    world->cDown = Vector_normalize( Vector_crossProduct( world->cRight, 
                                                          c ) );

    
    world->cCorner = Vector_add( 
        Camera_location( cam ), 
        Vector_subtract( 
            Vector_multiply( 
                Camera_zoom( cam ), 
                c ),
            Vector_add( 
                Vector_multiply( Camera_worldWidth( cam ) / 2, 
                                 world->cRight ),
                Vector_multiply( Camera_worldHeight( cam ) / 2,  
                                 world->cDown ) ) ) );
    
    return world;
}

void World_free( World world )
{
    LightArray_destroy( world->lights );
    ObjectArray_destroy( world->objects );
    free( world );
}
