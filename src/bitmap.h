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

#include "Color.h"

namespace Protracer {
  
  class Bitmap {
  public:
    Bitmap(unsigned int width, unsigned int height);
    ~Bitmap();

    unsigned int get_width() const { return width; }
    unsigned int get_height() const { return height; }

    const Color& operator() (unsigned int x, unsigned int y) const
    {
      return pixels[x + y * width];
    }

    Color& operator() (unsigned int x, unsigned int y)
    {
      return pixels[x + y * width];
    }

  private:
    unsigned int width;
    unsigned int height;
    Color* pixels;
  };

}

#endif //BITMAP_H
