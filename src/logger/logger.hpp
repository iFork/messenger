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
        bool headers = true;
        bool colored = true;
        log_level level = log_level::info;
        std::string default_log_file = "log.txt";
    };
    /**
     * @brief configuration object, will be defined in cpp file
     */
    extern log_config_struct log_config;
    
    class logger {
    public:
        /**
         * @brief copy constructor 
         */
        logger(const logger& other) = delete;
        /**
         * @brief move constructor 
         */
        logger(const logger&& other) = delete;
         /**
         * @brief assignment operator
         */
        logger& operator=(const logger& other) = delete;
        /**
         * @brief move assignment operator
         */
        logger& operator=(const logger&& other) = delete;
        
    protected:
        log_level m_message_level = log_level::info;
        /**
         * @brief get label depending of log level
         */
        std::string get_label(log_level type) noexcept;
        std::string get_current_time() noexcept;
        /**
         * @brief constructor 
         */
        logger() = default;
        /**
         * @brief destructor
         */
        ~logger() = default;
    };
} }

#endif
