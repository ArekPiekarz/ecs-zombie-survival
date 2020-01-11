#pragma once

#include <entt/fwd.hpp>

class SurvivorRenderer;
namespace sf { class RenderWindow; }

void runGame(sf::RenderWindow&, entt::registry&, SurvivorRenderer&);
