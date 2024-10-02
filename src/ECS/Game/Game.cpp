/*
** EPITECH PROJECT, 2024
** R-Type - Game : Game
** File description:
** Game class is the main class to game.
** Implementation of the main game loop, window, and integration with ECS.
*/

#include "Game.hh"
#include <cstddef>
#include <cstdlib>

std::size_t ECS::CTypeRegistry::nextTypeIndex = 0;

Rtype::Game::Game()
    : _isRunning(true)
{
    _core = std::make_unique<ECS::Core::Core>();

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    _window.Init(1000, 800, "R-Type Game");
    SetTargetFPS(60);
    _backgroundTexture = LoadTexture("ha.png");
    initComponents();
    initSystems();
    initEntities();
}

Rtype::Game::~Game()
{
    UnloadTexture(_backgroundTexture);
    std::cout << "Game destroyed" << std::endl;
}

void Rtype::Game::initComponents()
{
    _core->registerComponent<ECS::Components::Position>();
    _core->registerComponent<ECS::Components::Velocity>();
    _core->registerComponent<ECS::Components::Hitbox>();
    _core->registerComponent<ECS::Components::Input>();
    _core->registerComponent<ECS::Components::Projectile>();
    _core->registerComponent<ECS::Components::Background>();
}

void Rtype::Game::initSystems()
{
    _core->registerSystem<ECS::Systems::SystemVelocity>();
    _core->registerSystem<ECS::Systems::Collision>();
    _core->registerSystem<ECS::Systems::ProjectileCollision>();
    _core->registerSystem<ECS::Systems::InputUpdates>();

    Signature velocitySystemSignature;
    velocitySystemSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Position>());
    velocitySystemSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Velocity>());
    _core->setSystemSignature<ECS::Systems::SystemVelocity>(velocitySystemSignature);

    Signature collisionSignature;
    collisionSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Position>());
    collisionSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Hitbox>());
    _core->setSystemSignature<ECS::Systems::Collision>(collisionSignature);

    Signature projectileCollisionSignature;
    projectileCollisionSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Position>());
    projectileCollisionSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Hitbox>());
    projectileCollisionSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Projectile>());
    _core->setSystemSignature<ECS::Systems::ProjectileCollision>(projectileCollisionSignature);

    Signature inputUpdatesSignature;
    inputUpdatesSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Input>());
    _core->setSystemSignature<ECS::Systems::InputUpdates>(inputUpdatesSignature);
}

void Rtype::Game::initEntities()
{
    std::size_t player = _core->createEntity();
    _core->addComponent(player, ECS::Components::Position{200.0f, 300.0f});
    _core->addComponent(player, ECS::Components::Velocity{0.0f, 0.0f});
    _core->addComponent(player, ECS::Components::Hitbox{50.0f, 50.0f});
    _core->addComponent(player, ECS::Components::Input{});

    std::size_t enemy = _core->createEntity();
    _core->addComponent(enemy, ECS::Components::Position{500.0f, 300.0f});
    _core->addComponent(enemy, ECS::Components::Velocity{0.0f, 0.0f});
    _core->addComponent(enemy, ECS::Components::Hitbox{50.0f, 50.0f});

    std::size_t background = _core->createEntity();
    _core->addComponent(background, ECS::Components::Position{0.0f, 0.0f});
    _core->addComponent(background, ECS::Components::Velocity{-2.0f, 0.0f});
    _core->addComponent(background, ECS::Components::Background{});

    std::size_t background2 = _core->createEntity();
    float oui = _backgroundTexture.width;
    _core->addComponent(background2, ECS::Components::Position{oui, 0.0f});
    _core->addComponent(background2, ECS::Components::Velocity{-2.0f, 0.0f});
    _core->addComponent(background2, ECS::Components::Background{});
}

void Rtype::Game::run()
{
    while (!_window.ShouldClose() && _isRunning) {
        update();
        render();
    }
}

std::vector<std::size_t> getAllInputs() {
    std::vector<std::size_t> vec;
    if (IsKeyDown(KEY_RIGHT))
        vec.push_back(1);
    if (IsKeyDown(KEY_UP))
        vec.push_back(2);
    if (IsKeyDown(KEY_LEFT))
        vec.push_back(3);
    if (IsKeyDown(KEY_DOWN))
        vec.push_back(4);
    return vec;
}

