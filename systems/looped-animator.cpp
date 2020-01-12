#include "systems/looped-animator.hpp"
#include "components/animation.hpp"
#include <entt/entity/registry.hpp>

LoopedAnimator::LoopedAnimator(entt::registry& registry, sf::Time frameTime)
    : registry(registry), frameTime(frameTime.asMilliseconds())
{
}

void LoopedAnimator::update(const sf::Time elapsed)
{
    elapsedSum += elapsed.asMilliseconds();
    const auto frameProgress = elapsedSum / frameTime;
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
    
    elapsedSum -= frameProgress * frameTime;
}
