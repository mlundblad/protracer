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

#ifndef PARAMETERS_H
#define PARAMETERS_H

#include "constants.h"

namespace Protracer {

  class Parameters {
  public:
    Parameters(float zoom = DEFAULT_ZOOM, 
	       float world_width = DEFAULT_WORLD_WIDTH,
	       float world_height = DEFAULT_WORLD_HEIGHT,
	       unsigned int pixel_width = DEFAULT_PIXEL_WIDTH,
	       unsigned int pixel_height = DEFAULT_PIXEL_HEIGHT);

    float get_zoom() const { return zoom; }
    float get_world_width() const { return world_width; }
    float get_world_height() const { return world_height; }
    unsigned int get_pixel_width() const { return pixel_width; }
    unsigned int get_pixel_height() const { return pixel_height; }

  private:
    float zoom;
    float world_width;
    float world_height;
    unsigned int pixel_width;
    unsigned int pixel_height;
  };

}

#endif //PARAMETERS

