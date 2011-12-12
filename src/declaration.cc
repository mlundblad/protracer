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

#include "declaration.h"
#include <iostream>

namespace Protracer {

  std::map<std::string, Declaration> Declaration::global_declarations =
    std::map<std::string, Declaration>();

  Declaration::Declaration(const std::string& name, float scalar)
  {
    type = SCALAR;
    this->name = name; 
    value.scalar = scalar;
  }

  Declaration::Declaration(const std::string& name, const Vector& vector)
  {
    type = VECTOR;
    this->name = name;
    value.vector = new Vector(vector);
  }

  Declaration::Declaration(const std::string& name, const Color& color)
  {
    type = COLOR;
    this->name = name;
    value.color = new Color(color);
  }


  Declaration::Declaration(const std::string& name, Object* object)
  {
    type = OBJECT;
    this->name = name;
    value.object = object;
  }

  bool
  Declaration::is_defined(const std::string& name)
  {
    return global_declarations.find(name) != global_declarations.end();
  }
  
  Declaration
  Declaration::get_declaration(const std::string& name)
  {
    return (global_declarations.find(name))->second;
  }

  void
  Declaration::add_global_declaration(Declaration decl)
  {
    if (is_defined(decl.get_name())) {
      Declaration d = get_declaration(decl.get_name());

      // if it's a heap-allocated object, delete it
      if (d.get_type() == OBJECT)
	delete d.get_object();
      else if (d.get_type() == VECTOR)
	delete d.value.vector;
      else if (d.get_type() == COLOR)
	delete d.value.color;
    }

    global_declarations.insert(std::pair<std::string, Declaration>(decl.get_name(),
								   decl));
  }

  void
  Declaration::remove_global_declaration(const std::string& name)
  {
    Declaration d = get_declaration(name);

    if (d.get_type() == OBJECT)
      delete d.get_object();
    else if (d.get_type() == VECTOR)
      delete d.value.vector;
    else if (d.get_type() == COLOR)
      delete d.value.color;

    global_declarations.erase(name);
  }

}
