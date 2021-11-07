#pragma once

#include <SFML/Window/Event.hpp>
#include <map>
#include <memory>
#include <vector>

class IEventSystem;
class ITimeSystem;

using EventSystems = std::map<sf::Event::EventType, std::unique_ptr<IEventSystem>>;
using TimeSystems = std::vector<std::unique_ptr<ITimeSystem>>;
