#include "maths/radians.hpp"
#include <cmath>


Radians::Radians(float value)
  : value(value)
{}

auto Radians::toDegrees() const -> Degrees
{
    return value * 180 / static_cast<float>(M_PI);
}
