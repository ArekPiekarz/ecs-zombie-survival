#include "setup/texture-loader.hpp"
#include <fmt/format.h>

using fmt::format;
using std::runtime_error;
using std::string_view;

namespace
{

struct TextureLoadError : runtime_error
{
    TextureLoadError(string_view fileName)
     : runtime_error(format("Failed to load {}", fileName))
    {}
};

}

Textures loadTextures(const string_view filePattern, const size_t count)
{
    Textures textures;
    textures.resize(count);
    for (auto i = 0u; i < count; ++i)
    {
        const auto filePath = format(filePattern, i);
        if (not textures[i].loadFromFile(filePath))
        {
            throw TextureLoadError(filePath);
        }
    }
    return textures;
}
