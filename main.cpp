#include "constants/animation-constants.hpp"
#include "core/game.hpp"
#include "setup/crash-handler.hpp"
#include "setup/logger-setup.hpp"
#include "setup/survivor-renderer-setup.hpp"
#include "setup/survivor-setup.hpp"
#include "setup/window.hpp"
#include "setup/zombie-renderer-setup.hpp"
#include "setup/zombie-setup.hpp"
#include "systems/aimer.hpp"
#include "systems/looped-animator.hpp"
#include "systems/systems.hpp"
#include <entt/entity/registry.hpp>

using std::make_unique;

int main()
{
    const auto crashHandler = setupCrashHandler();
    setupLogger();
    auto window = Window{};
    auto registry = entt::registry{};

    setupSurvivor(registry);
    setupZombies(registry);

    auto eventSystems = EventSystems{};
    eventSystems.emplace(sf::Event::MouseMoved, make_unique<Aimer>(registry));

    auto timeSystems = TimeSystems{};
    timeSystems.emplace_back(make_unique<LoopedAnimator>(registry));
    timeSystems.emplace_back(makeSurvivorRenderer(registry, *window));
    timeSystems.emplace_back(makeZombieRenderer(registry, *window));

    Game game{*window, eventSystems, timeSystems};
    game.run();
    return 0;
}
