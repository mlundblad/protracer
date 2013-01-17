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

#include "camera.h"

#include "constants.h"
#include "vector.h"

namespace Protracer {

  // default camera located at origo, looking in the positive z-direction
  // oriented with picture-wise up in the positive y-direction
  Camera::Camera() :
    location(0),
    look_at(0, 0, 1),
    up(0, 1, 0),
    zoom(DEFAULT_ZOOM),
    world_width(DEFAULT_WORLD_WIDTH),
    world_height(DEFAULT_WORLD_HEIGHT),
    pixel_width(DEFAULT_PIXEL_WIDTH),
    pixel_height(DEFAULT_PIXEL_HEIGHT)
  {
  }

  Camera::Camera(const Vector& location, const Vector& look_at,
		 const Vector& up,
		 float zoom, float world_width, float world_height,
		 int pixel_width, int pixel_height) :
    location(location),
    look_at(look_at),
    up(up),
    zoom(zoom),
    world_width(world_width),
    world_height(world_height),
    pixel_width(pixel_width),
    pixel_height(pixel_height)
  {
  }

  void
  Camera::translate(const Vector& v)
  {
    location += v;
    look_at += v;
  }

  void
  Camera::rotate(const Vector& v)
  {
    location = location.rotate(v);
    look_at = look_at.rotate(v);
    up = up.rotate(v);
  }

}
