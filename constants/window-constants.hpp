#pragma once

#include "types/window-size.hpp"
#include <SFML/System/Time.hpp>

constexpr auto WINDOW_FRAME_LIMIT = 60u;
const auto WINDOW_FRAME_TIME = sf::milliseconds(1000 / WINDOW_FRAME_LIMIT);
const auto WINDOW_SIZE = WindowSize{800, 600};
