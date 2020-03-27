// /**
//  * @file logger.cpp
//  * @author annie
//  * @brief log class implementation
// */

#include "logger.hpp"
#include <string.h>

namespace messenger { namespace logger {

    log_config_struct log_config = {};

    std::string logger::get_label(log_level type) noexcept
    {
        std::map<log_level, std::string> labels {
            { log_level::error, "ERROR" },
            { log_level::warning, "WARNING" },
            { log_level::info, "INFO" }
        };
        return labels[type];
    }

    std::string logger::get_current_time() noexcept
    {
          time_t my_time = time(NULL);
          return strtok(ctime(&my_time), "\n");   
    }
} }
