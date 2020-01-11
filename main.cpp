#include "core/game.hpp"
#include "setup/crash-handler.hpp"
#include "setup/logger-setup.hpp"
#include "setup/player.hpp"
#include "setup/window.hpp"
#include "systems/survivor-renderer.hpp"
#include <entt/entity/registry.hpp>

int main()
{
    const auto crashHandler = setupCrashHandler();
    setupLogger();
    auto window = Window{};
    auto registry = entt::registry{};
    setupPlayer(registry, window->getSize());
    auto renderer = SurvivorRenderer{*window};

    runGame(*window, registry, renderer);
    return 0;
}
