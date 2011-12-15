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

#ifndef COLOR_PIGMENT_H
#define COLOR_PIGMENT_H

#include "pigment.h"
#include "color.h"

namespace Protracer {
  
  class ColorPigment : public Pigment {
  public:
    static const unsigned char DEFAULT_RED   = 0; 
    static const unsigned char DEFAULT_GREEN = 0; 
    static const unsigned char DEFAULT_BLUE  = 0; 

    static Color default_color() { return Color(DEFAULT_RED,
                                                DEFAULT_GREEN,
                                                DEFAULT_BLUE); }

    ColorPigment() : color(default_color()) {}
    ColorPigment(const Color& c) : color(c) {}

    bool is_uniform() const { return true; }
    Color get_color() const { return color; }
    Color get_color(float x, float y) const { return color; }

    ColorPigment* copy() const { return new ColorPigment(color); }

  private:
    Color color;
  };

}

#endif // COLOR_PIGMENT_H
