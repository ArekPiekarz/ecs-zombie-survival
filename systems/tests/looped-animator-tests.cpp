#include "systems/looped-animator.hpp"
#include "components/animation.hpp"
#include "constants/animation-constants.hpp"
#include "constants/window-constants.hpp"
#include <entt/entity/registry.hpp>
#include <gtest/gtest.h>
#include <unordered_map>

using std::unordered_map;
using testing::Test;

namespace
{

const auto FRAME_TIME = static_cast<float>(WINDOW_FRAME_TIME.asMilliseconds()) * ANIMATION_FRAME_TIME_SCALE;
const auto HALF_OF_FRAME_TIME = FRAME_TIME / 2;
constexpr auto ANIMATION1 = Animation{Frame{0}, Size{2}};
constexpr auto ANIMATION2 = Animation{Frame{3}, Size{12}};

}

struct LoopedAnimatorTests : Test
{
    LoopedAnimatorTests();
    void assertAnimationsSameAsInitial() const;
    void assertAnimationsForwardedBy(uint progress) const;

    unordered_map<entt::entity, Animation> animationForEntityMap;
    entt::registry registry;
    LoopedAnimator sut{registry};
};

LoopedAnimatorTests::LoopedAnimatorTests()
{
    const auto entity1 = registry.create();
    const auto entity2 = registry.create();
    registry.emplace<Animation>(entity1, ANIMATION1);
    registry.emplace<Animation>(entity2, ANIMATION2);
    animationForEntityMap.emplace(entity1, ANIMATION1);
    animationForEntityMap.emplace(entity2, ANIMATION2);
}

void LoopedAnimatorTests::assertAnimationsSameAsInitial() const
{
    ASSERT_EQ(2, registry.size());
    registry.each([&](const auto entity) {
        ASSERT_TRUE(registry.all_of<Animation>(entity));
        ASSERT_EQ(animationForEntityMap.at(entity), registry.get<Animation>(entity));
    });
}

void LoopedAnimatorTests::assertAnimationsForwardedBy(const uint progress) const
{
    ASSERT_EQ(2, registry.size());
    registry.each([&](const auto entity) {
        ASSERT_TRUE(registry.all_of<Animation>(entity));
        auto expectedAnimation = animationForEntityMap.at(entity);
        expectedAnimation.frame += progress;
        ASSERT_EQ(expectedAnimation, registry.get<Animation>(entity));
    });
}

TEST_F(LoopedAnimatorTests, shouldNotForwardAnimations_whenElapsedTimeIsLessThanFrameTime)
{
    sut.update(sf::milliseconds(static_cast<int>(HALF_OF_FRAME_TIME)));
    assertAnimationsSameAsInitial();
}

TEST_F(LoopedAnimatorTests, shouldForwardAnimationsBy1_whenElapsedTimeEqualsFrameTime)
{
    sut.update(sf::milliseconds(static_cast<int>(FRAME_TIME)));
    assertAnimationsForwardedBy(1);
}

TEST_F(LoopedAnimatorTests, shouldForwardAnimationsBy1_whenElapsedTimeIsBetweenOneAndTwoFrameTimes)
{
    sut.update(sf::milliseconds(static_cast<int>(FRAME_TIME + HALF_OF_FRAME_TIME)));
    assertAnimationsForwardedBy(1);
}

TEST_F(LoopedAnimatorTests, shouldLoopAllAnimations_whenElapsedTimeIsProductOfTheirSizes)
{
    sut.update(sf::milliseconds(static_cast<int>(FRAME_TIME * ANIMATION1.size * ANIMATION2.size)));
    assertAnimationsSameAsInitial();
}
