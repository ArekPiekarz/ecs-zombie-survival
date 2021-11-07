#include "systems/aimer.hpp"
#include "components/position.hpp"
#include "components/rotation.hpp"
#include "components/survivor.hpp"
#include "exceptions/unexpected-event-error.hpp"
#include "maths/radians.hpp"
#include <entt/entity/registry.hpp>
#include <SFML/Window/Event.hpp>
#include <cmath>

const auto EXPECTED_EVENT = sf::Event::MouseMoved;


Aimer::Aimer(entt::registry& registry)
  : registry(registry)
{}

Aimer::~Aimer() = default;

void Aimer::handle(const sf::Event& event)
{
    if (event.type != EXPECTED_EVENT)
    {
        throw UnexpectedEventError(ExpectedEventType(EXPECTED_EVENT), ReceivedEventType(event.type));
    }

    const auto mousePosition = Position{static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y)};
    auto view = registry.view<Survivor, Position, Rotation>();
    for (const auto entity: view)
    {
        const auto& survivorPosition = view.get<Position>(entity);
        auto& rotation = view.get<Rotation>(entity);
        rotation.angle = Radians(atan2f(mousePosition.y - survivorPosition.y, mousePosition.x - survivorPosition.x)).toDegrees();
    }
}
