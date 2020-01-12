#pragma once

#include "core/types.hpp"
#include "systems/isystem.hpp"
#include <entt/fwd.hpp>
#include <SFML/System/Time.hpp>

class LoopedAnimator : public ISystem
{
public:
    LoopedAnimator(entt::registry&, sf::Time frameTime);
    void update(sf::Time) override;

private:
    entt::registry& registry;
    const uint frameTime;
    uint elapsedSum = 0;
};
