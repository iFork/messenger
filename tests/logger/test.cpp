#include "logger/file_log.hpp"
#include "logger/console_log.hpp"
#include <thread>

void log(int t)
{
    using namespace messenger::logger;
    log_config.default_log_file = "my_log.txt";
    // log_config.headers = false;
    // log_config.colored = false;
    // output to file
    file_log(log_level::error) << t << "error text";
    file_log(log_level::warning) << t << "warning text";
    file_log(log_level::info) << t << "info text";
    file_log() << t << "default info text" ;
    // output to terminal
    console_log(log_level::error) << t << "error text";
    console_log(log_level::warning) << t << "warning text";
    console_log(log_level::info) << t << "info text";
    console_log() << t << "default info text" ;
}

int main() 
{
 
    std::thread t1(log, 1);
    std::thread t2(log, 2);
    std::thread t3(log, 3);
    t1.join();
    t2.join();
    t3.join();
}