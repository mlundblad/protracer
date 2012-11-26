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

#include "color.h"

namespace Protracer {
  Color::Color(const Magick::Color& c)
  {
    red = Magick::Color::scaleQuantumToDouble(c.redQuantum()) *
      COMPONENT_MAX;
    green = Magick::Color::scaleQuantumToDouble(c.greenQuantum()) *
      COMPONENT_MAX;
    blue = Magick::Color::scaleQuantumToDouble(c.blueQuantum()) *
      COMPONENT_MAX;
  }

  Color::operator Magick::Color() const
  {
    return Magick::Color(Magick::Color::scaleDoubleToQuantum(double(red) /
							     COMPONENT_MAX),
			 Magick::Color::scaleDoubleToQuantum(double(green) /
							     COMPONENT_MAX),
			 Magick::Color::scaleDoubleToQuantum(double(blue) /
							     COMPONENT_MAX));
  }

}
