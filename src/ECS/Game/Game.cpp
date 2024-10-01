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
    _core->registerComponent<ECS::Components::Input>();

    auto velocitySystem = _core->registerSystem<ECS::Systems::SystemVelocity>();
    auto collisionSystem = _core->registerSystem<ECS::Systems::Collision>();
    auto InputUpdatesSystem = _core->registerSystem<ECS::Systems::InputUpdates>();

    Signature velocitySystemSignature;
    velocitySystemSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Position>());
    velocitySystemSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Velocity>());
    _core->setSystemSignature<ECS::Systems::SystemVelocity>(velocitySystemSignature);

    std::cout << "velocity sign " << velocitySystemSignature << std::endl;

    Signature collisionSignature;
    collisionSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Position>());
    collisionSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Hitbox>());
    _core->setSystemSignature<ECS::Systems::Collision>(collisionSignature);

    std::cout << "collision sign " << collisionSignature << std::endl;

    Signature inputUpdatesSignature;
    inputUpdatesSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Input>());
    _core->setSystemSignature<ECS::Systems::InputUpdates>(inputUpdatesSignature);

    std::cout << "input sign " << inputUpdatesSignature << std::endl;

    std::size_t player = _core->createEntity();
    _core->addComponent(player, ECS::Components::Position{200.0f, 300.0f});
    _core->addComponent(player, ECS::Components::Velocity{0.0f, 0.0f});
    _core->addComponent(player, ECS::Components::Hitbox{50.0f, 50.0f});
    _core->addComponent(player, ECS::Components::Input{});

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

std::vector<std::size_t> getAllInputs() {
    std::vector<std::size_t> jaj;
    if (IsKeyDown(KEY_RIGHT))
        jaj.push_back(1);
    if (IsKeyDown(KEY_UP))
        jaj.push_back(2);
    if (IsKeyDown(KEY_LEFT))
        jaj.push_back(3);
    if (IsKeyDown(KEY_DOWN))
        jaj.push_back(4);
    return jaj;
}

void Rtype::Game::update() {
    auto velocitySystem = _core->getSystem<ECS::Systems::SystemVelocity>();
    auto collisionSystem = _core->getSystem<ECS::Systems::Collision>();
    auto inputUpdatesSystem = _core->getSystem<ECS::Systems::InputUpdates>();

    auto velocityEntities = _core->getEntitiesWithSignature(_core->getSystemSignature<ECS::Systems::SystemVelocity>());
    auto collisionEntities = _core->getEntitiesWithSignature(_core->getSystemSignature<ECS::Systems::Collision>());
    auto inputEntities = _core->getEntitiesWithSignature(_core->getSystemSignature<ECS::Systems::InputUpdates>());

//    std::cout << inputEntities.size() << std::endl;
    inputUpdatesSystem->updateInputs(getAllInputs(),
                                     _core->getComponents<ECS::Components::Input>(),
                                     inputEntities);

    inputUpdatesSystem->updateInputedVelocity(_core->getComponents<ECS::Components::Input>(),
                                              _core->getComponents<ECS::Components::Velocity>(),
                                              inputEntities);

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
