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
|  File: Pigment.h                                                        |
|                                                                         |
|  Defines an abstract datatype for pigment                               |
|  uses stack allocation                                                  |
\*************************************************************************/

#ifndef PIGMENT_H
#define PIGMENT_H

#include "Color.h"
#include "Bitmap.h"

/* pigment defaults */
#define PIGMENT_DEFAULT_RED (Color_component)127  /* 0.5 of total */
#define PIGMENT_DEFAULT_GREEN (Color_component)127
#define PIGMENT_DEFAULT_BLUE (Color_component)127

typedef enum {PIGMENT_COLOR, PIGMENT_BITMAP} PigmentType;

typedef struct
{
    PigmentType type;
    union
    {
        Color  color;
        Bitmap bitmap;
    } pigment;
} Pigment;


/**************************************************************************
  Function:  Pigment_type
  Arguments: Pigment
  Result:    PigmentType
  Procedure: Returns the pigment type
 *************************************************************************/

PigmentType Pigment_type( Pigment pigment );


/**************************************************************************
  Function:  Pigment_createColor
  Arguments: Color
  Result:    Pigment
  Procedure: creates a pigment of type color
 *************************************************************************/

Pigment Pigment_createColor( Color col );


/**************************************************************************
  Function:  Pigment_color
  Arguments: Pigment
  Result:    Color
  Procedure: returns the Color
 *************************************************************************/

Color Pigment_color( Pigment pigment );


/**************************************************************************
  Function:  Pigment_createBitmap
  Arguments: Bitmap
  Result:    Pigment
  Procedure: creates a pigment of type bitmap
 *************************************************************************/

Pigment Pigment_createBitmap( Bitmap bitmap );

/**************************************************************************
  Function:  Pigment_bitmap
  Arguments: Pigment
  Result:    bitmap
  Procedure: returns the Bitmap
 *************************************************************************/

Bitmap Pigment_bitmap( Pigment pigment );


#endif /* PIGMENT_H */

