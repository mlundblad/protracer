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
|  File: World.h                                                          |
|                                                                         |
|  Defines an ADT for a world representation                              |
|  uses stack allocation                                                  |
\*************************************************************************/

#ifndef WORLD_H
#define WORLD_H

#include "ObjectList.h"
#include "LightList.h"
#include "ObjectArray.h"
#include "LightArray.h"
#include "Color.h"
#include "Scalar.h"

#define EPS (scalar)0.001

#define DEFAULT_BACKGROUND (Color_createFromRGB(0,0,0))

struct WorldStruct
{
    ObjectArray objects;
    LightArray  lights;
    Camera      camera;
    Color       background;
    Vector      cCorner;
    Vector      cRight;
    Vector      cDown;
    Vector      c;
};

typedef struct WorldStruct* World;

/**************************************************************************
  Function:  World_create
  Arguments: ObjectList, Camera,Color
  Result:    World
  Procedure: creates a world from a list of objects...
 *************************************************************************/

World World_create( ObjectList objects, LightList lights, 
                    Camera cam, Color background );


/**************************************************************************
  Function:  World_free
  Arguments: World
  Result:    void
  Procedure: frees the object arrays in a world
 *************************************************************************/

void World_free( World w );


#define World_cCorner( w ) (w->cCorner)

#define World_cRight( w ) (w->cRight)

#define World_cDown( w ) (w->cDown)


/**************************************************************************
  Function:  World_colorOfPixel
  Arguments: World, int, int, int, bool
  Result:    Color
  Procedure: returns the color of the spec pixel given coords and
             reflection depth
 *************************************************************************/

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
                                          bool noShadowNoReflection );

static inline Color World_colorOfPixel( World world, int x, int y, int reflDepth,
                          bool noShadowNoReflection )
{
    Ray ray;
    Vector rayDirection;
  
    rayDirection = 
        Vector_normalize( 
            Vector_subtract( 
                Vector_add( 
                    Vector_add( 
                        Vector_multiply( ( Camera_worldWidth( 
                                                    World_camera( world ) ) /  
                                           Camera_pixelWidth( 
                                               World_camera( world ) ) ) 
                                         * x, 
                                         World_cRight( world ) ),
                        Vector_multiply( ( Camera_worldHeight( 
                                                  World_camera( world ) ) / 
                                           Camera_pixelHeight( 
                                               World_camera( world ) ) ) * y, 
                                         World_cDown( world ) ) ),
                    World_cCorner( world ) ), 
                Camera_location( World_camera( world ) ) ) );


   
    
    ray = Ray_create( Camera_location( World_camera( world ) ), 
                      rayDirection );

    return World_colorAtHitPoint( world, x, y, ray, reflDepth,
                                                     noShadowNoReflection );
}



#endif /* WORLD_H */
