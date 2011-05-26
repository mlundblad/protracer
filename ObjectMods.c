/*************************************************************************\
|  File: ObjectMods.c                                                     |
|                                                                         |
|  implements an abstract datatype for object pramams                     |
\*************************************************************************/

#include "ObjectMods.h"

ObjectMods ObjectMods_create( Pigment pgmnt, Finish fin )
{
    ObjectMods om;
    
    om.pigment = pgmnt;
    om.finish = fin;

    return om;
}

Pigment ObjectMods_pigment( ObjectMods om )
{
    return om.pigment;
}

Finish ObjectMods_finish( ObjectMods om )
{
    return om.finish;
}

