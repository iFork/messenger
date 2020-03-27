/**
 * @file logger.hpp
 * @author annie
 * @brief logger class definition
*/

#ifndef CONSOLE_LOG_HPP
#define CONSOLE_LOG_HPP

#include "logger.hpp"

namespace messenger { namespace logger {

    class console_log : public logger {
    public:
        /**
         * @brief overload insertion operator 
         */
        template<class T>
        console_log& operator<<(const T& message) noexcept;
        /**
         * @brief constructor 
         */
        console_log(log_level type = log_level::info) noexcept;
        /**
         * @brief copy constructor 
         */
        console_log(const console_log& other) = delete;
        /**
         * @brief move constructor 
         */
        console_log(const console_log&& other) = delete;
         /**
         * @brief assignment operator
         */
        console_log& operator=(const console_log& other) = delete;
        /**
         * @brief move assignment operator
         */
        console_log& operator=(const console_log&& other) = delete;
        /**
         * @brief destructor
         */
        ~console_log() noexcept;
    private:
        template<class T>
        void print_colored_message(const T& message) noexcept;
    };

    template<class T>
    console_log& console_log::operator<<(const T& message) noexcept
    {
        if (m_message_level >= log_config.level) {
            if (log_config.colored) {
                print_colored_message(message);
            } else {
                std::cout << message;
            }
        }
        return *this;
    }
    template<class T>
    void console_log::print_colored_message(const T& message) noexcept
    {
        switch (m_message_level) {
        case log_level::info:
            set_blue(message);
            break;
        case log_level::warning:
            set_yellow(message);
            break;
        case log_level::error:
            set_red(message);
            break;
        default:
            break;
        }
    }

} }

#endif // CONSOLE_LOG_HPP
