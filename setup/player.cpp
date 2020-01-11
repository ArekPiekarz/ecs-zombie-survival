#include "setup/player.hpp"
#include "components/position.hpp"
#include "components/survivor.hpp"
#include <entt/entity/registry.hpp>

void setupPlayer(entt::registry& registry, const WindowSize& windowSize)
{
    const auto entity = registry.create();
    registry.assign<Survivor>(entity);
    const auto position = Position{windowSize.x / 2.0f, windowSize.y / 2.0f};
    registry.assign<Position>(entity, position);
}
