#pragma once

#include "systems/systems.hpp"

namespace sf
{
class RenderWindow;
class Time;
}

class Game
{
public:
    Game(sf::RenderWindow&, Systems&);
    void run();

private:
    void handleEvents();
    void update(sf::Time);

    sf::RenderWindow& window;
    Systems& systems;
};
