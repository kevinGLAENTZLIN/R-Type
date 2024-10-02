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
    _camera = raylib::Camera3D({ 0.0f, 10.0f, 10.0f }, { 0.0f, 10.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 60.0f);

    Vector3 movement = { 0.0f, 0.0f, 0.0f };
    Vector3 rotation = { .0f, 90.0f, 0.0f }; // Rotate 90 degrees around X-axis for top-down view
    float zoom = 1.0f;
    _camera.Update(movement, rotation, zoom);
    SetTargetFPS(60);
    _core->registerComponent<ECS::Components::Position>();
    _core->registerComponent<ECS::Components::Velocity>();
    _core->registerComponent<ECS::Components::Hitbox>();
    _core->registerComponent<ECS::Components::Input>();
    _core->registerComponent<ECS::Components::Render>();

    auto velocitySystem = _core->registerSystem<ECS::Systems::SystemVelocity>();
    auto collisionSystem = _core->registerSystem<ECS::Systems::Collision>();
    auto InputUpdatesSystem = _core->registerSystem<ECS::Systems::InputUpdates>();
    auto renderSystem = _core->registerSystem<ECS::Systems::SystemRender>();

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

    Signature renderSignature;
    renderSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Position>());
    renderSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Render>());
    _core->setSystemSignature<ECS::Systems::SystemRender>(renderSignature);

    std::cout << "render sign " << renderSignature << std::endl;


    std::size_t player = _core->createEntity();
    _core->addComponent(player, ECS::Components::Position{200.0f, 300.0f});
    _core->addComponent(player, ECS::Components::Velocity{0.0f, 0.0f});
    _core->addComponent(player, ECS::Components::Hitbox{50.0f, 50.0f});
    _core->addComponent(player, ECS::Components::Input{});
    _core->addComponent(player, ECS::Components::Render{"../../../resources/Disco.obj"});

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
    // Update the camera to achieve a top-down view
}

void Rtype::Game::render()
{
    BeginDrawing();
    _window.ClearBackground(RAYWHITE);

    auto &positions = _core->getComponents<ECS::Components::Position>();
    auto &hitboxes = _core->getComponents<ECS::Components::Hitbox>();

    auto renderSystem = _core->getSystem<ECS::Systems::SystemRender>();
    auto renderEntities = _core->getEntitiesWithSignature(_core->getSystemSignature<ECS::Systems::SystemRender>());
    _camera.BeginMode();
    {
    renderSystem->update(_core->getComponents<ECS::Components::Position>(),
                         _core->getComponents<ECS::Components::Render>(),
                         renderEntities,
                         _ressourcePool);
        DrawGrid(1000, 0.1f);
    }
    _camera.EndMode();
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

        } else {
            std::cerr << "Position or hitbox not set!" << std::endl;
        }
    }
    DrawRectangle(10, 10, 300, 150, Fade(SKYBLUE, 0.5f));
    DrawRectangleLines(10, 10, 300, 150, BLUE);
    DrawText(TextFormat("Camera Position: (%.2f, %.2f, %.2f)", _camera.GetPosition().x, _camera.GetPosition().y, _camera.GetPosition().z), 20, 20, 10, BLACK);
    DrawText(TextFormat("Camera Target: (%.2f, %.2f, %.2f)", _camera.GetTarget().x, _camera.GetTarget().y, _camera.GetTarget().z), 20, 40, 10, BLACK);
    DrawText(TextFormat("Camera Up: (%.2f, %.2f, %.2f)", _camera.GetUp().x, _camera.GetUp().y, _camera.GetUp().z), 20, 60, 10, BLACK);
    EndDrawing();
}
