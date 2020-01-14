#include "setup/window.hpp"
#include "constants/window-constants.hpp"

Window::Window()
 : window(sf::VideoMode(800, 600), "ECS Zombie Survival")
{
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(WINDOW_FRAME_LIMIT);
    centerWindow();
}

void Window::centerWindow()
{
    const auto& desktop = sf::VideoMode::getDesktopMode();
    window.setPosition({
        static_cast<int>(desktop.width/2 - window.getSize().x/2),
        static_cast<int>(desktop.height/2 - window.getSize().y/2)});
}

sf::RenderWindow& Window::operator*()
{
    return window;
}

sf::RenderWindow* Window::operator->()
{
    return &window;
}
