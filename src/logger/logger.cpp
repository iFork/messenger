/**
 * @file logger.cpp
 * @author annie
 * @brief logger class implementation
*/

#include "logger.hpp"
#include "colors.hpp"
#include <iostream>
#include <cassert>

void logger::set_level(log_level level) 
{
    m_log_level = level;
}

void logger::error(const std::string& message) 
{
    assert(!message.empty());
    if (m_log_level >= log_level::error) {
        std::cerr << labels[log_level::error] 
                  << SET_RED(message) 
                  << std::endl;
    }
}

void logger::warn(const std::string& message) 
{
    assert(!message.empty());
    if (m_log_level >= log_level::warning) {
        std::cout << labels[log_level::warning] 
                  << SET_YELLOW(message) 
                  << std::endl;
    }
}

void logger::info(const std::string& message) 
{
    assert(!message.empty());
    if (m_log_level >= log_level::info) {
        std::cout << labels[log_level::info] 
                  << SET_BLUE(message) 
                  << std::endl;
    }
}

logger::~logger() noexcept
{
}
