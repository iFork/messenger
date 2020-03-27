/**
 * @file colors.hpp
 * @author annie
 * @brief header file to color terminal output
*/

#ifndef COLORS_HPP
#define COLORS_HPP

#include <iostream>

namespace messenger { namespace logger {

    /**
     * codes that change the color of terminal output 
    */

    #define RESET_TEXT "\x1B[0m"
    #define RED  "\x1B[31m"
    #define YELLOW "\x1B[33m"
    #define BLUE  "\x1B[34m"

    /**
     * change the colors and then reset it back
    */
    template<typename T>
    void set_red(const T& message) 
    {
        std::cout << RED << message << RESET_TEXT;
    }

    template<typename T>
    void set_yellow(const T& message) 
    {
        std::cout << YELLOW << message << RESET_TEXT;
    }

    template<typename T>
    void set_blue(const T& message) 
    {
        std::cout << BLUE << message << RESET_TEXT;
    }
}}

#endif // COLORS_HPP