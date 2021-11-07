#pragma once

#include "systems/itime-system.hpp"
#include <entt/fwd.hpp>

class LoopedAnimator : public ITimeSystem
{
public:
    LoopedAnimator(entt::registry&);
    void update(sf::Time) override;

private:
    entt::registry& registry;
    float elapsedSum = 0;
};
