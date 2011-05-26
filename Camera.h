/*************************************************************************\      
|  File: Camera.h                                                         |
|                                                                         |
|  This file defines the Camera struct                                    |
|  Copyright (C) Ulf Magnusson & Marcus Lundblad & Yuwei Zhao 1999        |
|                                                                         |
\*************************************************************************/

#ifndef _CAMERA_H
#define _CAMERA_H

#include "Vector.h"
#include "Bool.h"
#include "Scalar.h"


typedef struct
{
    Vector location;
    Vector lookAt;
    Vector upVector;
    scalar zoom;
    scalar worldWidth;
    scalar worldHeight;
    long   pixelWidth;
    long   pixelHeight;
} Camera;

/**************************************************************************
  Function:  Camera_create
  Arguments: Vector location,
             Vector lookAt,
	     Vector upVector,
	     scalar zoom,
	     scalar worldWidth,
	     scalar worldHeight,
	     long pixelWidth,
	     long pixelHeight
  Result:    A Camera
  Procedure: Create a new camera and 
 *************************************************************************/

Camera Camera_create( Vector location,
		    Vector lookAt,
		    Vector upVector,
		    scalar zoom,
		    scalar worldWidth,
		    scalar worldHeight,
		    long pixelWidth,
		    long pixelHeight );


/**************************************************************************
  Function:  Camera_location
  Arguments: Camera
  Result:    Vector
  Procedure: Fetch the location vector in the struct
 *************************************************************************/

static inline Vector Camera_location( Camera cam )
{
    return cam.location;
}



/**************************************************************************
  Function:  Camera_lookAt
  Arguments: Camera
  Result:    Vector
  Procedure: Fetch the lookAt vector in the struct
 *************************************************************************/

static inline Vector Camera_lookAt( Camera cam )
{
    return cam.lookAt;
}



/**************************************************************************
  Function:  Camera_upVector
  Arguments: Camera
  Result:    Vector
  Procedure: Fetch the upVector vector in the struct
 *************************************************************************/

static inline Vector Camera_upVector( Camera cam )
{
    return cam.upVector;
}


/**************************************************************************
  Function:  Camera_zoom
  Arguments: Camera
  Result:    scalar
  Procedure: Fetch the zoom constant in the class
 *************************************************************************/

static inline scalar Camera_zoom( Camera cam ) 
{
    return cam.zoom;
}


/**************************************************************************
  Function:  Camera_pixelWidth
  Arguments: Camera
  Result:    scalar
  Procedure: Fetch the width constant in the struct
 *************************************************************************/

static inline long Camera_pixelWidth( Camera cam )
{
    return cam.pixelWidth;
}

/**************************************************************************
  Function:  Camera_pixelHeight
  Arguments: Camera
  Result:    scalar
  Procedure: Fetch the width constant in the struct
 *************************************************************************/

static inline long Camera_pixelHeight( Camera cam )
{
    return cam.pixelHeight;
}


/**************************************************************************
  Function:  Camera_worldWidth
  Arguments: Camera
  Result:    long
  Procedure: Fetch the width constant in the struct
 *************************************************************************/

static inline scalar Camera_worldWidth( Camera cam )
{
    return cam.worldWidth;
}


/**************************************************************************
  Function:  Camera_worldHeight
  Arguments: Camera
  Result:    long
  Procedure: Fetch the width constant in the struct
 *************************************************************************/

static inline scalar Camera_worldHeight( Camera cam ) 
{
    return cam.worldHeight;
}


#endif
