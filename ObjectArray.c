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
|  File: ObjectArray.c                                                    |
|                                                                         |
|  Implements the ADT for object arrays                                   |
|                                                                         |
\*************************************************************************/


#include "ObjectArray.h"
#include "Error.h"

#include <stdlib.h>

ObjectArray ObjectArray_create( unsigned int num )
{
    ObjectArray oa;

    oa.num_objects = num;
    oa.objects = malloc( sizeof( Object ) * num );
    
    if(oa.objects == NULL)
        Error_printErrorAndExit( "Outofmem allocing object arr" );

    /*fprintf( stderr, "Created object array with %d entries\n", num );*/

    return oa;
}


ObjectArray ObjectArray_createFromList( ObjectList ol )
{
    ObjectList tempList = ol;
    ObjectArray oa;
    int num = 0;
    int index = 0;

    while( !ObjectList_isEmpty( tempList ) )
    {
        tempList = ObjectList_tail( tempList );
        num++;
    }

    oa = ObjectArray_create( num );

    while( !ObjectList_isEmpty( ol ) )
    {
        ObjectArray_setObjectAt( oa, 
                                 ObjectList_head( ol ),
                                 index );
        ol = ObjectList_tail( ol );

        index++;
    }
    
    return oa;
}

void ObjectArray_destroy( ObjectArray oa )
{
    free(oa.objects);
}


void ObjectArray_setObjectAt( ObjectArray oa, Object o, unsigned int index )
{
    /*fprintf( stderr, "Trying to set element %d in a %d element array\n",
      index, ObjectArray_numObjects( oa ) );*/
    /*if( index >= ObjectArray_numObjects( oa ) )
        Error_printErrorAndExit( "Object array index of of bounds" );*/

    oa.objects[index] = o;
}

