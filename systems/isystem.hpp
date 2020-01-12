#pragma once

namespace sf { class Time; }

class ISystem
{
public:
    virtual ~ISystem() = default;
    virtual void update(sf::Time) = 0;
};
