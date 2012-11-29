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

#ifndef BITMAP_H
#define BITMAP_H

#include <string>

#include "color.h"

namespace Protracer {
  
  class Bitmap {
  public:
    Bitmap(const std::string& path);
    Bitmap(unsigned int width, unsigned int height);
    Bitmap(const Bitmap& bm);
    ~Bitmap();

    unsigned int get_width() const { return width; }
    unsigned int get_height() const { return height; }

    void write(const std::string& path, const std::string& type = "") const;

    const Color operator() (unsigned int x, unsigned int y) const
    {
      return Color(pixels[(x + y * width) * 3],
                   pixels[(x + y * width) * 3 + 1],
                   pixels[(x + y * width) * 3 + 2]);
    }

    void set_pixel(unsigned int x, unsigned int y, const Color& c);
    
    static bool can_write_format(const std::string& format);

  private:
    unsigned int width;
    unsigned int height;
    unsigned char* pixels;
  };

}

#endif //BITMAP_H
