#include "setup/zombie-renderer-setup.hpp"
#include "components/animation.hpp"
#include "components/position.hpp"
#include "components/rotation.hpp"
#include "components/scale.hpp"
#include "components/zombie.hpp"
#include "constants/zombie-animation-constants.hpp"
#include "setup/texture-loader.hpp"
#include "systems/sprite-renderer.hpp"
#include "types/textures.hpp"
#include <entt/entity/registry.hpp>
#include <entt/entity/runtime_view.hpp>

using std::make_unique;
using std::move;
using std::unique_ptr;
using std::vector;

namespace
{

constexpr auto TEXTURE_FILE_PATH_PATTERN = "graphics/zombie/idle/idle00{:0>2}.png";

}

unique_ptr<ISystem> makeZombieRenderer(entt::registry& registry, sf::RenderTarget& renderTarget)
{
    auto components = vector<entt::component>{
        registry.type<Zombie>(),
        registry.type<Animation>(),
        registry.type<Position>(),
        registry.type<Rotation>(),
        registry.type<Scale>()};
    auto textures = loadTextures(TEXTURE_FILE_PATH_PATTERN, ZOMBIE_IDLE_FRAME_SIZE);
    return make_unique<SpriteRenderer>(registry, move(components), renderTarget, move(textures));
}
