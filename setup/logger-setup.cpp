#include "setup/logger-setup.hpp"
#include "core/logger.hpp"

void setupLogger()
{
    spdlog::set_level(spdlog::level::trace);
    // pattern is: time + colored log level + source location + function name + message
    spdlog::set_pattern("[%H:%M:%S.%e] [%^%l%$] [%s:%#] [%!] %v");
}
