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
|  File: Bitmap.h                                                         |
|                                                                         |
|  Dfines an abstract datatype for bitmaps                               |
|  uses heap alloctaion, caller is responsible for calling Bitmap_destroy |
\*************************************************************************/


#ifndef BITMAP_H
#define BITMAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Color.h"
#include "Bool.h"
#include "Error.h"

typedef struct
{
    unsigned long width;
    unsigned long height;
    
    Color *pixels;
} Bitmap;


/**************************************************************************
  Function:  Bitmap_create
  Arguments: 2 unsigned ints
  Result:    Bitmap
  Procedure: creates a bitmap given width and height, inits it black
 *************************************************************************/

Bitmap Bitmap_create(unsigned int width, unsigned int height);


/**************************************************************************
  Function:  Bitmap_delete
  Arguments: pointer to bitmap
  Result:    void
  Procedure: deletes bitmap
 *************************************************************************/

void Bitmap_delete( Bitmap bm );


/**************************************************************************
  Function:  Bitmap_colorAt
  Arguments: pointer to bitmap, 2 unsigned ints
  Result:    Color
  Procedure: gets color at spec. pos in bitmap
 *************************************************************************/

Color Bitmap_colorAt( Bitmap bm, unsigned int x, unsigned int y );



/**************************************************************************
  Function:  Bitmap_getWidth
  Arguments: 
  Result:    unsigned long
  Procedure: return value from struct

 *************************************************************************/

static inline unsigned long Bitmap_width( Bitmap bm )
{
    return bm.width;
}



/**************************************************************************
  Function:  Bitmap_getHeight
  Arguments: 
  Result:    unsigned long
  Procedure: return value from struct

 *************************************************************************/

static inline unsigned long Bitmap_height( Bitmap bm )
{
    return bm.height;
}


/**************************************************************************
  Function:  Bitmap_setColorAt
  Arguments: pointer to bitmap, color, 2 unsigned ints
  Result:    void
  Procedure: sets color at given pos in bitmap, fails if coords is out of range 
 *************************************************************************/

static inline void Bitmap_setColorAt( Bitmap bm, Color col, unsigned int x, unsigned int y )
{
    if( x >= Bitmap_width(bm) || y >= Bitmap_height(bm) )
    {
        Error_printErrorAndExit( "Bitmap coordinates of range" );
    }

    bm.pixels[x + y * Bitmap_width(bm)] = col;
}

#ifdef __cplusplus
};
#endif

#endif /* BITMAP_H */

