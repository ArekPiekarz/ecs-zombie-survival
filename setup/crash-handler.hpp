#pragma once

#include <backward.hpp>

auto setupCrashHandler()
{
    return backward::SignalHandling{};
}
