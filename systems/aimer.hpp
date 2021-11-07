#pragma once

#include "systems/ievent-system.hpp"
#include <entt/entity/fwd.hpp>


class Aimer : public IEventSystem
{
public:
    Aimer(entt::registry&);
    ~Aimer() override;
    void handle(const sf::Event&) override;

private:
    entt::registry& registry;
};
