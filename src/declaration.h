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

#ifndef DECLARATION_H
#define DECLARATION_H

#include <string>
#include <cmath>
#include <map>

#include "object.h"

namespace Protracer {

  class Declaration {
  public:

    enum Type {
      SCALAR,
      VECTOR,
      COLOR,
      OBJECT
    } type;

    union Value {
      float scalar;
      Vector* vector;
      Color* color;
      Object* object;
    } value;

    Declaration(const std::string& name, float scalar);
    Declaration(const std::string& name, const Vector& vector);
    Declaration(const std::string& name, const Color& color); 
    Declaration(const std::string& name, Object* object);

    const std::string get_name() const { return name; }
    const float get_scalar() const { return value.scalar; }
    const Vector& get_vector() const { return *(value.vector); }
    const Color& get_color() const { return *(value.color); }
    const Object* get_object() const { return type == OBJECT ? value.object : 0; }
    Type get_type() const { return type; }
    
    static bool is_defined(const std::string& name);
    static Declaration get_declaration(const std::string& name);
    static void add_global_declaration(Declaration decl);
    static void remove_global_declaration(const std::string& name);

    static std::map<std::string, Declaration> global_declarations;

  private:
    
    std::string name;
  };

}

#endif // DECLARATION_H
