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

