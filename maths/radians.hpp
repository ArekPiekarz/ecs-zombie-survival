#pragma once

#include "maths/degrees.hpp"


class Radians
{
public:
    Radians(float value);
    auto toDegrees() const -> Degrees;

    float value;
};
