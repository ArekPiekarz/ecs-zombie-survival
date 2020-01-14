#pragma once

#include <entt/fwd.hpp>
#include <memory>

class ISystem;
namespace sf { class RenderTarget; }

std::unique_ptr<ISystem> makeZombieRenderer(entt::registry&, sf::RenderTarget&);
