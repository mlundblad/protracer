/*************************************************************************\
|  File: Error.h                                                          |
|                                                                         |
|  Defines an error handling module                                       |
|                                                                         |
\*************************************************************************/

#ifndef ERROR_H
#define ERROR_H 

#include <stdio.h>

/**************************************************************************
 Function:  ErrorPrintErrorAndExit         
 Arguments: string         
 Result:    void            
 Procedure: prints error and exits
 *************************************************************************/

void Error_printErrorAndExit( char *err );

#define ERROR_PRINT_DEBUG(ds) fputs(ds, stderr)

#endif /*ERROR_H */
