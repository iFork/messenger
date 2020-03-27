// /**
//  * @file logger.cpp
//  * @author annie
//  * @brief log class implementation
// */

#include "console_log.hpp"
#include <string.h>
#include <iomanip>
#include <mutex>

namespace messenger { namespace logger {

    std::mutex console_mutex;

    console_log::console_log(log_level type) noexcept
    {
        m_message_level = type;
        console_mutex.lock();
        if (log_config.headers) {
            operator << ("[" + get_label(type) + "]");
        }
    }
    
    console_log::~console_log() noexcept
    {
        std::cout << std::endl;
        console_mutex.unlock();
    }
} }
