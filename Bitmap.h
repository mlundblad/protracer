/*************************************************************************\    
|  File: Bitmap.h                                                         |
|                                                                         |
|  Dfines an abstract datatype for bitmaps                               |
|  uses heap alloctaion, caller is responsible for calling Bitmap_destroy |
\*************************************************************************/


#ifndef BITMAP_H
#define BITMAP_H


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

#endif /* BITMAP_H */

