#pragma once

#include <entt/fwd.hpp>
#include <memory>

class ITimeSystem;
namespace sf { class RenderTarget; }

std::unique_ptr<ITimeSystem> makeSurvivorRenderer(entt::registry&, sf::RenderTarget&);
