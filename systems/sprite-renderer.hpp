#pragma once

#include "systems/isystem.hpp"
#include "types/component-ids.hpp"
#include "types/textures.hpp"
#include <entt/fwd.hpp>

namespace sf{ class Time; }

class SpriteRenderer : public ISystem
{
public:
    SpriteRenderer(const entt::registry&, ComponentIds, sf::RenderTarget&, Textures);
    void update(sf::Time) override;

private:
    const entt::registry& registry;
    const ComponentIds componentIds;
    sf::RenderTarget& renderTarget;
    const Textures textures; 
};
