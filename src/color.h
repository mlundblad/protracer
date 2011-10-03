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

#ifndef COLOR_H
#define COLOR_H

namespace Protracer {
  
  class Color {
  public:
    Color() : red(0), green(0), blue(0) {}
    Color(unsigned char red, unsigned char green, unsigned char blue) :
      red(red), green(green), blue(blue) {}

    unsigned char get_red() const { return red; }
    unsigned char get_green() const { return green; }
    unsigned char get_blue() const { return blue; }

    static const unsigned char COMPONENT_MAX = 255;

  private:
    unsigned char red;
    unsigned char green;
    unsigned char blue;
  };

  inline Color operator*(const Color& c, float s)
  {
    return Color(int(c.get_red()) * s > Color::Color::COMPONENT_MAX ?
		 Color::COMPONENT_MAX : c.get_red() * s,
		 int(c.get_green()) * s > Color::COMPONENT_MAX ?
		 Color::COMPONENT_MAX : c.get_green() * s,
		 int(c.get_blue()) * s > Color::COMPONENT_MAX ?
		 Color::COMPONENT_MAX : c.get_blue() * s);
  }

  inline Color operator+(const Color& c1, const Color& c2)
  {
    return Color(int(c1.get_red()) + int(c2.get_red()) > Color::COMPONENT_MAX ?
		 Color::COMPONENT_MAX : c1.get_red() + c2.get_red(),
		 int(c1.get_green()) + int(c2.get_green()) > Color::COMPONENT_MAX ?
		 Color::COMPONENT_MAX : c1.get_green() + c2.get_green(),
		 int(c1.get_blue()) + int(c2.get_blue()) > Color::COMPONENT_MAX ?
		 Color::COMPONENT_MAX : c1.get_blue() + c2.get_blue());
  }

}

#endif //COLOR_H
