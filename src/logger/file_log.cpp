// /**
//  * @file logger.cpp
//  * @author annie
//  * @brief log class implementation
// */

#include "logger.hpp"
#include <string.h>
#include <iomanip>
#include <mutex>
#include "file_log.hpp"

namespace messenger { namespace logger {

    std::mutex file_mutex;

    file_log::file_log(log_level type) noexcept
    {
        m_message_level = type;
        if (!log_file.is_open()) {
            log_file.open(log_config.default_log_file, std::ios::app);
        }
        file_mutex.lock();
        if (log_config.headers) {
            operator << (std::left);
            operator << (std::setw(26));
            operator << (get_current_time());
            operator << (std::left);
            operator << (std::setw(9));
            operator << (get_label(type));
        }
    }

    file_log::~file_log() noexcept
    {
        operator << ("\n");
        if (log_file.is_open()) {
            log_file.close();
        }
        file_mutex.unlock();
    }
} }
