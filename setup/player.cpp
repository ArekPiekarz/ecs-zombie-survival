#include "setup/player.hpp"
#include "components/animation.hpp"
#include "components/flashlight.hpp"
#include "components/position.hpp"
#include "components/survivor.hpp"
#include "constants/survivor-animation-constants.hpp"
#include <entt/entity/registry.hpp>

constexpr auto FIRST_FRAME = 0;

void setupPlayer(entt::registry& registry, const WindowSize& windowSize)
{
    const auto entity = registry.create();
    registry.assign<Survivor>(entity);
    const auto position = Position{windowSize.x / 2.0f, windowSize.y / 2.0f};
    registry.assign<Position>(entity, position);
    registry.assign<Flashlight>(entity);
    registry.assign<Animation>(entity, FIRST_FRAME, SURVIVOR_FLASHLIGHT_IDLE_FRAME_SIZE);
}
