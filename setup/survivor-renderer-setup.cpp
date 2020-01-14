#include "setup/survivor-renderer-setup.hpp"
#include "components/animation.hpp"
#include "components/position.hpp"
#include "components/rotation.hpp"
#include "components/scale.hpp"
#include "components/survivor.hpp"
#include "constants/survivor-animation-constants.hpp"
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

constexpr auto TEXTURE_FILE_PATH_PATTERN = "graphics/survivor/flashlight/idle/survivor-idle_flashlight_{}.png";

}

unique_ptr<ISystem> makeSurvivorRenderer(entt::registry& registry, sf::RenderTarget& renderTarget)
{
    auto components = vector<entt::component>{
        registry.type<Survivor>(),
        registry.type<Animation>(),
        registry.type<Position>(),
        registry.type<Rotation>(),
        registry.type<Scale>()};
    auto textures = loadTextures(TEXTURE_FILE_PATH_PATTERN, SURVIVOR_FLASHLIGHT_IDLE_FRAME_SIZE);
    return make_unique<SpriteRenderer>(registry, move(components), renderTarget, move(textures));
}
