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

#include "ppm_file.h"
#include "exception.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

namespace Protracer {


  /* parses comment until LF, the next char read after this call will be the
     char after the LF */
  static void parse_comment( FILE *file )
  {
    int c;

    c = fgetc(file);
    
    while(c != (int)'\n')
      {
        c = fgetc(file);
      }
  }

  /* local function that skips evetual white space chars,
     and if the character after WS is a # the following line is regarded as a
     comment, characters after that is put in a buffer, until WS
  */



  static void skip_ws_and_read_until_ws(FILE *file, char *buffer)
  {
    int  i = 0;
    int  c;
    bool doneWS = FALSE;

    c = fgetc(file);

    while(!doneWS)
      {
        /* parse leading WS */
        
        while(isspace(c))
	  {
            /*ERROR_PRINT_DEBUG("parsing WS");*/
            c = fgetc(file);
	  }
        
        if( c == (int)'#')
	  {
            parse_comment(file);
            c = fgetc(file);
	  }        

        if(!isspace(c) && c != (int)'#')
	  doneWS = TRUE;
      }

    /* parse data */
    while(!isspace(c))
      {
        /*ERROR_PRINT_DEBUG("Reading data");*/
        buffer[i] = c;
        c = fgetc(file);
        i++;
      }
    /*ERROR_PRINT_DEBUG("Done reading data");*/
    buffer[i] = '\0';
  }


  
  void
  PPMFile::open_in(const std::string& file_name)
  {
    file = fopen(file_name.c_str(), "r");
    if (file == NULL) {
      throw new Exception("Could not open PPM file for input: " + file_name);
    }
  }

  void
  PPMFile::open_out(const std::string& file_name, Mode mode)
  {
    file = fopen(file_name.c_str(), "w");
    if (file == NULL) {
      throw new Exception("Could not open PPM file for output: " + file_name);
    }
    this->mode = mode;
  }

  void
  PPMFile::open_stdout(Mode mode)
  {
    file = stdout;
    if (file == NULL) {
      throw new Exception("Could not open PPM file for output on stdout");
    }
    this->mode = mode;
  }

  void
  PPMFile::close()
  {
    if (file != NULL && file != stdout)
      fclose(file);
  }

  Bitmap
  PPMFile::read_bitmap()
  {
    Mode         mode = PPM_ASCII; /* unnesesary, but "chokes" a warning */
    unsigned int    width, height, depth;
    char            temp[256];  /* some temp. storage */
    Bitmap          bm;

    /* read PPM-header */

    temp[0] = fgetc(file);
    temp[1] = fgetc(file);

    if (temp[0] == 'P' && temp[1] == '3')
      mode = PPM_ASCII;
    else if(temp[0] == 'P' && temp[1] == '6')
      mode = PPM_BINARY;    
    else
      throw new Exception("Not a PPM file");

    /* read width */
    skip_ws_and_read_until_ws(file, temp);
    /*fprintf(stderr, "w: %s\n", temp );*/
    width = strtol(temp, NULL, 10);

    /* read height */
    skip_ws_and_read_until_ws(file, temp);
    height = strtol(temp, NULL, 10);

    /* read (and ignore) depth */
    skip_ws_and_read_until_ws(file, temp);
    depth = strtol(temp, NULL, 10);

    
    bm = Bitmap_create(width, height);

    if (mode == PPM_ASCII) {
        for(int y = 0 ; y < height ; y++) {
            for(int x = 0 ; x < width ; x++) {
                /*ERROR_PRINT_DEBUG(temp);*/
                skip_ws_and_read_until_ws(file, temp);
                Color_component red = strtol(temp, NULL, 10);
                
                skip_ws_and_read_until_ws(file, temp);
                Color_component green = strtol(temp, NULL, 10);
                
                skip_ws_and_read_until_ws(file, temp);
                Color_component blue = strtol(temp, NULL, 10);
                
                /*ERROR_PRINT_DEBUG("One pixel read");*/
                Color col = Color_createFromRGB(red, green, blue);
                /*ERROR_PRINT_DEBUG("Color created");*/
                fprintf(stderr, "x: %d y: %d\n", x, y);
                Bitmap_setColorAt(bm, col, x, y);
                /*ERROR_PRINT_DEBUG("Pixel set in bitmap");*/

            }
        }
    } else {
        for (int y = 0 ; y < height ; y++) {
            for(int x = 0 ; x < width ; x++) {
	      Color_component red, green, blue;
	      if (fread(&red, 1, sizeof(Color_component), file) == 0)
		throw new Exception("Unable to read from PPM file");
	      
	      if(fread(&green, 1, sizeof(Color_component), file) == 0)
		throw new Exception("Unable to read from PPM file");
	      
	      if(fread(&blue, 1, sizeof(Color_component), file) == 0)
		throw new Exception("Unable to read from PPM file");
	      
	      Color col = Color_createFromRGB(red, green, blue);
	      Bitmap_setColorAt(bm, col, x, y);
            }
        }
    }

    return bm;
  }

  void
  PPMFile::write_bitmap(const Bitmap& bitmap)
  {
    int             width =  Bitmap_width(bitmap);
    int             height = Bitmap_height(bitmap);
    Color_component temp;
    
    if (mode == PPM_ASCII) {
      fprintf(file, "%s\n", MAGIC_ASCII.c_str());
    } else {
      fprintf(file, "%s\n", MAGIC_BINARY.c_str());
    }

    fputs( "#********************************************\n", file );
    fputs( "#* PRO-Tracer                               *\n", file );
    fputs( "#* Who knew nice code could be this fast... *\n", file );
    fputs( "#********************************************\n\n", file );
    
    fprintf(file, "%d %d\n", width, height);
    fprintf(file, "%d\n", MAX_COLOR_VALUE);

    if (mode == PPM_ASCII) {
        for (int y = 0 ; y < height ; y++) {
            for (int x = 0 ; x < width ; x++) {
                Color col = Bitmap_colorAt(bitmap, x, y);
                if (fprintf(file, "%d %d %d\n", Color_red(col),
                                                    Color_green(col),
                                                    Color_blue(col)  ) == EOF)
		  throw new Exception("Unable to write to PPM file");
            }
        }
    } else /*binary*/ {
      for (int y = 0 ; y < height ; y++) {
	for(int x = 0 ; x < width ; x++) {
	  Color col = Bitmap_colorAt(bitmap, x, y);
	  Color_component temp = Color_red(col);
          
	  if (fwrite(&temp, 1, sizeof(Color_component), file) == 0)
	    throw new Exception("Unable to write to PPM file");
	  
	  temp = Color_green(col);
	  if (fwrite(&temp, 1, sizeof(Color_component), file) == 0)
	    throw new Exception("Unable to write to file");
	  
	  temp = Color_blue(col);
	  if (fwrite(&temp, 1, sizeof(Color_component), file) == 0)
	    throw new Exception("Unable to write to file");
	}
      }
    }
  }
}
