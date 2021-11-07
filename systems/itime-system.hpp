#pragma once

namespace sf { class Time; }

class ITimeSystem
{
public:
    virtual ~ITimeSystem();
    virtual void update(sf::Time) = 0;
};
