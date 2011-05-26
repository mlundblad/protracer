/*************************************************************************\
|  File: SphereOptions.h                                                  |
|                                                                         |
|  Defines an abstract datatype for sphere options used by bison parser   |
|                                                                         |
\*************************************************************************/

#ifndef SPHEREOPTIONS_H
#define SPHEREOPTIONS_H

#include "Vector.h"

typedef struct
{
    Vector pole;
    Vector equator;
} SphereOptions;


/**************************************************************************
  Function:  SphereOptions_create
  Arguments: 2 Vectors
  Result:    SphereOpt
  Procedure: creates a sphere option
 *************************************************************************/

SphereOptions SphereOptions_create( Vector pole, Vector equator );


/**************************************************************************
  Function:  SphereOptions_pole
  Arguments: SphereOptions
  Result:    Vector
  Procedure: return the pole vector
 *************************************************************************/

static inline Vector SphereOptions_pole( SphereOptions so )
{
    return so.pole;
}



/**************************************************************************
  Function:  SphereOptions_equator
  Arguments: SphereOptions
  Result:    Vector
  Procedure: return the pole vector
 *************************************************************************/

static inline Vector SphereOptions_equator( SphereOptions so )
{
    return so.equator;
}

#endif /* SPHEREOPTIONS_H */

