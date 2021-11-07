#pragma once

namespace sf { class Event; }

class IEventSystem
{
public:
    virtual ~IEventSystem();
    virtual void handle(const sf::Event&) = 0;
};
