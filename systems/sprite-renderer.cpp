#include "systems/sprite-renderer.hpp"
#include "components/animation.hpp"
#include "components/position.hpp"
#include "components/rotation.hpp"
#include "components/scale.hpp"
#include <entt/entity/registry.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>

SpriteRenderer::SpriteRenderer(
    const entt::registry& registry,
    const ComponentIds componentIds,
    sf::RenderTarget& renderTarget,
    const Textures textures)
 : registry(registry),
   componentIds(componentIds),
   renderTarget(renderTarget),
   textures(textures)
{
}

void SpriteRenderer::update(sf::Time)
{
    const auto view = registry.runtime_view(componentIds.cbegin(), componentIds.cend());
    for (const auto entity: view)
    {
        const auto& animation = registry.get<const Animation>(entity);
        auto sprite = sf::Sprite{textures.at(animation.frame)};
        
        const auto bounds = sprite.getLocalBounds();
        sprite.setOrigin(bounds.width/2, bounds.height/2);

        const auto& position = registry.get<const Position>(entity);
        sprite.setPosition({position.x, position.y});

        const auto& rotation = registry.get<const Rotation>(entity);
        sprite.setRotation(rotation.angle);

        const auto& scale = registry.get<const Scale>(entity);
        sprite.setScale(scale.value, scale.value);

        renderTarget.draw(sprite);
    }
}
