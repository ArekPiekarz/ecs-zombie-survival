#pragma once

#include "constants/survivor-animation-constants.hpp"
#include "systems/isystem.hpp"
#include <entt/fwd.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace sf{ class Time; }

class SurvivorRenderer : public ISystem
{
public:
    SurvivorRenderer(const entt::registry&, sf::RenderTarget&);
    void update(sf::Time) override;

private:
    std::array<sf::Texture, SURVIVOR_FLASHLIGHT_IDLE_FRAME_SIZE> flashlightIdleTextures; 
    const entt::registry& registry;
    sf::RenderTarget& renderTarget;
};
