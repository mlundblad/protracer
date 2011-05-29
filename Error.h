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
