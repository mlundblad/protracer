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
|  File: Color.c                                                          |
|                                                                         |
|  Functions for using the Color ADT.                                     |
|                                                                         |
\*************************************************************************/

#include "Color.h"
#include "Scalar.h"

/*Color Color_createFromRGB(Color_component r, 
                          Color_component g, 
                          Color_component b)
{
    Color c;
    
    c.r = r;
    c.g = g;
    c.b = b;
    
    return c;
}*/

/*Color_component Color_red(Color c)
{
    return c.r;
}

Color_component Color_green(Color c)
{
    return c.g;
}

Color_component Color_blue(Color c)
{
    return c.b;
}*/

/*Color Color_shade( Color color, scalar shade )
{
    return Color_createFromRGB(
        ( (int)((int)Color_red( color ) * shade ) > COLOR_COMPONENT_MAX ?
          (Color_component) COLOR_COMPONENT_MAX :
          Color_red( color ) * shade ),
        
        ( (int)((int)Color_green( color ) * shade ) > COLOR_COMPONENT_MAX ?
          (Color_component) COLOR_COMPONENT_MAX :
          Color_green( color ) * shade ),
        
        ( (int)((int)Color_blue( color ) * shade ) > COLOR_COMPONENT_MAX ?
          (Color_component) COLOR_COMPONENT_MAX :
          Color_blue( color ) * shade ) );
}*/


/*Color Color_combine( Color color1, Color color2 )
{
    return Color_createFromRGB(
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
          Color_blue( color1 ) + Color_blue( color2 ) ) );

}*/
