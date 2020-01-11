#include "core/game.hpp"
#include "core/logger.hpp"
#include "systems/survivor-renderer.hpp"
#include <magic_enum.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

using namespace magic_enum::ostream_operators;

namespace
{

void draw(sf::RenderWindow& window, entt::registry& registry, SurvivorRenderer& survivorRenderer)
{
    window.clear();
    survivorRenderer.draw(registry);
    window.display();
}

}

void runGame(sf::RenderWindow& window, entt::registry& registry, SurvivorRenderer& renderer)
{
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
            {
                window.close();
                break;
            }
            default:
            {
                SPDLOG_DEBUG("Event: {}\n", event.type);
            }
            }
        }

        draw(window, registry, renderer);
    }
}
