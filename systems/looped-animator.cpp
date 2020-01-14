#include "systems/looped-animator.hpp"
#include "components/animation.hpp"
#include "constants/animation-constants.hpp"
#include "constants/window-constants.hpp"
#include <entt/entity/registry.hpp>

namespace
{

const auto FRAME_TIME = WINDOW_FRAME_TIME.asMilliseconds() * ANIMATION_FRAME_TIME_SCALE;

}

LoopedAnimator::LoopedAnimator(entt::registry& registry)
    : registry(registry)
{
}

void LoopedAnimator::update(const sf::Time elapsed)
{
    elapsedSum += elapsed.asMilliseconds();
    const auto frameProgress = static_cast<uint>(elapsedSum / FRAME_TIME);
    if (frameProgress == 0)
    {
        return;
    }

    auto view = registry.view<Animation>();
    for (const auto entity: view)
    {
        auto& animation = view.get<Animation>(entity);
        animation.frame = (animation.frame + frameProgress) % animation.size;
    }
    
    elapsedSum -= frameProgress * FRAME_TIME;
}
