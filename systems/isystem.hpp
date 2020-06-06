#pragma once

namespace sf { class Time; }

class ISystem
{
public:
    virtual ~ISystem();
    virtual void update(sf::Time) = 0;
};
