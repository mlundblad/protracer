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
|  File: HitData.h                                                        |
|                                                                         |
|  Defines an abstract datatype for hit data                              |
|                                                                         |
\*************************************************************************/

#ifndef HIT_DATA_H
#define HIT_DATA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Scalar.h"
#include "Vector.h"
#include "Color.h"
#include "Scalar.h"

typedef struct
{
    scalar distance;
    Vector normal;
    Color  color;
    bool   hit;
} HitData;


/**************************************************************************
  Function:  HitData_createNoHit
  Arguments: void
  Result:    HitData
  Procedure: returns a HitData indicating no hit
  *************************************************************************/

static inline HitData HitData_createNoHit( void )
{
    HitData hd;
    hd.hit = FALSE;
    return hd;
}



/**************************************************************************
  Function:  HitData_createHit
  Arguments: scalar, Vector, Color
  Result:    HitData
  Procedure: returns a HitData given hit indication, distance, normal and
  Color indicating a hit
  *************************************************************************/

#define HitData_createHit( dist, normal, color ) ((HitData) \
{ dist, normal, color, TRUE } )



/**************************************************************************
  Function:  HitData_hit
  Arguments: HitData
  Result:    bool
  Procedure: given a HitData return TRUE if hit, else FALSE
 *************************************************************************/

#define HitData_hit( hitdata ) (hitdata.hit)


/**************************************************************************
  Function:  HitData_distance
  Arguments: HitData
  Result:    scalar
  Procedure: given a HitData return distance
 *************************************************************************/

#define HitData_distance( hitdata ) (hitdata.distance)


/**************************************************************************
  Function:  HitData_normal
  Arguments: HitData
  Result:    Vector
  Procedure: given a HitData return hit normal
 *************************************************************************/

#define HitData_normal( hitdata ) (hitdata.normal )


/**************************************************************************
  Function:  HitData_color
  Arguments: HitData
  Result:    Color
  Procedure: given a HitData return color at hitpoint
 *************************************************************************/

#define HitData_color( hitdata ) (hitdata.color)


/**************************************************************************
  Function:  HitData_setColor
  Arguments: HitData
  Result:    void
  Procedure: given a HitData set it's color
 *************************************************************************/

#define HitData_setColor( hitdata, col ) (hitdata.color = (col) )

#ifdef __cplusplus
};
#endif

#endif
