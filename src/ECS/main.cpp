#include </opt/homebrew/Cellar/sfml/2.6.1/include/SFML/Graphics.hpp>
#include "Component/Health/Health.hh"
#include "Core/Core.hpp"
#include "Component/Position/Position.hpp"
#include "Component/Velocity/Velocity.hh"
#include "System/Velocity/Velocity.hpp"
#include "System/Velocity/Velocity.hpp"

std::size_t ECS::ComponentManager::ComponentTypeRegistry::nextTypeIndex = 0;

int main(void)
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML ECS - Moving Squares");

    ECS::Core::Core core;
    core.registerComponent<ECS::Components::Position>();
    core.registerComponent<ECS::Components::Velocity>();
    core.registerComponent<ECS::Components::Health>();

    auto velocitySystem = core.registerSystem<ECS::Systems::SystemVelocity>();

    Signature velocitySystemSignature;
    velocitySystemSignature.set(ECS::ComponentManager::ComponentTypeRegistry::getTypeId<ECS::Components::Position>());
    velocitySystemSignature.set(ECS::ComponentManager::ComponentTypeRegistry::getTypeId<ECS::Components::Velocity>());
    core.setSystemSignature<ECS::Systems::SystemVelocity>(velocitySystemSignature);

    std::size_t entity1 = core.createEntity();
    std::size_t entity2 = core.createEntity();

    core.addComponent(entity1, ECS::Components::Position{400.0f, 100.0f});
    core.addComponent(entity1, ECS::Components::Velocity{0.001f, 0.001f});

    core.addComponent(entity2, ECS::Components::Position{400.0f, 100.0f});
    core.addComponent(entity2, ECS::Components::Velocity{0.001f, -0.001f});

    sf::RectangleShape square1(sf::Vector2f(50.0f, 50.0f));
    square1.setFillColor(sf::Color::Red);

    sf::RectangleShape square2(sf::Vector2f(50.0f, 50.0f));
    square2.setFillColor(sf::Color::Blue);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        std::vector<std::size_t> entities = core.getEntitiesWithSignature(velocitySystemSignature);
        velocitySystem->update(core.getComponents<ECS::Components::Position>(),
                               core.getComponents<ECS::Components::Velocity>(),
                               entities);

        auto &pos1 = core.getComponent<ECS::Components::Position>(entity1);
        square1.setPosition(pos1.getX(), pos1.getY());

        auto &pos2 = core.getComponent<ECS::Components::Position>(entity2);
        square2.setPosition(pos2.getX(), pos2.getY());

        window.clear();

        window.draw(square1);
        window.draw(square2);

        window.display();
    }

    return 0;
}
