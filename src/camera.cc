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
#include "Vector.h"

namespace Protracer {
  Camera::Camera()
  {
    // default camera located at origo, looking in the positive z-direction
    // oriented with picture-wise up in the positive y-direction
    this->location = Vector_createFromCartesian(0, 0, 0);
    this->look_at = Vector_createFromCartesian(0, 0, 1);
    this->up = Vector_createFromCartesian(0, 1, 0);
    this->zoom = DEFAULT_ZOOM;
    this->world_width = DEFAULT_WORLD_WIDTH;
    this->world_height = DEFAULT_WORLD_HEIGHT;
    this->pixel_width = DEFAULT_PIXEL_WIDTH;
    this->pixel_height = DEFAULT_PIXEL_HEIGHT;
  }

  Camera::Camera(const Vector& location, const Vector& look_at,
		 const Vector& up,
		 float zoom, float world_width, float world_height,
		 int pixel_width, int pixel_height)
  {
    this->location = location;
    this->look_at = look_at;
    this->up = up;
    this->zoom = zoom;
    this->world_width = world_width;
    this->world_height = world_height;
    this->pixel_width = pixel_width;
    this->pixel_height = pixel_height;
  }
}
