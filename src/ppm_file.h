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

#ifndef PPM_FILE_H
#define PPM_FILE_H

#include <string>
#include <stdio.h>

#include "Bitmap.h"

namespace Protracer {

  static unsigned int MAX_COLOR_VALUE = 255;
  static std::string MAGIC_ASCII = "P3";
  static std::string MAGIC_BINARY = "P6";
  
  class PPMFile {
  public:
    enum Mode {
      PPM_ASCII,
      PPM_BINARY
    };

    // open file for input
    void open_in(const std::string& file_name);

    // open file for output
    void open_out(const std::string& file_name, Mode mode);

    // open for output on stdout
    void open_stdout(Mode mode);

    void close();

    Bitmap read_bitmap();
    void write_bitmap(const Bitmap& bitmap);
    

  private:
    FILE* file;
    Mode mode;
  };
}

#endif //PPM_FILE_H
