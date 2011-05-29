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
|  File: Camera.c                                                         |
|                                                                         |
|  This file has functions for the Camera struct                          |
|  Copyright (C) Ulf Magnusson & Marcus Lundblad & Yuwei Zhao 1999        |
|                                                                         |
\*************************************************************************/

#include "Camera.h"
#include <stdio.h>
#include "Scalar.h"

Camera Camera_create( Vector location,
                      Vector lookAt,
                      Vector upVector,
                      scalar zoom,
                      scalar worldWidth,
                      scalar worldHeight,
                      long   pixelWidth,
                      long   pixelHeight )
{
    Camera cam;
    cam.location = location;
    cam.lookAt = lookAt;
    cam.upVector = upVector;
    cam.zoom = zoom;
    cam.worldWidth = worldWidth;
    cam.worldHeight = worldHeight;
    cam.pixelWidth = pixelWidth;
    cam.pixelHeight = pixelHeight;
    return( cam );
}

