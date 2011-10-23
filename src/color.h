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

#ifndef COLOR_H
#define COLOR_H

namespace Protracer {
  
  // CRTP base class for color expressions
  template <typename E>
  class ColorExpression {
  public:
    unsigned char get_red() const { static_cast<const E&>(*this).get_red(); }
    unsigned char get_green() const { static_cast<const E&>(*this).get_green();}
    unsigned char get_blue() const { static_cast<const E&>(*this).get_blue(); }

    operator E&() { return static_cast<E&>(*this); }
    operator const E&() const { return static_cast<const E&>(*this); }
  };


  class Color : public ColorExpression<Color> {
  public:
    Color() : red(0), green(0), blue(0) {}
    Color(unsigned char red, unsigned char green, unsigned char blue) :
      red(red), green(green), blue(blue) {}

    template <typename E>
    Color(const ColorExpression<E>& expr) {
      const E& c = expr;

      red = c.get_red();
      green = c.get_green();
      blue = c.get_blue();
    }

    unsigned char get_red() const { return red; }
    unsigned char get_green() const { return green; }
    unsigned char get_blue() const { return blue; }

    static const unsigned char COMPONENT_MAX = 255;

  private:
    unsigned char red;
    unsigned char green;
    unsigned char blue;
  };

  template <typename E>
  class ColorShade : public ColorExpression<ColorShade<E> > {
    const E& c;
    float s;
  public:
    ColorShade(const ColorExpression<E>& c, float s) : c(c), s(s) {}
    
    unsigned char get_red() const { return int(c.get_red()) * s >
	Color::COMPONENT_MAX ? Color::COMPONENT_MAX : c.get_red() * s; }
    unsigned char get_green() const { return int(c.get_green()) * s >
	Color::COMPONENT_MAX ? Color::COMPONENT_MAX : c.get_green() * s; }
    unsigned char get_blue() const { return int(c.get_blue()) * s >
	Color::COMPONENT_MAX ? Color::COMPONENT_MAX : c.get_blue() * s; }
  };

  template <typename E1, typename E2>
  class ColorCombine : public ColorExpression<ColorCombine<E1, E2> > {
    const E1& c1;
    const E2& c2;
  public:
    ColorCombine(const ColorExpression<E1>& c1, const ColorExpression<E2>& c2) :
      c1(c1), c2(c2) {}

    unsigned char get_red() const {
      return int(c1.get_red()) + int(c2.get_red()) > Color::COMPONENT_MAX ?
	Color::COMPONENT_MAX : c1.get_red() + c2.get_red(); }
    
    unsigned char get_green() const {
      return int(c1.get_green()) + int(c2.get_green()) > Color::COMPONENT_MAX ?
	Color::COMPONENT_MAX : c1.get_green() + c2.get_green(); }
    
    unsigned char get_blue() const {
      return int(c1.get_blue()) + int(c2.get_blue()) > Color::COMPONENT_MAX ?
	Color::COMPONENT_MAX : c1.get_blue() + c2.get_blue(); }
  };
    
  template <typename E>
  const ColorShade<E>
  operator*(const ColorExpression<E>& c, float s)
  {
    return ColorShade<E>(c, s);
  }

  template <typename E>
  const ColorShade<E>
  operator*(float s, const ColorExpression<E>& c)
  {
    return ColorShade<E>(c, s);
  }

  template <typename E1, typename E2>
  const ColorCombine<E1, E2>
  operator+(const ColorExpression<E1>& c1, const ColorExpression<E2>& c2)
  {
    return ColorCombine<E1, E2>(c1, c2);
  }

}

#endif //COLOR_H
