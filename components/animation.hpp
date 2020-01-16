#pragma once

#include "types/frame.hpp"
#include "types/size.hpp"
#include <tuple>

struct Animation
{
    Frame frame = 0;
    Size size = 1;

    auto tied() const
    {
        return std::tie(frame, size);
    }

    bool operator==(const Animation& rhs) const
    {
        return tied() == rhs.tied();
    }
};
