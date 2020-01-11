#include "systems/survivor-renderer.hpp"
#include "components/position.hpp"
#include "components/survivor.hpp"
#include <entt/entity/registry.hpp>
#include <fmt/format.h>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string_view>

using fmt::format;
using std::runtime_error;
using std::string_view;

namespace
{

const auto IMAGE_FILE_PATH = "graphics/survivor/flashlight/idle/survivor-idle_flashlight_0.png";

struct TextureLoadError : runtime_error
{
    TextureLoadError(string_view fileName)
     : runtime_error(format("Failed to load {}", fileName))
    {}
};

}

SurvivorRenderer::SurvivorRenderer(sf::RenderTarget& surface)
 : surface(surface)
{
    if (not texture.loadFromFile(IMAGE_FILE_PATH))
    {
        throw TextureLoadError(IMAGE_FILE_PATH);
    }

    sprite.setTexture(texture);
    sprite.setScale(0.5, 0.5);
    const auto bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width/2, bounds.height/2);
}

void SurvivorRenderer::draw(const entt::registry& registry)
{
    const auto view = registry.view<const Survivor, const Position>();
    for (const auto entity: view)
    {
        const auto& position = view.get<const Position>(entity);
        sprite.setPosition({position.x, position.y});
        surface.draw(sprite);
    }
}
