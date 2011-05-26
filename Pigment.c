/*************************************************************************\
|  File: Pigment.c                                                        |
|                                                                         |
|  Functions for using the Pigment ADT                                    |
|                                                                         |
\*************************************************************************/

#include "Pigment.h"

PigmentType Pigment_type( Pigment pigment )
{
    return pigment.type;
}

Pigment Pigment_createColor( Color col )
{
    Pigment pgmnt;

    pgmnt.type = PIGMENT_COLOR;
    pgmnt.pigment.color = col;

    return pgmnt;
}

Color Pigment_color( Pigment pigment )
{
    return pigment.pigment.color;
}


Pigment Pigment_createBitmap( Bitmap bitmap )
{
    Pigment pgmnt;

    pgmnt.type = PIGMENT_BITMAP;
    pgmnt.pigment.bitmap = bitmap;
    
    return pgmnt;
}

Bitmap Pigment_bitmap( Pigment pigment )
{
    return pigment.pigment.bitmap;
}
