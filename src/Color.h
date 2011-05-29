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
|  File: Color.h                                                          |
|                                                                         |
|  Defines an abstract datatype for colors                                |
|  uses stack allocation                                                  |
\*************************************************************************/

#ifndef COLOR_H
#define COLOR_H

#include "Scalar.h"

#define COLOR_COMPONENT_MAX (Color_component)255

typedef unsigned char Color_component; 



typedef struct
{
    Color_component r;
    Color_component g;
    Color_component b;
} Color;


/**************************************************************************
  Function:  Color_createFromRGB
  Arguments: 3 RGB_components
  Result:    Color
  Procedure: creates a color from 3 RGB components
 *************************************************************************/

#define Color_createFromRGB( r, g, b ) ((Color) { r,g,b } )


/**************************************************************************
  Function:  Color_red/green/blue
  Arguments: Color
  Result:    RGB_component
  Procedure: these functions get the respective RGB component from a color
 *************************************************************************/

/*
static inline Color_component Color_red( Color c )
{
    return c.r;
}
static inline Color_component Color_green( Color c )
{
    return c.g;
}

static inline Color_component Color_blue( Color c )
{
    return c.b;
}
*/

#define Color_red( c ) ((Color_component) c.r )
#define Color_green( c ) ((Color_component) c.g )
#define Color_blue( c ) ((Color_component) c.b )


/**************************************************************************
  Function:  Color_shade
  Arguments: Color, shade factor (scalar)
  Result:    Color
  Procedure: Shades the color, with the given constant
 *************************************************************************/


static inline Color Color_shade( Color color, scalar shade )
{
    Color col;
    
    col.r = (int)((int)color.r * shade ) > COLOR_COMPONENT_MAX ?
            (Color_component) COLOR_COMPONENT_MAX :
            color.r * shade;

    col.g = (int)((int)color.g * shade ) > COLOR_COMPONENT_MAX ?
            (Color_component) COLOR_COMPONENT_MAX :
            color.g * shade;

    col.b = (int)((int)color.b * shade ) > COLOR_COMPONENT_MAX ?
            (Color_component) COLOR_COMPONENT_MAX :
            color.b * shade;

    return col;
}

/*
#define Color_shade( color, shade ) ((Color) { \
(int)((int)color.r * shade ) > COLOR_COMPONENT_MAX ? \
(Color_component) COLOR_COMPONENT_MAX : \
color.r * shade, \
(int)((int)color.g * shade ) > COLOR_COMPONENT_MAX ? \
(Color_component) COLOR_COMPONENT_MAX : \
color.g * shade, \
(int)((int)color.b * shade ) > COLOR_COMPONENT_MAX ? \
(Color_component) COLOR_COMPONENT_MAX : \
color.b * shade } )
*/




/**************************************************************************
  Function:  Color_combine
  Arguments: Color, Color
  Result:    Color
  Procedure: Gives the average of 2 colors
 *************************************************************************/

static inline Color Color_combine( Color color1, Color color2 )
{
    Color col;
    /*return Color_createFromRGB(
        ( (int)(Color_red( color1 ) + 
                Color_red( color2 )) > COLOR_COMPONENT_MAX ?
          (Color_component) COLOR_COMPONENT_MAX :
          Color_red( color1 ) + Color_red( color2 ) ),

          ( (int)(Color_green( color1 ) + 
                  Color_green( color2 )) > COLOR_COMPONENT_MAX ?
          (Color_component) COLOR_COMPONENT_MAX :
          Color_green( color1 ) + Color_green( color2 ) ),
          
          ( (int)(Color_blue( color1 ) + 
                  Color_blue( color2 )) > COLOR_COMPONENT_MAX ?
          (Color_component) COLOR_COMPONENT_MAX :
          Color_blue( color1 ) + Color_blue( color2 ) ) );*/

    col.r = (int)(color1.r + color2.r ) > COLOR_COMPONENT_MAX ?
            (Color_component) COLOR_COMPONENT_MAX :
             color1.r + color2.r;

    col.g = (int)(color1.g + color2.g ) > COLOR_COMPONENT_MAX ?
            (Color_component) COLOR_COMPONENT_MAX :
             color1.g + color2.g;

    col.b = (int)(color1.b + color2.b ) > COLOR_COMPONENT_MAX ?
            (Color_component) COLOR_COMPONENT_MAX :
             color1.b + color2.b;
    
    return col;
}


#endif /* COLOR_H */
