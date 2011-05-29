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

#ifndef LIGHTLIST_H
#define LIGHTLIST_H

#include "Light.h"
#include "Bool.h"

struct LightList
{
    Light             head;
    struct LightList *tail;
};

typedef struct LightList *LightList;

/**************************************************************************
  Function:  LightList_createEmpty
  Arguments: void
  Result:    LightList
  Procedure: creates an empty Light list
 *************************************************************************/

LightList LightList_createEmpty( void );


/**************************************************************************
  Function:  LightList_insert
  Arguments: Light, LightList
  Result:    LightList
  Procedure: inserts an Light in front of an existing list
 *************************************************************************/

LightList LightList_insert( Light l, LightList ll );


/**************************************************************************
  Function:  LightList_isEmpty
  Arguments: LightList
  Result:    bool
  Procedure: returns TRUE if list is empty, otherwise FALSE
 *************************************************************************/

bool LightList_isEmpty( LightList ll );


/**************************************************************************
  Function:  LightList_head
  Arguments: LightList
  Result:    Light
  Procedure: returns head of list
 *************************************************************************/

Light LightList_head( LightList ll );


/**************************************************************************
  Function:  LightList_tail
  Arguments: LightList
  Result:    Light
  Procedure: returns tail of list
 *************************************************************************/

LightList LightList_tail( LightList ll );



#endif /* LIGHTLIST_H */
 
