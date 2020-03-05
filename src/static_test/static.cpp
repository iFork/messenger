
/**
 * @file src/static_test/static.cpp
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

#include "static.hpp"

#include <fstream>
#include <cassert>

namespace instigate {
        namespace  mkf_test {
                namespace static_test {

                        void run_one_output_test(const std::string& a) throw()
                        {
                                std::ofstream x(a.c_str()); assert(x.good());
                                x << "Static one output test";
                        }

                        void run_two_outputs_test(const std::string& a, 
                                                const std::string& b) throw()
                        {
                                std::ofstream x(a.c_str()); assert(x.good());
                                x << "Static two outputs test - output 1";
                                x.close();
                                x.open(b.c_str()); assert(x.good());
                                x << "Static two outputs test - output 2";
                        }
                } // static_test
        } // mkf_test
}
