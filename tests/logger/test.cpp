#include "logger.hpp"

int main() 
{
    using namespace messenger::logger;
    log_config.headers = true;
    log(log_level::error) << "error" << 5;
    log() << "default message will be info type" << 5;
}