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
#include <Magick++/CoderInfo.h>

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
        const Magick::Color& c = image.pixelColor(x, y);

        pixels[(x + y * width) * 3] =
          Magick::Color::scaleQuantumToDouble(c.redQuantum()) *
          Color::COMPONENT_MAX;;
        pixels[(x + y * width) * 3 + 1] =
          Magick::Color::scaleQuantumToDouble(c.greenQuantum()) *
          Color::COMPONENT_MAX;;
        pixels[(x + y * width) * 3 + 2] =
          Magick::Color::scaleQuantumToDouble(c.blueQuantum()) *
          Color::COMPONENT_MAX;;        
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
  Bitmap::write(const std::string& path, const std::string& type) const
  {
    Magick::Image image(width, height, "RGB", Magick::CharPixel, pixels);
    std::string spec = type != "" ? type + ":" + path : path;

    image.write(spec);
  }

  void
  Bitmap::set_pixel(unsigned int x, unsigned int y, const Color& c)
  {
    unsigned int offset = (x + y * width) * 3;
    pixels[offset] = c.get_red();
    pixels[offset + 1] = c.get_green();
    pixels[offset + 2] = c.get_blue();
  }

  bool
  Bitmap::can_write_format(const std::string& format)
  {
    try {
      Magick::CoderInfo info(format);
    
      return info.isWritable();
    } catch (Magick::ErrorOption e) {
      return false;
    }
  }
}
