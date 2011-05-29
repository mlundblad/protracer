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
