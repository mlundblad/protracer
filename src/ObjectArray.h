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
|  File: ObjectArray.h                                                    |
|                                                                         |
|  Defines an abstract datatype for arrays of objects                     |
|                                                                         |
\*************************************************************************/

#ifndef OBJECTARRAY_H
#define OBJECTARRAY_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Object.h"
#include "ObjectList.h"
#include "Error.h"

typedef struct
{
    int     num_objects;
    Object *objects;
} ObjectArray;


/**************************************************************************
  Function:  ObjectArray_create
  Arguments: unsigned int
  Result:    ObjectArray
  Procedure: creates an object array with spec. number of objects,
             fails if unable to allocate memory for objects
 *************************************************************************/

ObjectArray ObjectArray_create( unsigned int number );


/**************************************************************************
  Function:  ObjectArray_createFromList
  Arguments: ItemList
  Result:    ObjectArray
  Procedure: creates an object array from an itemlist with objects
 *************************************************************************/

ObjectArray ObjectArray_createFromList( ObjectList ol );


/**************************************************************************
  Function:  ObjectArray_destroy
  Arguments: ObjectArray
  Result:    void
  Procedure: deletes an object array
 *************************************************************************/

void ObjectArray_destroy( ObjectArray oa );


/**************************************************************************
  Function:  ObjectArray_numObjects
  Arguments: ObjectArray
  Result:    unsigned int
  Procedure: returns the number of objects in an object array
 *************************************************************************/

#define ObjectArray_numObjects( oa ) (oa.num_objects)


/**************************************************************************
  Function:  ObjectArray_objectAt
  Arguments: ObjectArray, unsigned int
  Result:    Object
  Procedure: returns the Object at a spec. index in the array, fails if index
             is out of range, indexes start at 0
 *************************************************************************/

#define ObjectArray_objectAt( oa, index ) (oa.objects[index])


/**************************************************************************
  Function:  ObjectArray_setObjectAt
  Arguments: Object, unsigned int index
  Result:    void
  Procedure: sets the object at index, fails if index is out of range
 *************************************************************************/

void ObjectArray_setObjectAt( ObjectArray oa, Object o, unsigned int index );

#ifdef __cplusplus
};
#endif

#endif /* OBJECTARRAY_H */
