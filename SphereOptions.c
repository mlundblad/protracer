/*************************************************************************\
|  File: SphereOptions.c                                                  |
|                                                                         |
|  Implements sphere options                                              |
|                                                                         |
\*************************************************************************/

#include "SphereOptions.h"

SphereOptions SphereOptions_create( Vector pole, Vector equator )
{
    SphereOptions so;

    so.pole = pole;
    so.equator = equator;
    return so;
}

/*Vector SphereOptions_pole( SphereOptions so )
{
    return so.pole;
}

Vector SphereOptions_equator( SphereOptions so )
{
    return so.equator;
}*/
