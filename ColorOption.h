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
