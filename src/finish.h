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

#ifndef FINISH_H
#define FINISH_H

namespace Protracer {

  class Finish {
  public:
    static const float DEFAULT_REFLECTION = 0.0f;
    static const float DEFAULT_DIFFUSION = 1.0f;

    Finish(float diffusion = DEFAULT_DIFFUSION,
	   float reflection = DEFAULT_REFLECTION);
    
    float get_diffusion() const { return diffusion; }
    float get_reflection() const { return reflection; }

  private:
    float diffusion;
    float reflection;
  };

}

#endif //FINISH_H
