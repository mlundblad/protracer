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
|  File: Finish.h                                                         |
|                                                                         |
|  Defines an abstract datatype for finish used by bison parser           |
|                                                                         |
\*************************************************************************/

#ifndef FINISH_H
#define FINISH_H


#define REFLECTION_DEFAULT (scalar)0.0
#define DIFFUSE_DEFAULT (scalar)1.0

#include "Scalar.h"

typedef struct
{
    scalar diffuse;
    scalar reflection;
} Finish;



/**************************************************************************
  Function:  Finish_create
  Arguments: 2 scalars
  Result:    Finish
  Procedure: creates a finish from diffuse and reflection
 *************************************************************************/

Finish Finish_create( scalar diffuse, scalar reflection );


/**************************************************************************
  Function:  Finish_diffuse
  Arguments: Finish
  Result:    scalar
  Procedure: returns the diffuse of a finish
 *************************************************************************/

scalar Finish_diffuse( Finish fi );


/**************************************************************************
  Function:  Finish_reflection
  Arguments: Finish
  Result:    scalar
  Procedure: returns the reflection of a finish
 *************************************************************************/

scalar Finish_reflection( Finish fi );

#endif /* FINISH_H */
