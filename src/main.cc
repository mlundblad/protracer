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
#include <string.h>

#include <iostream>
#include <vector>

#include "config.h"

#include "Scalar.h"

#include "Bitmap.h"
#include "PPMFile.h"
#include "Error.h"
#include "world.h"

#include "ObjectMods.h"
#include "Finish.h"
#include "SphereOptions.h"

#include "Parameters.h"

#include "light.h"
#include "parser.h"
#include "constants.h"


#define XPIX_MASK 0x1
#define YPIX_MASK 0x2
#define WIDTH_MASK 0x4
#define HEIGHT_MASK 0x8

static void print_version(void)
{
  std::cerr << PACKAGE << " " << VERSION << std::endl;
}

Protracer::World
parse(FILE *input, scalar zoom, long xpix, long ypix, scalar width,
	    scalar height)
{
    extern int yyparse();

    extern FILE        *yyin;
    extern Parameters  global_parameters;
    extern std::vector<Object>  global_object_list; 
    extern std::vector<Protracer::Light>   global_light_list;
    extern Color       global_background;
    extern Protracer::Camera      global_camera;

    global_parameters = Parameters_create(zoom, width, height, xpix, ypix );
    global_object_list = std::vector<Object>();
    global_light_list = std::vector<Protracer::Light>();

    global_background = Protracer::DEFAULT_BACKGROUND;

    yyin = input;
    yyparse();
    
    Protracer::World the_world = Protracer::World(global_object_list,
				 global_light_list,
				 global_camera,
				 global_background);
    
    return the_world;
}

Bitmap
trace( const Protracer::World& w, int xpix, int ypix, int reflectionDepth,
              bool noShadowNoReflection, bool quiet )
{
    int x,y;
    
    Bitmap bm = Bitmap_create( xpix, ypix );

    for (y = 0 ; y < ypix ; y++ ) {
        for (x = 0 ; x < xpix ; x++ ) {
            Bitmap_setColorAt(bm, w.color_of_pixel(x, y,
						   reflectionDepth,
						   noShadowNoReflection),
			      x, y);
        }
	if (!quiet)
	  std::cerr << (int)((scalar)y/(scalar)ypix * 100) << "%\r";
    }
    return bm;
}
     
static void usage(void)
{
  std::cerr << "   usage: " << PACKAGE << " [options] [input file]" 
	    << std::endl
            << std::endl
	    << "   -n, --no-shadows                          "
            << "no shadows or reflecions will be"
	    << "                                                used"
            << std::endl
            << "   -r, --reflection-depth=REFLECTION_DEPTH   "
	    << "set the reflection depth" << std::endl
            << "   -z, --zoom-factor=ZOOM                    "
	    << "set zoom factor" << std::endl
            << "   -x, --x-pixels=X_PIX                      "
	    << "set the pixel width of the" << std::endl
	    << "                                             resulting image"
            << std::endl
            << "   -y, --y-pixels=Y_PIX                      "
	    << "set the pixel height of the" << std::endl
	    << "                                             resulting image"
            << std::endl
            << "   -w, --width=WIDTH                         "
	    << "set picture width" << std::endl
            << "   -h, --height=HEIGHT                       "
	    << "set picture height" << std::endl
            << "   -o, --output=FILE                         "
	    << "set output file" << std::endl
            << "       --help                                "
	    << "print this help" << std::endl
            << "       --version                             "
	    << "print version information" << std::endl
            << "   -q, --quiet                               "
	    << "don't print a progress meter" << std::endl
            << std::endl
            << "If no input file is given, input is read from stdin."
            << std::endl
            << "Likewise, if no output file is given, output "
            << "(in PPM format) is written to" << std::endl << "stdout"
            << std::endl;
}

static void
usage_and_exit(void)
{
  usage();
  exit(-1);
}

