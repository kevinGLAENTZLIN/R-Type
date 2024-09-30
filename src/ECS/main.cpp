#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>

#include "Core/Core.hpp"

#include "Component/Health/Health.hh"
#include "Component/Position/Position.hpp"
#include "Component/Velocity/Velocity.hh"
#include "Component/Hitbox/Hitbox.hh"
#include "Component/Text/Text.hh"

#include "System/Velocity/Velocity.hpp"
#include "System/Collision/Collision.hh"
#include "System/ButtonClick/ButtonClick.hpp"

#include "Entity/Button/Button.hh"

std::size_t ECS::CTypeRegistry::nextTypeIndex = 0;

int main(void)
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML ECS - Moving Squares");

    ECS::Core::Core core;
    core.registerComponent<ECS::Components::Position>();
    core.registerComponent<ECS::Components::Velocity>();
    core.registerComponent<ECS::Components::Health>();
    core.registerComponent<ECS::Components::Hitbox>();
    core.registerComponent<ECS::Components::Text>();

    auto velocitySystem = core.registerSystem<ECS::Systems::SystemVelocity>();
    auto collisionSystem = core.registerSystem<ECS::Systems::Collision>();
    auto buttonClickSystem = core.registerSystem<ECS::Systems::ButtonClick>();

    Signature velocitySystemSignature;
    velocitySystemSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Position>());
    velocitySystemSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Velocity>());
    core.setSystemSignature<ECS::Systems::SystemVelocity>(velocitySystemSignature);

    Signature collisionSystemSignature;
    collisionSystemSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Position>());
    collisionSystemSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Hitbox>());
    core.setSystemSignature<ECS::Systems::Collision>(collisionSystemSignature);

    Signature buttonSystemSignature;
    buttonSystemSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Position>());
    buttonSystemSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Hitbox>());
    buttonSystemSignature.set(ECS::CTypeRegistry::getTypeId<ECS::Components::Text>());
    core.setSystemSignature<ECS::Systems::ButtonClick>(buttonSystemSignature);
    
    std::size_t entity1 = core.createEntity();
    std::size_t entity2 = core.createEntity();
    ECS::Entities::Button buttonEntity1(core.createEntity());

    core.addComponent(entity1, ECS::Components::Position{400.0f, 100.0f});
    core.addComponent(entity1, ECS::Components::Velocity{0.001f, 0.001f});
    core.addComponent(entity1, ECS::Components::Hitbox{50, 50});

    core.addComponent(entity2, ECS::Components::Position{400.0f, 100.0f});
    core.addComponent(entity2, ECS::Components::Velocity{0.001f, -0.001f});
    core.addComponent(entity2, ECS::Components::Hitbox{50, 50});

    core.addComponent(buttonEntity1, ECS::Components::Position{12.0f, 12.0f});
    core.addComponent(buttonEntity1, ECS::Components::Hitbox{50, 50});
    core.addComponent(buttonEntity1, ECS::Components::Text{"Bouton Chef"});

    sf::RectangleShape square1(sf::Vector2f(50.0f, 50.0f));
    square1.setFillColor(sf::Color::Red);

    sf::RectangleShape square2(sf::Vector2f(50.0f, 50.0f));
    square2.setFillColor(sf::Color::Blue);
    
    sf::RectangleShape button1(sf::Vector2f(50.0f, 50.0f));
    square2.setFillColor(sf::Color::Green);

    while (window.isOpen()) {
        sf::Event event;
        std::vector<std::size_t> velocitySystemEntities =
            core.getEntitiesWithSignature(velocitySystemSignature);
        std::vector<std::size_t> collisionSystemEntities =
            core.getEntitiesWithSignature(collisionSystemSignature);
        std::vector<std::size_t> buttonSystemEntities =
            core.getEntitiesWithSignature(buttonSystemSignature);

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed &&
                sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                buttonClickSystem->onClick(
                    core.getComponents<ECS::Components::Position>(),
                    core.getComponents<ECS::Components::Hitbox>(),
                    sf::Mouse::getPosition(window), buttonSystemEntities);
            }
        }

        velocitySystem->update(core.getComponents<ECS::Components::Position>(),
                               core.getComponents<ECS::Components::Velocity>(),
                               velocitySystemEntities);
        collisionSystem->isHit(core.getComponents<ECS::Components::Position>(),
                               core.getComponents<ECS::Components::Hitbox>(),
                               velocitySystemEntities);

        auto &pos1 = core.getComponent<ECS::Components::Position>(entity1);
        square1.setPosition(pos1.getX(), pos1.getY());

        auto &pos2 = core.getComponent<ECS::Components::Position>(entity2);
        square2.setPosition(pos2.getX(), pos2.getY());

        auto &pos3 = core.getComponent<ECS::Components::Position>(buttonEntity1);
        button1.setPosition(pos3.getX(), pos3.getY());

        window.clear();

        window.draw(square1);
        window.draw(square2);
        window.draw(button1);

        window.display();
    }

    return 0;
}
