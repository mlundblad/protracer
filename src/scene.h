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

#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "camera.h"
#include "color.h"
#include "vector.h"
#include "object.h"
#include "light.h"
#include "fog.h"

namespace Protracer {
  class Scene {
  public:
    Scene();
    virtual ~Scene();

    // getters
    const Vector& get_c_corner() const { return c_corner; };
    const Vector& get_c_right() const { return c_right; };
    const Vector& get_c_down() const { return c_down; };
    const Camera& get_camera() const { return camera; };
    const std::vector<Object*>& get_objects() const { return objects; };
    const Color& get_background() const { return background; };
    const std::vector<Light>& get_lights() const { return lights; }
    
    Color color_of_pixel(int x, int y, int refl_depth, 
				bool no_shadow_no_reflection) const;

    void add_object(Object* object);
    void add_light(const Light& light);
    void add_fog(Fog* fog);
    void set_camera(const Camera& camera);
    void set_background(const Color& color);

  private:
    std::vector<Object*> objects;
    std::vector<Light>  lights;
    std::vector<Fog*> fogs;
    unsigned int num_fogs;
    Camera      camera;
    Color       background;
    Vector      c_corner;
    Vector      c_right;
    Vector      c_down;
    Vector      c;

    Color color_at_hit_point(int x, int y, const Ray& ray,
				    int refl_depth,
				    bool no_shadow_no_reflection) const;
  };
}
    

#endif //SCENE_H
