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

#include <stdlib.h>
#include <getopt.h>

#include <iostream>
#include <vector>

#include "config.h"
#include "bitmap.h"
#include "ppm_file.h"
#include "Error.h"
#include "world.h"
#include "object.h"
#include "parameters.h"
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
parse(FILE *input, const Protracer::Parameters& params)
{
    global_parameters = params;
    global_object_list = std::vector<Protracer::Object*>();
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

void
trace(const Protracer::World& w, Protracer::Bitmap& bitmap, int xpix, int ypix,
      int reflectionDepth, bool no_shadow_no_reflection, bool quiet)
{
  int x,y;
  
  for (y = 0 ; y < ypix ; y++ ) {
    for (x = 0 ; x < xpix ; x++ ) {
      bitmap(x, y) = w.color_of_pixel(x, y, reflectionDepth,
				      no_shadow_no_reflection);
    }
    if (!quiet)
      std::cerr << (int)((float)y/(float)ypix * 100) << "%\r";
  }
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

int main(int argc, char **argv)
{
    int c;
    extern char *optarg;
    int  opt_ind = 0;
    bool        no_shadow_no_reflection = false;
    float       zoom = Protracer::DEFAULT_ZOOM;
    long        xpix = Protracer::DEFAULT_PIXEL_WIDTH;
    long        ypix = Protracer::DEFAULT_PIXEL_HEIGHT;
    float       width = Protracer::DEFAULT_WORLD_WIDTH;
    float       height = Protracer::DEFAULT_WORLD_HEIGHT;
    char        flagsSet = 0;
    char        numFlagsSet = 0;
    long        errflg = 0;
    long        reflectionDepth = 5;
    bool        quiet = false;

    Protracer::PPMFile     ppm_out;
    std::string out_file;
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
		no_shadow_no_reflection = true;
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

	        out_file = optarg;
		break;
	    case '?':
		errflg++;
		break;
	    case 'v':
	        print_version();
		exit(0);
		break;
	    case 'q':
	        quiet = true;
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

    Protracer::Parameters params =
      Protracer::Parameters(zoom, width, height, xpix, ypix);

    Protracer::World the_world =
      parse(in_file, params);
 
    /* Start the tracing */
    
    Protracer::Bitmap result = Protracer::Bitmap(xpix, ypix);

    trace(the_world, result, xpix, ypix, reflectionDepth,
	  no_shadow_no_reflection, quiet);

    if (!quiet)
      std::cerr << "100%- done!" << std::endl;

    if (out_file != "")
      ppm_out.open_out(out_file, Protracer::PPMFile::PPM_BINARY);
    else
      ppm_out.open_stdout(Protracer::PPMFile::PPM_BINARY);

    ppm_out.write_bitmap(result);
    
    return 0;
}
