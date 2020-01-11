#pragma once

#include <entt/fwd.hpp>
#include <SFML/System/Vector2.hpp>

using WindowSize = sf::Vector2u;

void setupPlayer(entt::registry&, const WindowSize&);
