/*
** EPITECH PROJECT, 2024
** R-Type - Game : Game
** File description:
** Game class is the main class to game.
** Implementation of the main game loop, window, and integration with ECS.
*/

#include "Game.hh"
#include <cstdlib>

std::size_t ECS::CTypeRegistry::nextTypeIndex = 0;

Rtype::Game::Game()
    : _isRunning(true)
{
    _core = std::make_unique<ECS::Core::Core>();

    _window.Init(1000, 800, "R-Type Game");
    SetTargetFPS(60);

    _core->registerComponent<ECS::Components::Position>();
    _core->registerComponent<ECS::Components::Velocity>();
    _core->registerComponent<ECS::Components::Hitbox>();

    auto velocitySystem = _core->registerSystem<ECS::Systems::SystemVelocity>();
    auto collisionSystem = _core->registerSystem<ECS::Systems::Collision>();

    Signature velocitySystemSignature;
        velocitySystemSignature.set(
            ECS::CTypeRegistry::getTypeId<ECS::Components::Position>());
        velocitySystemSignature.set(
            ECS::CTypeRegistry::getTypeId<ECS::Components::Velocity>());
        _core->setSystemSignature<ECS::Systems::SystemVelocity>(velocitySystemSignature);

    Signature hitboxSignature;
        hitboxSignature.set(
            ECS::CTypeRegistry::getTypeId<ECS::Components::Position>());
        hitboxSignature.set(
            ECS::CTypeRegistry::getTypeId<ECS::Components::Hitbox>());
        _core->setSystemSignature<ECS::Systems::Collision>(hitboxSignature);

    std::size_t player = _core->createEntity();
    _core->addComponent(player, ECS::Components::Position{200.0f, 300.0f});
    _core->addComponent(player, ECS::Components::Velocity{1.0f, 0.0f});
    _core->addComponent(player, ECS::Components::Hitbox{50.0f, 50.0f});

    std::size_t enemy = _core->createEntity();
    _core->addComponent(enemy, ECS::Components::Position{500.0f, 300.0f});
    _core->addComponent(enemy, ECS::Components::Velocity{-1.0f, 0.0f});
    _core->addComponent(enemy, ECS::Components::Hitbox{50.0f, 50.0f});
}

Rtype::Game::~Game()
{
    std::cout << "Game destroyed" << std::endl;
}

void Rtype::Game::run()
{
    while (!_window.ShouldClose() && _isRunning) {
        update();
        render();
    }
}

void Rtype::Game::update() {
    auto velocitySystem = _core->getSystem<ECS::Systems::SystemVelocity>();
    auto collisionSystem = _core->getSystem<ECS::Systems::Collision>();

    auto velocityEntities = _core->getEntitiesWithSignature(_core->getSystemSignature<ECS::Systems::SystemVelocity>());
    auto collisionEntities = _core->getEntitiesWithSignature(_core->getSystemSignature<ECS::Systems::Collision>());

    velocitySystem->update(_core->getComponents<ECS::Components::Position>(),
                           _core->getComponents<ECS::Components::Velocity>(),
                           velocityEntities);

    collisionSystem->isHit(_core->getComponents<ECS::Components::Position>(),
                           _core->getComponents<ECS::Components::Hitbox>(),
                           collisionEntities);
}


void Rtype::Game::render()
{
    BeginDrawing();
    _window.ClearBackground(RAYWHITE);

    auto &positions = _core->getComponents<ECS::Components::Position>();
    auto &hitboxes = _core->getComponents<ECS::Components::Hitbox>();

    for (std::size_t i = 0; i < positions.size(); ++i) {
        if (positions[i].has_value() && hitboxes[i].has_value()) {
            auto &pos = positions[i].value();
            auto &hitbox = hitboxes[i].value();

            if (hitbox.getWidth() <= 0 || hitbox.getHeight() <= 0) {
                std::cerr << "Invalid hitbox dimensions!" << std::endl;
                continue;
            }

            if (pos.getX() < 0 || pos.getY() < 0) {
                std::cerr << "Invalid position!" << std::endl;
                continue;
            }

            raylib::Rectangle rect(pos.getX(), pos.getY(), hitbox.getWidth(), hitbox.getHeight());
            rect.Draw(DARKBLUE);
        } else {
            std::cerr << "Position or hitbox not set!" << std::endl;
        }
    }

    EndDrawing();
}
