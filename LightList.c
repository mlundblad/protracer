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
|  File: LightList.c                                                      |
|                                                                         |
|  Functions for using the light list ADT                                 |
|                                                                         |
\*************************************************************************/

#include "LightList.h"
#include "Error.h"

#include <stdlib.h>


LightList LightList_createEmpty( void )
{
    return (LightList) NULL;
}


LightList LightList_insert(Light l, LightList ll)
{
    LightList new = malloc( sizeof( struct LightList ) );
    
    if(new == NULL)
        Error_printErrorAndExit( "Out of memory inserting Light in list" );

    new->head = l;
    new->tail = ll;
  
    return new;
}
    
bool LightList_isEmpty( LightList ll )
{
    return (ll == NULL ) ? TRUE : FALSE;
}

Light LightList_head( LightList ll )
{
    if( LightList_isEmpty( ll ) )
        Error_printErrorAndExit( "Can't get head of empty list" );
    
    return ll->head;
}

LightList LightList_tail( LightList ll )
{
    if( LightList_isEmpty( ll ) )
        Error_printErrorAndExit( "Can't get tail of empty list" );

    return ll->tail;
}    


