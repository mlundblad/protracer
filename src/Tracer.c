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
|  File: Tracer.c                                                         |
|                                                                         |
|  This is the main file for the tracer                                   |
|                                                                         |
\*************************************************************************/

#include <stdlib.h>
#include <getopt.h>

#include "Scalar.h"

#include "Bitmap.h"
#include "PPMFile.h"
#include "Error.h"
/*#include "Timer.h"*/
#include "World.h"

#include "ObjectMods.h"
#include "Finish.h"
#include "SphereOptions.h"

#include "Parameters.h"

#include "Baseparse.h"


#define XPIX_MASK 0x1
#define YPIX_MASK 0x2
#define WIDTH_MASK 0x4
#define HEIGHT_MASK 0x8

void printWelcomeMessage( void )
{
    fprintf( stderr, "********************************************\n" );
    fprintf( stderr, "* PRO-Tracer v0.8                          *\n" );
    fprintf( stderr, "* Who knew nice code could be this fast... *\n" );
    fprintf( stderr, "********************************************\n\n" );
    fflush( stderr );

}

World parse( scalar zoom, long xpix, long ypix, scalar width, scalar height)
{
    extern int yyparse();
    /*extern YYSTYPE yylval;*/

    extern Parameters  global_parameters;
    extern ObjectList  global_objectList; 
    extern LightList   global_lightList;
    extern Color       global_background;
    extern Camera      global_camera;
    World the_world;

    global_parameters = Parameters_create(zoom, width, height, xpix, ypix );
    global_objectList = ObjectList_createEmpty();
    global_lightList = LightList_createEmpty();

    global_background = DEFAULT_BACKGROUND;

    yyparse();
    
    the_world = World_create( global_objectList,
                              global_lightList,
                              global_camera,
                              global_background);
    
    return the_world;
}

Bitmap trace( World w, int xpix, int ypix, int reflectionDepth,
              bool noShadowNoReflection )
{
    int x,y;
    
    Bitmap bm = Bitmap_create( xpix, ypix );

    for( y = 0 ; y < ypix ; y++ )
    {
        for( x = 0 ; x < xpix ; x++ )
        {
            Bitmap_setColorAt( bm, World_colorOfPixel( w, x, y,
                                                       reflectionDepth,
                                                       noShadowNoReflection ),
                               x, y );
        }
        fprintf( stderr, "%d%%\r", (int)((scalar)y/(scalar)ypix * 100) );
    }
    return bm;
}
     


int main( int argc, char **argv )
{
    int c;
    extern char *optarg;
    extern int  optind;
    bool        noShadowNoReflection = FALSE;
    /*bool        printTraceTime = FALSE;*/
    scalar      zoom = 1.0;
    long        xpix = 240;
    long        ypix = 240;
    scalar      width = 1.0;
    scalar      height = 1.0;
    char        flagsSet = 0;
    char        numFlagsSet = 0;
    long        errflg = 0;
    long        reflectionDepth = 5;
    /*long        timeExpired;*/

    World       the_world;
    Bitmap      result;
    PPMFile     ppm_out;

    /* Welcome Message. */
    printWelcomeMessage();
    
    while( ( c = getopt(argc, argv, "qtr:z:x:y:w:h:" ) ) != EOF )
    {
	switch( c ) 
	{
	    case 'q':
		noShadowNoReflection = TRUE;
		fprintf( stderr, "- No Shadows or Reflecions will be used\n" );
		break;
	    
	    /*case 't':
		printTraceTime = TRUE;
		fprintf( stderr, "- Trace time will be displayed\n" );
		break; */
		
	    case 'r':
                reflectionDepth = atol( optarg );
		fprintf( stderr, "- reflectionDepth = %ld\n", atol( optarg ) );
                break;
	    case 'z':
		zoom = atof( optarg );
		fprintf( stderr, "- Zoom value = %f\n", atof( optarg ) );
                break;		
	    case 'x':
		xpix = atol( optarg );
		fprintf( stderr, "- xpix = %ld\n", atol( optarg ) );
		flagsSet |= XPIX_MASK;
		numFlagsSet++;
                break;		
	    case 'y':
		ypix = atol( optarg );
		fprintf( stderr, "- ypix = %ld\n", atol( optarg ) );
		flagsSet |= YPIX_MASK;
		numFlagsSet++;
                break;		
	    case 'w':
		width = atof( optarg );
		fprintf( stderr, "- width = %ld\n", atol( optarg ) );
		flagsSet |= WIDTH_MASK;
		numFlagsSet++;
                break;		
	    case 'h':
		height = atof( optarg );
		fprintf( stderr, "- height = %ld\n", atol( optarg ) );
		flagsSet |= HEIGHT_MASK;
		numFlagsSet++;
                break;		
	    case '?':
		errflg++;
		break;
	}
    }
    
    if( errflg > 0 ) /* Any errors in commandline? */
    {
	fprintf( stderr, "%ld Commandline error(s)\n", errflg );
	fprintf( stderr, "usage: tracer <-flags>  files...\n");
	fprintf( stderr, "Available flags are:\n" );
	fprintf( stderr, "-q = No Shadows or Reflecions will be used\n" );
	/*fprintf( stderr, "-t = Trace time will be displayed\n\n" );*/
	fprintf( stderr, "-r <reflectionDepth> = Set the reflectiondepth\n" );
	fprintf( stderr, "-z <zoom> = set zoom factor\n" );
	fprintf( stderr, "-x <xpix> = set # pixels in x-axel\n" );
	fprintf( stderr, "-y <ypix> = set # pixels in y-axel\n" );
	fprintf( stderr, "-w <width> = set picture width\n" );
	fprintf( stderr, "-h <height> = set picture height\n" );
	Error_printErrorAndExit( "" );
    }
    
    /* Check if only three args, if so calculate the last one. */
    if( numFlagsSet == 3 )
    {
	if( !(flagsSet & XPIX_MASK) )
	{
	    xpix = width / height * ypix;
	    fprintf( stderr, "Calculated xpix = %ld\n", xpix );
	}
	else if( !(flagsSet & YPIX_MASK) )
	{
	    ypix = height / width * xpix;
	    fprintf( stderr, "Calculated ypix = %ld\n", ypix );
	}
	else if( !(flagsSet & WIDTH_MASK) )
	{
	    width = (height * xpix) / ypix;
	    fprintf( stderr, "Calculated width = %f\n", width );
	}
	else if( !(flagsSet & HEIGHT_MASK) )
	{
	    height = (width * ypix) / xpix;
	    fprintf( stderr, "Calculated height = %f\n", height );
	}
    }
    
    the_world = parse( zoom, xpix, ypix, width, height );
 
    /* Start the tracing */
    
    result = trace( the_world, xpix, ypix, reflectionDepth,
                    noShadowNoReflection );

    /*timeExpired = Timer_getMilliseconds();*/ /* Stop timer. */
    fprintf( stderr, "100%% - done!\n" );

    ppm_out = PPMFile_openOut( argv[optind], PPM_BINARY );
    PPMFile_writeBitmap( ppm_out, result );
    
    return( 0 ); /* Success */
}
