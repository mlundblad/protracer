/*************************************************************************\
|  File: ObjectMods.h                                                     |
|                                                                         |
|  Defines an abstract datatype for object pramams                        |
|  uses stack allocation                                                  |
\*************************************************************************/

#ifndef OBJECTMODS_H
#define OBJECTMODS_H

#include "Pigment.h"
#include "Finish.h"

typedef struct
{
    Pigment  pigment;
    Finish   finish;
} ObjectMods;


/**************************************************************************
  Function:  ObjectMods_create
  Arguments: Color, double, double
  Result:    ObjectMods
  Procedure: creates an objectmods
 *************************************************************************/

ObjectMods ObjectMods_create( Pigment col, Finish fin );


/**************************************************************************
  Function:  ObjectMods_pigment
  Arguments: ObjectMods
  Result:    Pigment
  Procedure: returns the pigment of an object mod
 *************************************************************************/

Pigment ObjectMods_pigment( ObjectMods om );

/**************************************************************************
  Function:  ObjectMods_finish
  Arguments: ObjectMods
  Result:    Finish
  Procedure: returns the finish of an object mods
 *************************************************************************/

Finish ObjectMods_finish( ObjectMods om );

#endif /* OBJECTMODS_H */

