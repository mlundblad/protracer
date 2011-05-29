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
|  File: ObjectList.h                                                     |
|                                                                         |
|  Defines an abstract datatype for object lists                          |
|                                                                         |
\*************************************************************************/

#ifndef OBJECTLIST_H
#define OBJECTLIST_H

#include "Object.h"

struct ObjectList
{
    Object             head;
    struct ObjectList *tail;
};

typedef struct ObjectList *ObjectList;

/**************************************************************************
  Function:  ObjectList_createEmpty
  Arguments: void
  Result:    ObjectList
  Procedure: creates an empty Object list
 *************************************************************************/

ObjectList ObjectList_createEmpty( void );


/**************************************************************************
  Function:  ObjectList_insert
  Arguments: Object, ObjectList
  Result:    ObjectList
  Procedure: inserts an Object in front of an existing list
 *************************************************************************/

ObjectList ObjectList_insert( Object o, ObjectList ol );


/**************************************************************************
  Function:  ObjectList_isEmpty
  Arguments: ObjectList
  Result:    bool
  Procedure: returns TRUE if list is empty, otherwise FALSE
 *************************************************************************/

bool ObjectList_isEmpty( ObjectList ol );


/**************************************************************************
  Function:  ObjectList_head
  Arguments: ObjectList
  Result:    Object
  Procedure: returns head of list
 *************************************************************************/

Object ObjectList_head( ObjectList ol );


/**************************************************************************
  Function:  ObjectList_tail
  Arguments: ObjectList
  Result:    Object
  Procedure: returns tail of list
 *************************************************************************/

ObjectList ObjectList_tail( ObjectList ol );



#endif /* OBJECTLIST_H */
 
