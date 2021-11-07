#include "core/game.hpp"
#include "core/logger.hpp"
#include "systems/ievent-system.hpp"
#include "systems/itime-system.hpp"
#include <magic_enum.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

using magic_enum::enum_name;


Game::Game(sf::RenderWindow& window, EventSystems& eventSystems, TimeSystems& timeSystems)
    : window(window), eventSystems(eventSystems), timeSystems(timeSystems)
{
}

void Game::run()
{
    sf::Clock clock;
    while (window.isOpen())
    {
        const auto elapsed = clock.restart();
        window.clear();
        handleEvents();
        update(elapsed);
        window.display();
    }
}

void Game::handleEvents()
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
        case sf::Event::MouseMoved:
        {
            const auto it = eventSystems.find(event.type);
            if (it != eventSystems.end())
            {
                it->second->handle(event);
            }
            break;
        }
        default:
        {
            SPDLOG_DEBUG("Event: {}\n", enum_name(event.type));
        }
        }
    }
}

void Game::update(const sf::Time elapsed)
{
    for (auto& system: timeSystems)
    {
        system->update(elapsed);
    }
}
