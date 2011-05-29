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

