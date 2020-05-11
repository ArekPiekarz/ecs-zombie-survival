#include "setup/zombie-setup.hpp"
#include "components/animation.hpp"
#include "components/position.hpp"
#include "components/rotation.hpp"
#include "components/scale.hpp"
#include "components/zombie.hpp"
#include "constants/animation-constants.hpp"
#include "constants/window-constants.hpp"
#include "constants/zombie-animation-constants.hpp"
#include <entt/entity/registry.hpp>
#include <experimental/array>

using std::experimental::make_array;

namespace
{

struct EntityParams
{
    Position position{};
    Angle angle = 0;
    Frame frame = 0;
};

}

void setupZombies(entt::registry& registry)
{
    const auto zombiesParams = make_array<EntityParams>(
        EntityParams{Position{0.2f,  0.3f},  Angle{20},  Frame{0}},
        EntityParams{Position{0.35f, 0.5f},  Angle{0},   Frame{10}},
        EntityParams{Position{0.25f, 0.8f},  Angle{320}, Frame{20}});

    for (const auto& entry: zombiesParams)
    {
        const auto entity = registry.create();
        registry.emplace<Zombie>(entity);
        registry.emplace<Position>(entity, WINDOW_SIZE.x * entry.position.x, WINDOW_SIZE.y * entry.position.y);
        registry.emplace<Rotation>(entity, entry.angle);
        registry.emplace<Scale>(entity, 1.5f);
        registry.emplace<Animation>(entity, entry.frame, ZOMBIE_IDLE_FRAME_SIZE);
    }
}
