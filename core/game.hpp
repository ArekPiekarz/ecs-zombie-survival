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
    Game(sf::RenderWindow&, EventSystems&, TimeSystems&);
    void run();

private:
    void handleEvents();
    void update(sf::Time);

    sf::RenderWindow& window;
    EventSystems& eventSystems;
    TimeSystems& timeSystems;
};
