
/**
 * @file src/shared_test/shared.cpp
 *
 * Copyright © 2005-2010 Instigate CJSC, Armenia
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 * 
 */

#include "shared.hpp"
#include <cassert>
#include <fstream>

namespace instigate {
namespace mkf_test {
namespace shared_test {

void run(const std::string& a) throw()
{
        std::ofstream x(a.c_str()); assert(x.good());
        x << "Shared one output test";
}

}
}
}
