/*************************************************************************\
|  File: Error.c                                                          |
|                                                                         |
|  Functions for error handling                                           |
|                                                                         |
\*************************************************************************/

#include <stdio.h>

#include "Error.h"

void Error_printErrorAndExit( char *err )
{
    fprintf( stderr, "%s Aborting...\n", err );
    exit( 0 );
}

