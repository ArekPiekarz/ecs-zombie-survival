#pragma once

#include <entt/fwd.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class SurvivorRenderer
{
public:
    SurvivorRenderer(sf::RenderTarget&);
    void draw(const entt::registry&);

private:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::RenderTarget& surface;
};
