#pragma once

#include "core/types.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

class Window
{
public:
    Window();
    sf::RenderWindow& operator*();
    sf::RenderWindow* operator->();
    static uint getFrameLimit();
    static sf::Time getFrameTime();

private:
    void centerWindow();
    
    sf::RenderWindow window;
};
