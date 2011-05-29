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
|  File: LightArray.c                                                     |
|                                                                         |
|  Implements the ADT for light arrays                                    |
|                                                                         |
\*************************************************************************/


#include "LightArray.h"
#include "Error.h"

#include <stdlib.h>

LightArray LightArray_create( unsigned int num )
{
    LightArray la;

    la.num_lights = num;
    la.lights = malloc( sizeof( Light ) * num );
    
    if(la.lights == NULL)
        Error_printErrorAndExit( "Outofmem alloc light arr" );

    /*fprintf( stderr, "Created Light array with %d entries\n", num );*/

    return la;
}


LightArray LightArray_createFromList( LightList ll )
{
    LightList tempList = ll;
    LightArray la;
    int num = 0;
    int index = 0;

    while( ! LightList_isEmpty( tempList ) )
    {
        tempList = LightList_tail( tempList );
        num++;
    }

    la = LightArray_create( num );

    while( !LightList_isEmpty( ll ) )
    {
        LightArray_setLightAt( la, 
                               LightList_head( ll ),
                               index );
        ll = LightList_tail( ll );
        index++;
    }
    
    return la;
}

void LightArray_destroy( LightArray la )
{
    free(la.lights);
}



void LightArray_setLightAt( LightArray la, Light l, unsigned int index )
{
    /*fprintf( stderr, "Trying to set element %d in a %d element array\n",
      index, LightArray_countItems( oa ) );*/
    /*if( index >= LightArray_numLights( la ) )
        Error_printErrorAndExit( "Light array index of of bounds" );*/

    la.lights[index] = l;
}

