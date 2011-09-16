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

#ifndef BITMAP_PIGMENT_H
#define BITMAP_PIGMENT_H

#include "pigment.h"
#include "Bitmap.h"
#include "Color.h"


namespace Protracer {

  class BitmapPigment : public Pigment {
  public:
    BitmapPigment(const Bitmap& b) : bitmap(b) {}
    bool is_uniform() const { return false; }
    Color& get_color() const { return Color(0,0,0); }
    Color& get_color(float x, float y) const;

  private:
    Bitmap bitmap;
  };

}

#endif // BITMAP_PIGMENT_H
