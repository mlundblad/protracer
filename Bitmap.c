/*************************************************************************\   
|  File: Bitmap.c                                                         |
|                                                                         |
|  Functions for bitmap handling                                          |
|                                                                         |
\*************************************************************************/

#include <stdlib.h>

#include "Bitmap.h"
#include "Error.h"


Bitmap Bitmap_create( unsigned int width, unsigned int height )
{
    Bitmap bm;
    Color  black = Color_createFromRGB(0, 0, 0);
    int    x, y;

    bm.pixels = (Color *)malloc(sizeof(Color) * width * height);
    
    if( bm.pixels == NULL )
        Error_printErrorAndExit("Out of memory when creating bitmap data");

    bm.width = width;
    bm.height = height;

    /*set all pixels black*/
    for( x = 0 ; x < width ; x++ )
    {
        for( y = 0 ; y < height ; y++ )
        {
            Bitmap_setColorAt( bm, black, x, y );
        }
    }

    return bm;
}

 
void Bitmap_delete( Bitmap bm )
{
    if( bm.pixels )        /* if bitmap isn't empty */
        free( bm.pixels );
}

Color Bitmap_colorAt( Bitmap bm, unsigned int x, unsigned int y )
{
    if( x >= Bitmap_width(bm) || y >= Bitmap_height(bm) )
    {
        Error_printErrorAndExit("Bitmap coordinates out of range");
    }

    return bm.pixels[x + y * Bitmap_width(bm)];
}

/*void Bitmap_setColorAt( Bitmap bm, Color col, unsigned int x, unsigned int y )
{
    if( x >= Bitmap_width(bm) || y >= Bitmap_height(bm) )
    {
        Error_printErrorAndExit( "Bitmap coordinates of range" );
    }

    bm.pixels[x + y * Bitmap_width(bm)] = col;
}*/
    
/*unsigned long Bitmap_width( Bitmap bm )
{
    return bm.width;
}

unsigned long Bitmap_height( Bitmap bm )
{
    return bm.height;
}*/
