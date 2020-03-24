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

/**
 * @class class logger
*/
class logger 
{
public: 
    enum class log_level {
        error, 
        warning, 
        info
    };
private:
    log_level m_log_level = log_level::info;
    std::map<log_level, std::string> labels {
        { log_level::error, " [ERROR] " },
        { log_level::warning, " [WARNING] " },
        { log_level::info, " [INFO] " }
    };
public:
    /**
     * @brief change m_log_level
     */
    void set_level(log_level level);
    /**
     * @brief warning log
     */
    void warn(const std::string& message);
    /**
     * @brief error log
     */
    void error(const std::string& message);
    /**
     * @brief info log
     */
    void info(const std::string& message);
    /**
     * @brief Destructor
     */
    ~logger() noexcept;
};

#endif // LOGGER_HPP
