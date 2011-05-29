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
|  File: ColorOption.h                                                    |
|                                                                         |
|  Defines an abstract datatype for color options                         |
|  uses stack allocation                                                  |
\*************************************************************************/


#ifndef COLOROPTION_H
#define COLOROPTION_H

#include "Color.h"
#include "Bool.h"

typedef struct
{
    Color col;
    bool  backGround;
} ColorOption;


/**************************************************************************
  Function:  ColorOption_create
  Arguments: Color, bool
  Result:    ColorOption
  Procedure: creates a ColorOption
 *************************************************************************/

ColorOption ColorOption_create( Color col, bool isBackground );


 
/**************************************************************************
  Function:  ColorOption_color
  Arguments: ColorOption
  Result:    Color
  Procedure: returns the color of a color option
 *************************************************************************/

Color ColorOption_color( ColorOption co );


/**************************************************************************
  Function:  ColorOption_switch
  Arguments: ColorOption
  Result:    bool
  Procedure: returns TRUE if the option is representing a background
 *************************************************************************/

bool ColorOption_isBackground( ColorOption co );

#endif /* COLOROPTION_H */
