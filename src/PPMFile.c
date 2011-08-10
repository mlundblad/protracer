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
|  File: PPMFile.c                                                        |
|                                                                         |
|  Functions for using the PPM file format                                |
|                                                                         |
\*************************************************************************/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "PPMFile.h"
#include "Color.h"
#include "Error.h"


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



PPMFile PPMFile_openIn(const char *filename)
{
    PPMFile file;
    
    file.file = fopen(filename, "r");
    if(file.file == NULL)
    {
        Error_printErrorAndExit("Can't open PPM-file for input");
    }
    return file;
}

PPMFile PPMFile_openOut(const char *filename, PPMMode mode)
{
    PPMFile file;

    file.file = fopen(filename, "w");
    if(file.file == NULL)
    {
        Error_printErrorAndExit("Can't open PPM-file for output");
    }
    file.mode = mode;
    return file;
}

PPMFile PPMFile_openStdOut(PPMMode mode)
{
    PPMFile file;

    file.file = stdout;
    if(file.file == NULL)
    {
        Error_printErrorAndExit("Can't open PPM-file for output on stdout");
    }
    file.mode = mode;
    return file;
}



void PPMFile_close( PPMFile file )
{
    if( file.file != NULL )
    {
        fclose( file.file );
    }
}

Bitmap PPMFile_readBitmap( PPMFile file )
{
    PPMMode         mode = PPM_ASCII; /* unnesesary, but "chokes" a warning */
    unsigned int    width, height, depth;
    unsigned int    x, y;
    char            temp[256];  /* some temp. storage */
    Color_component red, green, blue;
    Color           col;
    Bitmap          bm;

    
    /* read PPM-header */

    temp[0] = fgetc(file.file);
    temp[1] = fgetc(file.file);

    if(temp[0] == 'P' && temp[1] == '3')
    {
        mode = PPM_ASCII;
    }
    else if(temp[0] == 'P' && temp[1] == '6')
    {
        mode = PPM_BINARY;
    }
    
    else
    {
        Error_printErrorAndExit("Not a PPM file");
    }

    /* read width */
    skip_ws_and_read_until_ws(file.file, temp);
    /*fprintf(stderr, "w: %s\n", temp );*/
    width = strtol(temp, NULL, 10);

    /* read height */
    skip_ws_and_read_until_ws(file.file, temp);
    height = strtol(temp, NULL, 10);

    /* read (and ignore) depth */
    skip_ws_and_read_until_ws(file.file, temp);
    depth = strtol(temp, NULL, 10);

    
    bm = Bitmap_create(width, height);

    if(mode == PPM_ASCII)
    {
        for(y = 0 ; y < height ; y++)
        {
            for(x = 0 ; x < width ; x++)
            {
                /*ERROR_PRINT_DEBUG(temp);*/
                skip_ws_and_read_until_ws(file.file, temp);
                red = strtol(temp, NULL, 10);
                
                skip_ws_and_read_until_ws(file.file, temp);
                green = strtol(temp, NULL, 10);
                
                skip_ws_and_read_until_ws(file.file, temp);
                blue = strtol(temp, NULL, 10);
                
                /*ERROR_PRINT_DEBUG("One pixel read");*/
                col = Color_createFromRGB(red, green, blue);
                /*ERROR_PRINT_DEBUG("Color created");*/
                fprintf(stderr, "x: %d y: %d\n", x, y);
                Bitmap_setColorAt(bm, col, x, y);
                /*ERROR_PRINT_DEBUG("Pixel set in bitmap");*/

            }
        }
    }

    else
    {
        for(y = 0 ; y < height ; y++)
        {
            for(x = 0 ; x < width ; x++)
            {
                if(fread(&red, 1, sizeof(Color_component), file.file) == 0)
                    Error_printErrorAndExit("Unable to read from PPM file");

                if(fread(&green, 1, sizeof(Color_component), file.file) == 0)
                    Error_printErrorAndExit("Unable to read from PPM file");
                
                if(fread(&blue, 1, sizeof(Color_component), file.file) == 0)
                    Error_printErrorAndExit("Unable to read from PPM file");

                col = Color_createFromRGB(red, green, blue);
                Bitmap_setColorAt(bm, col, x, y);
            }
        }
    }

    return bm;
}

void PPMFile_writeBitmap(PPMFile file, Bitmap bm)
{
    int             x,y;
    int             width =  Bitmap_width(bm);
    int             height = Bitmap_height(bm);
    Color           col;
    Color_component temp;
    
    if(file.mode == PPM_ASCII)
    {
        fprintf( file.file, "%s\n", PPM_MAGIC_ASCII);
    }
    else
    {
        fprintf( file.file, "%s\n", PPM_MAGIC_BINARY);
    }
    fputs( "#********************************************\n", file.file );
    fputs( "#* PRO-Tracer                               *\n", file.file );
    fputs( "#* Who knew nice code could be this fast... *\n", file.file );
    fputs( "#********************************************\n\n", file.file );
    
    fprintf(file.file, "%d %d\n", width, height);
    fprintf(file.file, "%d\n", PPM_MAX_COLOR_VALUE);

    if(file.mode == PPM_ASCII)
    {
        for(y = 0 ; y < height ; y++)
        {
            for(x = 0 ; x < width ; x++)
            {
                /*sprintf(buffer, "Write: width: %d height: %d", 
                  width, height);*/
                /*ERROR_PRINT_DEBUG(buffer);*/

                col = Bitmap_colorAt(bm, x, y);
                if(fprintf(file.file, "%d %d %d\n", Color_red(col),
                                                    Color_green(col),
                                                    Color_blue(col)  ) == EOF)
                    Error_printErrorAndExit("Unable to write to file");
            }
        }
    }
    else /*binary*/
    {
        for(y = 0 ; y < height ; y++)
        {
            for(x = 0 ; x < width ; x++)
            {
                col = Bitmap_colorAt(bm, x, y);
                temp = Color_red(col);
                if(fwrite(&temp, 1, sizeof(Color_component), file.file) == 0)
                    Error_printErrorAndExit("Unable to write to file");

                temp = Color_green(col);
                if(fwrite(&temp, 1, sizeof(Color_component), file.file) == 0)
                    Error_printErrorAndExit("Unable to write to file");

                temp = Color_blue(col);
                if(fwrite(&temp, 1, sizeof(Color_component), file.file) == 0)
                    Error_printErrorAndExit("Unable to write to file");
            }
        }
    }
}


    
    
