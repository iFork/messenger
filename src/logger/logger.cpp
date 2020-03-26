// /**
//  * @file logger.cpp
//  * @author annie
//  * @brief log class implementation
// */

#include "logger.hpp"

namespace messenger { namespace logger {
    log_config_struct log_config = {};
    std::string log::get_label(log_level type) 
    {
        std::map<log_level, std::string> labels {
            { log_level::error, "ERROR" },
            { log_level::warning, "WARNING" },
            { log_level::info, "INFO" }
        };
        return labels[type];
    }
    log::log(log_level type) 
    {
        m_message_level = type;
        if(log_config.headers) {
            operator << ("["+get_label(type)+"]");
        }
    }
    log::~log() 
    {
        if(m_opened) {
            std::cout << std::endl;
        }
        m_opened = false;
    }
} }
