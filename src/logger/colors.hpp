/**
 * @file colors.hpp
 * @author annie
 * @brief header file to color terminal output
*/

#ifndef COLORS_HPP
#define COLORS_HPP

/**
 * codes that change the color of terminal output 
*/

#define RESET_TEXT "\x1B[0m"
#define RED  "\x1B[31m"
#define YELLOW "\x1B[33m"
#define BLUE  "\x1B[34m"

/**
 * change the color and then reset it back
*/

#define SET_RED(str) RED + str + RESET_TEXT
#define SET_YELLOW(str) YELLOW + str + RESET_TEXT
#define SET_BLUE(str) BLUE + str + RESET_TEXT


#endif // COLORS_HPP