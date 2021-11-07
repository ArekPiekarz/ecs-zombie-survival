#pragma once

#include <SFML/Window/Event.hpp>
#include <stdexcept>


struct ExpectedEventType
{
    sf::Event::EventType value;
};

struct ReceivedEventType
{
    sf::Event::EventType value;
};

class UnexpectedEventError : public std::invalid_argument
{
public:
    UnexpectedEventError(ExpectedEventType, ReceivedEventType);
};
