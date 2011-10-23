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

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "color.h"

namespace Protracer {
  const float EPS = 0.001;
  const Color DEFAULT_BACKGROUND = Color(0, 0, 0);
  const float DEFAULT_ZOOM = 1.0f;
  const float DEFAULT_WORLD_WIDTH = 1.0f;
  const float DEFAULT_WORLD_HEIGHT = 1.0f;
  const unsigned int DEFAULT_PIXEL_WIDTH = 240;
  const unsigned int DEFAULT_PIXEL_HEIGHT = 240;
}

#endif //CONSTANTS_H
