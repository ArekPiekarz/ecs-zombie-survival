#pragma once

#include "types/textures.hpp"
#include <string_view>

Textures loadTextures(std::string_view filePattern, size_t count);
