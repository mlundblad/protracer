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
|  File: Parmeters.h                                                      |
|                                                                         |
|  This file defines the ADT for trace parameters                         |
|                                                                         |
\*************************************************************************/

#ifndef PARAMETERS_H
#define PARAMETERS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Scalar.h"

typedef struct
{
    scalar zoom;
    scalar world_width;
    scalar world_height;
    int    pixel_width;
    int    pixel_height;
} Parameters;



/**************************************************************************
  Function:  Parameters_create
  Arguments: 5 ints
  Result:    Parameters
  Procedure: Parameters object
 *************************************************************************/

Parameters Parameters_create( scalar zoom,
                              scalar world_width,
                              scalar world_height,
                              int pixel_width,
                              int pixel_height );


/**************************************************************************
  Function:  Parameters_zoom
  Arguments: Parameters
  Result:    int
  Procedure: returns the zoom of a Parameters
 *************************************************************************/

scalar Parameters_zoom( Parameters p );


/**************************************************************************
  Function:  Parameters_worldWidth
  Arguments: Parameters
  Result:    int
  Procedure: returns the world width of a Parameters
 *************************************************************************/

scalar Parameters_worldWidth( Parameters p );


/**************************************************************************
  Function:  Parameters_worldHeight
  Arguments: Parameters
  Result:    int
  Procedure: returns the world height of a Parameters
 *************************************************************************/

scalar Parameters_worldHeight( Parameters p );


/**************************************************************************
  Function:  Parameters_pixelWidth
  Arguments: Parameters
  Result:    int
  Procedure: returns the pixel width of a Parameters
 *************************************************************************/

int Parameters_pixelWidth( Parameters p );


/**************************************************************************
  Function:  Parameters_pixelHeight
  Arguments: Parameters
  Result:    int
  Procedure: returns the pixel height of a Parameters
 *************************************************************************/

int Parameters_pixelHeight( Parameters p );

#ifdef __cplusplus
};
#endif

#endif /* PARAMETERS_H */

