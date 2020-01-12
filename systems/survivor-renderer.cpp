#include "systems/survivor-renderer.hpp"
#include "components/animation.hpp"
#include "components/flashlight.hpp"
#include "components/position.hpp"
#include "components/survivor.hpp"
#include <entt/entity/registry.hpp>
#include <fmt/format.h>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>
#include <string_view>

using fmt::format;
using std::runtime_error;
using std::string_view;

namespace
{

const auto IMAGE_FILE_PATH = "graphics/survivor/flashlight/idle/survivor-idle_flashlight_{}.png";

struct TextureLoadError : runtime_error
{
    TextureLoadError(string_view fileName)
     : runtime_error(format("Failed to load {}", fileName))
    {}
};

}

SurvivorRenderer::SurvivorRenderer(const entt::registry& registry, sf::RenderTarget& renderTarget)
 : registry(registry), renderTarget(renderTarget)
{
    for (auto i = 0u; i < flashlightIdleTextures.size(); ++i)
    {
        const auto filePath = format(IMAGE_FILE_PATH, i);
        if (not flashlightIdleTextures[i].loadFromFile(filePath))
        {
            throw TextureLoadError(filePath);
        }
    }
}

void SurvivorRenderer::update(sf::Time)
{
    const auto view = registry.view<const Survivor, const Flashlight, const Animation, const Position>();
    for (const auto entity: view)
    {
        const auto& animation = view.get<const Animation>(entity);
        sf::Sprite sprite{flashlightIdleTextures.at(animation.frame)};
        const auto bounds = sprite.getLocalBounds();
        sprite.setOrigin(bounds.width/2, bounds.height/2);
        sprite.setScale(0.5, 0.5);

        const auto& position = view.get<const Position>(entity);
        sprite.setPosition({position.x, position.y});

        renderTarget.draw(sprite);
    }
}
