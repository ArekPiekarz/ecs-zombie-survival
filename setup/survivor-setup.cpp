#include "setup/survivor-setup.hpp"
#include "components/animation.hpp"
#include "components/flashlight.hpp"
#include "components/position.hpp"
#include "components/rotation.hpp"
#include "components/scale.hpp"
#include "components/survivor.hpp"
#include "constants/animation-constants.hpp"
#include "constants/survivor-animation-constants.hpp"
#include "constants/window-constants.hpp"
#include <entt/entity/registry.hpp>

void setupSurvivor(entt::registry& registry)
{
    const auto entity = registry.create();
    registry.emplace<Survivor>(entity);
    registry.emplace<Flashlight>(entity);
    registry.emplace<Position>(entity, WINDOW_SIZE.x / 2.0f + 50, WINDOW_SIZE.y / 2.0f);
    registry.emplace<Animation>(entity, FIRST_FRAME, SURVIVOR_FLASHLIGHT_IDLE_FRAME_SIZE);
    registry.emplace<Rotation>(entity, 180);
    registry.emplace<Scale>(entity, 0.5);
}
