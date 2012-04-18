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

#ifndef CAMERA_H
#define CAMERA_H

#include "item.h"
#include "vector.h"

namespace Protracer {

  class Camera : public Item {
  public:
    Camera();
    Camera(const Vector& location, const Vector& look_at, const Vector& up,
	   float zoom, float world_width, float world_height,
	   int pixel_width, int pixel_height);

    const Vector& get_location() const { return location; }
    const Vector& get_look_at() const { return look_at; }
    const Vector& get_up() const { return up; }
    float get_zoom() const { return zoom; }
    float get_world_width() const { return world_width; }
    float get_world_height() const { return world_height; }
    unsigned int get_pixel_width() const { return pixel_width; }
    unsigned int get_pixel_height() const { return pixel_height; }

    virtual void translate(const Vector& v);
    virtual void rotate(const Vector& v);

  private:
    Vector location;
    Vector look_at;
    Vector up;
    float zoom;
    float world_width;
    float world_height;
    unsigned int pixel_width;
    unsigned int pixel_height;

  };
}

#endif //CAMERA_H
