#pragma once

#include "types/uint.hpp"
#include "systems/isystem.hpp"
#include <entt/fwd.hpp>

class LoopedAnimator : public ISystem
{
public:
    LoopedAnimator(entt::registry&);
    void update(sf::Time) override;

private:
    entt::registry& registry;
    float elapsedSum = 0;
};