void Rtype::Game::createProjectile(std::size_t entityID)
{
    auto &positions = _core->getComponents<ECS::Components::Position>();

    if (!positions[entityID].has_value()) {
        std::cerr << "Entity " << entityID << " does not have a valid position!" << std::endl;
        return;
    }
    const ECS::Components::Position &entityPos = positions[entityID].value();
    std::size_t projectile = _core->createEntity();
    _core->addComponent(projectile, ECS::Components::Position{entityPos.getX() + 60.0f, entityPos.getY() + 10.0f});
    _core->addComponent(projectile, ECS::Components::Velocity{5.0f, 0.0f});
    _core->addComponent(projectile, ECS::Components::Hitbox{10.0f, 5.0f});
    _core->addComponent(projectile, ECS::Components::Projectile{});
}

void Rtype::Game::update() {
    auto velocitySystem = _core->getSystem<ECS::Systems::SystemVelocity>();
    auto collisionSystem = _core->getSystem<ECS::Systems::Collision>();
    auto projectileCollisionSystem = _core->getSystem<ECS::Systems::ProjectileCollision>();
    auto inputUpdatesSystem = _core->getSystem<ECS::Systems::InputUpdates>();

    auto velocityEntities = _core->getEntitiesWithSignature(_core->getSystemSignature<ECS::Systems::SystemVelocity>());
    auto collisionEntities = _core->getEntitiesWithSignature(_core->getSystemSignature<ECS::Systems::Collision>());
    auto projectileEntities = _core->getEntitiesWithSignature(_core->getSystemSignature<ECS::Systems::ProjectileCollision>());
    auto inputEntities = _core->getEntitiesWithSignature(_core->getSystemSignature<ECS::Systems::InputUpdates>());

    std::size_t entitesID = inputUpdatesSystem->updateInputs(getAllInputs(),
                                     _core->getComponents<ECS::Components::Input>(),
                                     inputEntities);

    if (entitesID <= 10000)
        createProjectile(entitesID);
    inputUpdatesSystem->updateInputedVelocity(_core->getComponents<ECS::Components::Input>(),
                                              _core->getComponents<ECS::Components::Velocity>(),
                                              inputEntities);

    velocitySystem->update(_core->getComponents<ECS::Components::Position>(),
                           _core->getComponents<ECS::Components::Velocity>(),
                           velocityEntities);

    collisionSystem->isHit(_core->getComponents<ECS::Components::Position>(),
                           _core->getComponents<ECS::Components::Hitbox>(),
                           collisionEntities);

    projectileCollisionSystem->projectileIsHit(
        _core->getComponents<ECS::Components::Position>(),
        _core->getComponents<ECS::Components::Hitbox>(),
        projectileEntities, collisionEntities);
}

void Rtype::Game::renderBackground(ECS::ComponentManager::SparseArray<ECS::Components::Position> &positions)
{
    auto backgrounds = _core->getEntitiesWithComponent<ECS::Components::Background>();

    for (size_t i = 0; i < backgrounds.size(); i++) {
        if (positions[backgrounds[i]]->getX() == - (_backgroundTexture.width))
            positions[backgrounds[i]]->setX(_backgroundTexture.width);
        DrawTexture(_backgroundTexture, positions[backgrounds[i]]->getX(),
                    positions[backgrounds[i]]->getY(), WHITE);
    }
}

void Rtype::Game::render()
{
    BeginDrawing();
    _window.ClearBackground(RAYWHITE);

    auto &positions = _core->getComponents<ECS::Components::Position>();
    auto &hitboxes = _core->getComponents<ECS::Components::Hitbox>();
    auto &velocities = _core->getComponents<ECS::Components::Velocity>();

    auto toDraw = _core->getEntitiesWithComponent<ECS::Components::Position, ECS::Components::Hitbox>();
    auto backgrounds = _core->getEntitiesWithComponent<ECS::Components::Background>();

    renderBackground(positions);

    for (std::size_t i = 0; i < toDraw.size(); ++i) {
        auto &pos = positions[toDraw[i]].value();
        auto &hitbox = hitboxes[toDraw[i]].value();

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
    }

    EndDrawing();
}
