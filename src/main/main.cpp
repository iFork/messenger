
/**
 * @file src/main/main.cpp
 *
 * @brief Implementation of the entry point for the Instigate build system
 * test application.
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

#include <static_test/static.hpp>
#include <shared_test/shared.hpp>
 
#include <dlfcn.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cassert>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <sys/utsname.h>
#include <algorithm>

// print function pointer definition for dynamic library
typedef void (*print_fun)();

std::string generate_dynamic_library_extension() throw()
{
	struct utsname u; 
	memset(&u, 0, sizeof(u));
	uname(&u);
	assert(0 != u.sysname);
	std::string k(u.sysname);
	std::transform(k.begin(), k.end(), k.begin(), ::tolower);
	if (std::string::npos != k.find("cygwin") || 
		std::string::npos != k.find("mingw")) {
		return "dll";
	} else if (std::string::npos != k.find("darwin")) {
		return "dylib";
	}
	return "so";
}

// Helper function for dynamic library test 
void* load_library(const std::string& s) throw()
{
        assert(! s.empty());
	std::string n = s + ".";
	n = n + generate_dynamic_library_extension();
        void* h = ::dlopen(n.c_str(), RTLD_GLOBAL | RTLD_LAZY);
        if (0 == h) {
                std::cout << "Can't load " << s << std::endl;
                return 0;
        }
        char* e = dlerror();
        if (0 != e) {
                std::cout << e << std::endl;
                return 0;
        }
        return h;
}

/**
 * @brief Calls dynamic library run function.
 *
 * @param a - the name of file on which the data is output. 
 */
void dynamic_one_output_test(const std::string& a) throw()
{
        std::string s = "libdynamic_test";
        void* h = load_library(s);
        if (0 == h) {
                return;
        }
        union {
                void* v;
                void* (*f)(const std::string&);
        } u;
        u.v = ::dlsym(h, "run");
        if (0 == u.v) {
                std::cout << "Can't load symbol run." << std::endl;
                return;
        }
        char* e = dlerror();
        if (0 != e) {
                std::cout << e << std::endl;
                return;
        }
        (*(u.f))(a);
        dlclose(h);
}

/*
 * @brief Prints usage for this test application.
 *
 * @param s - string to be printed in usage description 
 */
void usage(const std::string& s) throw()
{
        assert(! s.empty());
        std::cout << "\nUsage " 
                  << s << ": <OPTION> <FILE_NAME_1> <FILE_NAME_2>\n" 
                  << " <OPTION> is one of the followings:\n"
                  << "\t" << " - static_one_output\n"
                  << "\t" << " - shared_one_output\n"
                  << "\t" << " - dynamic_one_output\n"
                  << "\t" << " - static_two_outputs\n" 
                  << " <FILE_NAME_1> is the name of file in which"
                  << " the output will be stored.\n"
                  << " <FILE_NAME_2> is valid only for static_two_outputs "
                  << "option, which is\n"
                  << " the name of the second file in which "
                  << "the output will be stored." << std::endl;
}

/// This is the entry point for build system test application.
int main(int argc, char** argv)
{
        if (3 > argc) { 
                usage(argv[0]); 
                return 1; 
        }
        namespace M = instigate::mkf_test;
        if ("static_one_output" == std::string(argv[1])) {
                M::static_test::run_one_output_test(argv[2]);
        } else if ("dynamic_one_output" == std::string(argv[1])) {
                dynamic_one_output_test(argv[2]);
        } else if ("shared_one_output" == std::string(argv[1])) {
                M::shared_test::run(argv[2]);
        } else if ("static_two_outputs" == std::string(argv[1])) {
                if (4 > argc) { usage(argv[0]); return 1; }
                M::static_test::run_two_outputs_test(argv[2], argv[3]);
        }
        return 0;
}
