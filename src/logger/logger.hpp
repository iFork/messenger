/**
 * @file logger.hpp
 * @author annie
 * @brief logger class definition
*/

#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "colors.hpp"
#include <map>
#include <string>
#include <iostream>

namespace messenger { namespace logger {
    /**
     * @brief log level: info(0), warning(1), error(2)
     */
    enum class log_level {
        info,
        warning, 
        error 
    };
    /**
     * @brief struct to configure logger settings
     */
    struct log_config_struct {
        bool headers = false;
        bool colored = false;
        log_level level = log_level::info;
    };
    /**
     * @brief configuration object, will be defined in cpp file
     */
    extern log_config_struct log_config;
    
    class log {
    public:
        /**
         * @brief overload insertion operator 
         */
        template<class T>
        log& operator<<(const T &msg) {
            if(m_message_level >= log_config.level) {
                std::cout << msg;
                m_opened = true;
            }
            return *this;
        }
        /**
         * @brief constructor 
         */
        log(log_level type = log_level::info);
        /**
         * @brief copy constructor 
         */
        log(const log& other) = delete;
        /**
         * @brief move constructor 
         */
        log(const log&& other) = delete;
         /**
         * @brief assignment operator
         */
        log& operator=(const log& other) = delete;
        /**
         * @brief move assignment operator
         */
        log& operator=(const log&& other) = delete;
        ~log();
    private:
        bool m_opened = false;
        log_level m_message_level = log_level::info;
        /**
         * @brief get label depending of log level
         */
        std::string get_label(log_level type);
    };
} }

#endif
