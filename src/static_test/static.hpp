
#ifndef INSTIGATE_MKF_TEST_STATIC_TEST_STATIC_HPP 
#define INSTIGATE_MKF_TEST_STATIC_TEST_STATIC_HPP

/**
 * @file src/static_test/static.hpp
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

#include <string>

/**
 * The top namespace for Instigate build system test application.
 */
namespace instigate {
        namespace mkf_test {
                namespace static_test {
                        void run_one_output_test(const std::string& a) throw();
                        void run_two_outputs_test(const std::string& a,
                                        const std::string& b) throw();
                } // static_test
        } // mkf_test
}

#endif // INSTIGATE_MKF_TEST_STATIC_TEST_STATIC_HPP 
