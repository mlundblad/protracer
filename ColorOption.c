/*************************************************************************\
|  File: ColorOption.c                                                    |
|                                                                         |
|  implements an abstract datatype for color options                      |
|  uses stack allocation                                                  |
\*************************************************************************/

#include "ColorOption.h"

ColorOption ColorOption_create( Color col, bool isBackground )
{
    return (ColorOption){ col, isBackground };
}

Color ColorOption_color( ColorOption co )
{
    return co.col;
}

bool ColorOption_isBackground( ColorOption co )
{
    return co.backGround;
}


