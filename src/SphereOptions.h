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

