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
