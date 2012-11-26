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

#include "bitmap.h"

#include <Magick++/Image.h>

#include <iostream>
#include <cstring>

namespace Protracer {
  Bitmap::Bitmap(const std::string& path)
  {
    Magick::Image image(path);

    width = image.columns();
    height = image.rows();
    pixels = new unsigned char[width * height * 3];

    for (int x = 0 ; x < width ; x++) {
      for (int y = 0 ; y < height ; y++) {
        const Color c = image.pixelColor(x, y);
        pixels[(x + y * width) * 3] = c.get_red();
        pixels[(x + y * width) * 3 + 1] = c.get_green();
        pixels[(x + y * width) * 3 + 2] = c.get_blue();        
      }
    }
  }

  Bitmap::Bitmap(unsigned int width, unsigned int height)
  {
    this->width = width;
    this->height = height;
    this->pixels = new unsigned char[width * height * 3];
  }

  Bitmap::Bitmap(const Bitmap& bm)
  {
    if (this != &bm) {
      int size = bm.width * bm.height * 3;

      width = bm.width;
      height = bm.height;
      pixels = new unsigned char[size];
      std::memcpy(pixels, bm.pixels, size);
    }
  }

  Bitmap::~Bitmap()
  {
    delete [] pixels;
  }

  void
  Bitmap::write(const std::string& path, const std::string& type)
  {
    Magick::Image image(width, height, "RGB", Magick::CharPixel, pixels);

    if (type != "") {
      image.magick(type);
    }

    image.write(path);
  }

  void
  Bitmap::set_pixel(unsigned int x, unsigned int y, const Color& c)
  {
    pixels[(x + y * width) * 3] = c.get_red();
    pixels[(x + y * width) * 3 + 1] = c.get_green();
    pixels[(x + y * width) * 3 + 2] = c.get_blue();
  }

}