int main( int argc, char **argv )
{
    int c;
    extern char *optarg;
    int  opt_ind = 0;
    bool        noShadowNoReflection = FALSE;
    scalar      zoom = Protracer::DEFAULT_ZOOM;
    long        xpix = Protracer::DEFAULT_PIXEL_WIDTH;
    long        ypix = Protracer::DEFAULT_PIXEL_HEIGHT;
    scalar      width = Protracer::DEFAULT_WORLD_WIDTH;
    scalar      height = Protracer::DEFAULT_WORLD_HEIGHT;
    char        flagsSet = 0;
    char        numFlagsSet = 0;
    long        errflg = 0;
    long        reflectionDepth = 5;
    bool        quiet = FALSE;

    Bitmap      result;
    PPMFile     ppm_out;
    char        *out_file = NULL;
    FILE        *in_file;

    static struct option long_options[] =
      {
	{"no-shadows", no_argument, 0, 'n'},
	{"reflection-depth", required_argument, 0, 'r'},
	{"zoom-value", required_argument, 0, 'z'},
	{"x-pixels", required_argument, 0, 'x'},
	{"y-pixels", required_argument, 0, 'y'},
	{"width", required_argument, 0, 'w'},
	{"height", required_argument, 0, 'h'},
	{"output-file", required_argument, 0, 'o'},
	{"help", no_argument, 0, '?'},
	{"version", no_argument, 0, 'v'},
	{"quiet", no_argument, 0, 'q'},
	{0, 0, 0, 0}
      };

    while ((c = getopt_long(argc, argv, "qnr:z:x:y:w:h:e:o:", long_options,
			    &opt_ind) ) != EOF ) {
      switch (c) {
	    case 'n':
		noShadowNoReflection = TRUE;
		break;
	    case 'r':
	        if (!optarg)
		  usage_and_exit();

                reflectionDepth = atol( optarg );
                break;
	    case 'z':
	        if (!optarg)
		  usage_and_exit();

		zoom = atof( optarg );
                break;		
	    case 'x':
	        if (!optarg)
		  usage_and_exit();

		xpix = atol( optarg );
		flagsSet |= XPIX_MASK;
		numFlagsSet++;
                break;		
	    case 'y':
	        if (!optarg)
		  usage_and_exit();

		ypix = atol( optarg );
		flagsSet |= YPIX_MASK;
		numFlagsSet++;
                break;		
	    case 'w':
	        if (!optarg)
		  usage_and_exit();

		width = atof( optarg );
		flagsSet |= WIDTH_MASK;
		numFlagsSet++;
                break;		
	    case 'h':
	        if (!optarg)
		  usage_and_exit();

		height = atof( optarg );
		flagsSet |= HEIGHT_MASK;
		numFlagsSet++;
                break;
	    case 'o':
	        if (!optarg)
		  usage_and_exit();

	        out_file = strdup(optarg);
		break;
	    case '?':
		errflg++;
		break;
	    case 'v':
	        print_version();
		exit(0);
		break;
	    case 'q':
	        quiet = TRUE;
		break;
	}
    }
    
    if( errflg > 0 ) /* Any errors in commandline? */
    {
      usage();
      exit(0);
    }
    
    /* Check if only three args, if so calculate the last one. */
    if( numFlagsSet == 3 )
    {
	if (!(flagsSet & XPIX_MASK)) {
	    xpix = width / height * ypix;
	    std::cerr << "Calculated xpix = " << xpix << std::endl;
	} else if (!(flagsSet & YPIX_MASK)) {
	    ypix = height / width * xpix;
	    std::cerr << "Calculated ypix = " << ypix << std::endl;
	} else if (!(flagsSet & WIDTH_MASK)) {
	    width = (height * xpix) / ypix;
	    std::cerr << "Calculated width = " << width << std::endl;
	} else if (!(flagsSet & HEIGHT_MASK)) {
	    height = (width * ypix) / xpix;
	    std::cerr << "Calculated height = " << height << std::endl;
	}
    }
    
    /* open in file */
    if (argv[optind] != NULL) {
      in_file = fopen(argv[optind], "r");
    } else {
      in_file = stdin;
    }

    Protracer::World the_world =
      parse(in_file, zoom, xpix, ypix, width, height );
 
    /* Start the tracing */
    
    result = trace(the_world, xpix, ypix, reflectionDepth,
		   noShadowNoReflection, quiet);

    if (!quiet)
      std::cerr << "100%% - done!" << std::endl;

    if (out_file != NULL)
      ppm_out = PPMFile_openOut(out_file, PPM_BINARY);
    else
      ppm_out = PPMFile_openStdOut(PPM_BINARY);

    PPMFile_writeBitmap(ppm_out, result);
    
    return 0;
}
