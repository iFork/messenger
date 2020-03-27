/**
 * @file logger.hpp
 * @author annie
 * @brief logger class definition
*/

#ifndef FILE_LOG_HPP
#define FILE_LOG_HPP

#include "colors.hpp"
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include "logger.hpp"

namespace messenger { namespace logger {
    
    class file_log : public logger {
    public:
        /**
         * @brief overload insertion operator 
         */
        template<class T>
        file_log& operator<<(const T& message) noexcept;
        /**
         * @brief constructor 
         */
        file_log(log_level type = log_level::info) noexcept;
        /**
         * @brief copy constructor 
         */
        file_log(const file_log& other) = delete;
        /**
         * @brief move constructor 
         */
        file_log(const file_log&& other) = delete;
         /**
         * @brief assignment operator
         */
        file_log& operator=(const file_log& other) = delete;
        /**
         * @brief move assignment operator
         */
        file_log& operator=(const file_log&& other) = delete;
        
        /**
         * @brief destructor
         */
        ~file_log() noexcept;
    private:
        std::ofstream log_file;
    };

    template<class T>
    file_log& file_log::operator<<(const T& message) noexcept
    {
        if (m_message_level >= log_config.level) {
            log_file << message;
        }
        return *this;
    }
} }

#endif // FILE_LOG_HPP
