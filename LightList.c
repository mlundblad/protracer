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


