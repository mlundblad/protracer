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
|  File: Parmeters.c                                                      |
|                                                                         |
|  This file implements the ADT for trace parameters                      |
|                                                                         |
\*************************************************************************/

#include "Parameters.h"
#include "Scalar.h"


#include <stdio.h>

Parameters Parameters_create( scalar zoom,
                              scalar world_width,
                              scalar world_height,
                              int pixel_width,
                              int pixel_height )
{
    Parameters p;

    p.zoom = zoom;
    p.world_width = world_width;
    p.world_height = world_height;
    p.pixel_width = pixel_width;
    p.pixel_height = pixel_height;

    return p;
}

scalar Parameters_zoom( Parameters p )
{
    return p.zoom;
}

scalar Parameters_worldWidth( Parameters p )
{
    return p.world_width;
}

scalar Parameters_worldHeight( Parameters p )
{
    return p.world_height;
}

int Parameters_pixelWidth( Parameters p )
{
    return p.pixel_width;
}

int Parameters_pixelHeight( Parameters p )
{
    return p.pixel_height;
}
