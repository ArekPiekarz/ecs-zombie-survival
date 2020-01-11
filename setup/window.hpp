#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

class Window
{
public:
    Window();
    sf::RenderWindow& operator*();
    sf::RenderWindow* operator->();

private:
    void centerWindow();
    
    sf::RenderWindow window;
};
