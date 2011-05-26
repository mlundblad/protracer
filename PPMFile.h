/*************************************************************************\
|  File: PPMFile.h                                                        |
|                                                                         |
|  ADT for PPM format bitmap files                                        |
|  uses stack allocation                                                  |
\*************************************************************************/

#include "Bitmap.h"

#ifndef PPMFILE_H
#define PPMFILE_H

#include <stdio.h>

#define PPM_MAX_COLOR_VALUE (Color_component)255
#define PPM_MAGIC_ASCII     (char *)"P3"
#define PPM_MAGIC_BINARY    (char *)"P6" 

typedef enum {PPM_ASCII, PPM_BINARY} PPMMode;

typedef struct
{
    FILE   *file;
    PPMMode mode;
} PPMFile;



/**************************************************************************
  Function:  PPMFile_openIn
  Arguments: string
  Result:    PPMFile
  Procedure: opens a PPMFile with given filname
 *************************************************************************/

PPMFile PPMFile_openIn( char *filename );

/*************************************************************************
  Function:  PPMFile_openOut
  Arguments: string, PPMMode
  Result:    PPMFile
  Procedure: opens an existing PPMFile for reading
 *************************************************************************/

PPMFile PPMFile_openOut( char *filename, PPMMode mode );


/**************************************************************************
  Function:  PPMFile_openStdOut
  Arguments: PPMMode
  Result:    PPMFile
  Procedure: opens a ppm file from stdout
 **************************************************************************/

PPMFile PPMFile_openStdOut( PPMMode mode );


/**************************************************************************
  Function:  PPMFile_close
  Arguments: PPMFile
  Result:    void
  Procedure: closes a PPMFile
 **************************************************************************/


void PPMFile_close( PPMFile file );

/***************************************************************************
  Function:  PPMFile_readBitmap
  Arguments: PPMFile
  Result:    pointer to bitmap
  Procedure: reads bitmap from file returning bitmape, user is responsible
             for calling Bitmap_destroy
 **************************************************************************/

Bitmap PPMFile_readBitmap( PPMFile file );

/***************************************************************************
  Function:  PPMFile_writeBitmap
  Arguments: PPMFile, pointer to bitmap
  Result:    pointer to bitmap
  Procedure: writes bitmap to PPMFile
 ***************************************************************************/

void PPMFile_writeBitmap( PPMFile file, Bitmap bm );


#endif /* PPMFILE_H */

