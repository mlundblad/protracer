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
|  File: LightArray.h                                                     |
|                                                                         |
|  Defines an abstract datatype for arrays of lights                      |
|                                                                         |
\*************************************************************************/

#ifndef LIGHTARRAY_H
#define LIGHTARRAY_H

#include "Light.h"
#include "LightList.h"

typedef struct
{
    int     num_lights;
    Light  *lights;
} LightArray;



/**************************************************************************
  Function:  LightArray_create
  Arguments: unsigned int
  Result:    LightArray
  Procedure: creates an Light array with spec. number of Lights,
             fails if unable to allocate memory for Lights
 *************************************************************************/

LightArray LightArray_create( unsigned int number );


/**************************************************************************
  Function:  LightArray_createFromList
  Arguments: ItemList
  Result:    LightArray
  Procedure: creates an Light array from an itemlist with Lights
 *************************************************************************/

LightArray LightArray_createFromList( LightList ll );


/**************************************************************************
  Function:  LightArray_destroy
  Arguments: LightArray
  Result:    void
  Procedure: deletes an Light array
 *************************************************************************/

void LightArray_destroy( LightArray oa );


/**************************************************************************
  Function:  LightArray_numLights
  Arguments: LightArray
  Result:    unsigned int
  Procedure: returns the number of Lights in an Light array
 *************************************************************************/

#define LightArray_numLights( la ) (la.num_lights)


/**************************************************************************
  Function:  LightArray_LightAt
  Arguments: LightArray, unsigned int
  Result:    Light
  Procedure: returns the Light at a spec. index in the array, fails if index
             is out of range, indexes start at 0
 *************************************************************************/

#define LightArray_lightAt( la, index ) (la.lights[index])


/**************************************************************************
  Function:  LightArray_setLightAt
  Arguments: Light, unsigned int index
  Result:    void
  Procedure: sets the Light at index, fails if index is out of range
 *************************************************************************/

void LightArray_setLightAt( LightArray oa, Light o, unsigned int index );


#endif /* OBJECTARRAY_H */
