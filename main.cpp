#include "constants/animation-constants.hpp"
#include "core/game.hpp"
#include "setup/crash-handler.hpp"
#include "setup/logger-setup.hpp"
#include "setup/player.hpp"
#include "setup/window.hpp"
#include "systems/looped-animator.hpp"
#include "systems/survivor-renderer.hpp"
#include "systems/systems.hpp"
#include <entt/entity/registry.hpp>

using std::make_unique;

int main()
{
    const auto crashHandler = setupCrashHandler();
    setupLogger();
    auto window = Window{};
    auto registry = entt::registry{};
    setupPlayer(registry, window->getSize());

    auto systems = Systems{};
    systems.emplace_back(make_unique<LoopedAnimator>(registry, window.getFrameTime() * ANIMATION_FRAME_TIME_SCALE));
    systems.emplace_back(make_unique<SurvivorRenderer>(registry, *window));

    Game game{*window, systems};
    game.run();
    return 0;
}
