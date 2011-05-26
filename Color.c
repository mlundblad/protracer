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
