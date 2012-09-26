/* -*- mode: C++; indent-tabs-mode: nil; c-basic-offset: 2  -*- */
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
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <iostream>
#include <vector>
#include <thread>

#include "config.h"
#include "bitmap.h"
#include "ppm_file.h"
#include "scene.h"
#include "object.h"
#include "parameters.h"
#include "light.h"
#include "parser.h"
#include "constants.h"
#include "exception.h"


#define XPIX_MASK 0x1
#define YPIX_MASK 0x2
#define WIDTH_MASK 0x4
#define HEIGHT_MASK 0x8

static void print_version()
{
  std::cerr << PACKAGE << " " << VERSION << std::endl;
}

void
parse(FILE *input, Protracer::Scene& scene, const Protracer::Parameters& params)
{
    global_parameters = params;
    global_background = Protracer::DEFAULT_BACKGROUND;
    global_scene = &scene;

    yyin = input;
    yyparse();

    // set background (this is not set from within the parser, since we want
    // to get the default one incase none was set in the scene definition)
    scene.set_background(global_background);
}

void
trace(const Protracer::Scene* scene, Protracer::Bitmap* bitmap,
      int thread_id, int num_threads, int xpix, int ypix,
      int reflectionDepth, bool no_shadow_no_reflection, bool quiet)
{
  int y;
  Protracer::Bitmap& bm = *bitmap;
  
  std::cerr << "Running thread #" << thread_id << std::endl;

  for (y = thread_id ; y < ypix ; y += num_threads) {
    for (int x = 0 ; x < xpix ; x++ ) {
      bm(x, y) = scene->color_of_pixel(x, y, reflectionDepth,
                                       no_shadow_no_reflection);
    }

    if (!quiet && thread_id == 0)
      std::cerr << (int)((float)y/(float)ypix * 100) << "%\r";
  }

  std::cerr << "Thread #" << thread_id << " finished." << std::endl;
}

static void usage()
{
  std::cerr << "   usage: " << PACKAGE << " [options] [input file]" 
	    << std::endl
            << std::endl
	    << "   -n, --no-shadows                          "
            << "no shadows or reflections will be"
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
            << "   -t, --threads                             "
            << "number of threads to run" << std::endl
            << "                                             "
            << "(defaults to the number of CPU cores)" << std::endl
            << std::endl
            << "If input is redirected (piped) to the program "
            << "no input file is required to be"
            << std::endl
            << "specified."
            << std::endl
            << "If no output file is given, output "
            << "(in PPM format) is written to stdout"
            << std::endl;
}

static void
usage_and_exit()
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
    char        flags_set = 0;
    char        num_flags_set = 0;
    long        errflg = 0;
    long        reflection_depth = 5;
    bool        quiet = false;
    int num_threads = 0;

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
        {"threads", required_argument, 0, 't'},
	{0, 0, 0, 0}
      };

    while ((c = getopt_long(argc, argv, "qnr:z:x:y:w:h:e:o:t:", long_options,
			    &opt_ind) ) != EOF ) {
      switch (c) {
	    case 'n':
		no_shadow_no_reflection = true;
		break;
	    case 'r':
	        if (!optarg)
		  usage_and_exit();

		reflection_depth = atol( optarg );
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
		flags_set |= XPIX_MASK;
		num_flags_set++;
                break;	
	    case 'y':
	        if (!optarg)
		  usage_and_exit();

		ypix = atol( optarg );
		flags_set |= YPIX_MASK;
		num_flags_set++;
                break;	
	    case 'w':
	        if (!optarg)
		  usage_and_exit();

		width = atof( optarg );
		flags_set |= WIDTH_MASK;
		num_flags_set++;
                break;	
	    case 'h':
	        if (!optarg)
		  usage_and_exit();

		height = atof( optarg );
		flags_set |= HEIGHT_MASK;
		num_flags_set++;
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
            case 't':
              if (!optarg)
                usage_and_exit();

              num_threads = atoi(optarg);
              break;
	}
    }
    
    if (errflg > 0) {
      usage();
      exit(0);
    }
    
    /* Check if only three args, if so calculate the last one. */
    if (num_flags_set == 3) {
	if (!(flags_set & XPIX_MASK)) {
	    xpix = width / height * ypix;
	    std::cerr << "Calculated xpix = " << xpix << std::endl;
	} else if (!(flags_set & YPIX_MASK)) {
	    ypix = height / width * xpix;
	    std::cerr << "Calculated ypix = " << ypix << std::endl;
	} else if (!(flags_set & WIDTH_MASK)) {
	    width = (height * xpix) / ypix;
	    std::cerr << "Calculated width = " << width << std::endl;
	} else if (!(flags_set & HEIGHT_MASK)) {
	    height = (width * ypix) / xpix;
	    std::cerr << "Calculated height = " << height << std::endl;
	}
    }
    
    /* open in file */
    if (argv[optind] != NULL) {
      in_file = fopen(argv[optind], "r");

      if (in_file == 0) {
        std::cerr << "Could not read \"" << argv[optind] << "\": "
                  << strerror(errno) << std::endl;
        exit(-1);
      }
    } else {
      // if running interactively without giving an input file, show usage
      // instead of "getting stuck" waiting for input, this way it will still work
      // to pipe input
      if (isatty(STDIN_FILENO)) {
        usage();
        exit(0);
      }

      in_file = stdin;
    }

    try {
      Protracer::Parameters params =
        Protracer::Parameters(zoom, width, height, xpix, ypix);
      Protracer::Scene scene;

      parse(in_file, scene, params);

      /* Start the tracing */      
      Protracer::Bitmap result = Protracer::Bitmap(xpix, ypix);
      
      // if number of threads wasn't manually set, try to base on
      // number of physical cores
      if (num_threads == 0) {
        num_threads = std::thread::hardware_concurrency();
        if (num_threads == 0) {
          num_threads = 1;
        }

        if (!quiet) {
          std::cerr << "Using " << num_threads << " threads." << std::endl;
        }
      }

      std::vector<std::thread> threads;

      for (int thread_id = 0 ; thread_id < num_threads ; thread_id++) {
        std::cerr << "Creating thread " << thread_id << std::endl;
        threads.emplace_back(trace, &scene, &result, 
                             thread_id, num_threads,xpix, ypix,
                             reflection_depth,
                             no_shadow_no_reflection, quiet);
      }

      for (std::thread& thread : threads) {
        thread.join();
      }

      if (!quiet)
        std::cerr << "100%- done!" << std::endl;
      
      if (out_file != "")
	ppm_out.open_out(out_file, Protracer::PPMFile::PPM_BINARY);
      else
	ppm_out.open_stdout(Protracer::PPMFile::PPM_BINARY);
      
      ppm_out.write_bitmap(result);
    } catch (Protracer::Exception* e) {
      std::cerr << "Error occured: " << e->what() << std::endl;
      return -1;
    }

    return 0;
}
