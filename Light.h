/*************************************************************************\     
|  File: Light.h                                                          |
|                                                                         |
|  Defines an abstract datatype for light sources                         |
|                                                                         |
\*************************************************************************/

#ifndef LIGHT_H
#define LIGHT_H

#include "Vector.h"

typedef struct
{
    Vector position;
} Light;



/**************************************************************************
  Function:  Light_create
  Arguments: Vector
  Result:    Light
  Procedure: create a light positioned at Vector
 *************************************************************************/

#define Light_create( v ) ((Light) {v} )


/**************************************************************************
  Function:  Light_position
  Arguments: Light
  Result:    Vector
  Procedure: gives the position of a light
 *************************************************************************/

#define Light_position( l ) (l.position)


#endif /* LIGHT_H */
