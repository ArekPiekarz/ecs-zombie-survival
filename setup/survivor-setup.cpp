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
    registry.assign<Survivor>(entity);
    registry.assign<Flashlight>(entity);
    registry.assign<Position>(entity, WINDOW_SIZE.x / 2.0f + 50, WINDOW_SIZE.y / 2.0f);
    registry.assign<Animation>(entity, FIRST_FRAME, SURVIVOR_FLASHLIGHT_IDLE_FRAME_SIZE);
    registry.assign<Rotation>(entity, 180);
    registry.assign<Scale>(entity, 0.5);
}
