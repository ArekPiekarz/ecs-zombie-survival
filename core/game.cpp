#include "core/game.hpp"
#include "core/logger.hpp"
#include "systems/isystem.hpp"
#include <magic_enum.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

using namespace magic_enum::ostream_operators;

Game::Game(sf::RenderWindow& window, Systems& systems)
    : window(window), systems(systems)
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
        default:
        {
            SPDLOG_DEBUG("Event: {}\n", event.type);
        }
        }
    }
}

void Game::update(const sf::Time elapsed)
{
    for (auto& system: systems)
    {
        system->update(elapsed);
    }
}
