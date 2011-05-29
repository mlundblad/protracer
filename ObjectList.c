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
|  File: ObjectList.c                                                     |
|                                                                         |
|  Functions for using the ObjectList ADT                                 |
|                                                                         |
\*************************************************************************/

#include "ObjectList.h"
#include "Error.h"
#include "Bool.h"

#include <stdlib.h>


ObjectList ObjectList_createEmpty( void )
{
    return (ObjectList) NULL;
}


ObjectList ObjectList_insert(Object o, ObjectList ol)
{
    ObjectList new = malloc( sizeof( struct ObjectList ) );
    
    if(new == NULL)
        Error_printErrorAndExit( "Out of memory inserting Object in list" );

    new->head = o;
    new->tail = ol;
  
    return new;
}
    
bool ObjectList_isEmpty( ObjectList ol )
{
    return (ol == NULL ) ? TRUE : FALSE;
}

Object ObjectList_head( ObjectList ol )
{
    if( ObjectList_isEmpty( ol ) )
        Error_printErrorAndExit( "Can't get head of empty list" );
    
    return ol->head;
}

ObjectList ObjectList_tail( ObjectList ol )
{
    if( ObjectList_isEmpty( ol ) )
        Error_printErrorAndExit( "Can't get tail of empty list" );

    return ol->tail;
}    


