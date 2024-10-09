/*
** EPITECH PROJECT, 2024
** R-Type - Game : Game
** File description:
** Game class is the main class to game.
** Implementation of the main game loop, window, and integration with ECS.
*/

#include "Game.hh"

std::size_t ECS::CTypeRegistry::nextTypeIndex = 0;
std::unordered_map<std::size_t, std::function<std::type_index()>> ECS::CTypeRegistry::indexToTypeMap;

Rtype::Game::Game()
    : _isRunning(true)
{
    _core = std::make_unique<ECS::Core::Core>();

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(60);
    _window.Init(1000, 800, "R-Type Game");
    _camera = raylib::Camera3D({ 0.0f, 10.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, -1.0f }, 60.0f);
    _ressourcePool.addModel("./resources/Disco.obj");
    _ressourcePool.addTexture("./resources/background.png");
    _core->registerComponent<ECS::Components::Position>();
    _core->registerComponent<ECS::Components::Velocity>();
    _core->registerComponent<ECS::Components::Hitbox>();
    _core->registerComponent<ECS::Components::Input>();
    _core->registerComponent<ECS::Components::Render2D>();
    _core->registerComponent<ECS::Components::Render3D>();
    _core->registerComponent<ECS::Components::Projectile>();
    _core->registerComponent<ECS::Components::Background>();
    _core->registerSystem<ECS::Components::Patapata>();

    _core->registerSystem<ECS::Systems::SystemVelocity>();
    _core->registerSystem<ECS::Systems::Collision>();
    _core->registerSystem<ECS::Systems::ProjectileCollision>();
    _core->registerSystem<ECS::Systems::InputUpdates>();
    _core->registerSystem<ECS::Systems::SystemRender2D>();
    _core->registerSystem<ECS::Systems::SystemRender3D>();
    _core->registerSystem<ECS::Systems::UpdateVelocityPatapata>();

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

    Signature renderSignature3D;
    renderSignature3D.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Position>());
    renderSignature3D.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Render3D>());
    _core->setSystemSignature<ECS::Systems::SystemRender3D>(renderSignature3D);


    Signature renderSignature2D;
    renderSignature2D.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Position>());
    renderSignature2D.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Render2D>());
    _core->setSystemSignature<ECS::Systems::SystemRender2D>(renderSignature2D);

    Signature updateVelocityPatapataSignature;
    updateVelocityPatapataSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Velocity>());
    updateVelocityPatapataSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Patapata>());
    _core->setSystemSignature<ECS::Systems::UpdateVelocityPatapata>(updateVelocityPatapataSignature);

    std::size_t player = _core->createEntity();
    _core->addComponent(player, ECS::Components::Position{0.0f, 0.0f});
    _core->addComponent(player, ECS::Components::Velocity{0.0f, 0.0f});
    _core->addComponent(player, ECS::Components::Hitbox{50.0f, 50.0f});
    _core->addComponent(player, ECS::Components::Input{});
    _core->addComponent(player, ECS::Components::Render3D{"./resources/Disco.obj"});

    std::size_t enemy = _core->createEntity();
    _core->addComponent(enemy, ECS::Components::Position{500.0f, 300.0f});
    _core->addComponent(enemy, ECS::Components::Velocity{0.0f, 0.0f});
    _core->addComponent(enemy, ECS::Components::Hitbox{50.0f, 50.0f});

    std::size_t background = _core->createEntity();
    _core->addComponent(background, ECS::Components::Position{0.0f, 0.0f});
    _core->addComponent(background, ECS::Components::Velocity{-0.5f, 0.0f});
    _core->addComponent(background, ECS::Components::Background{});
    _core->addComponent(background, ECS::Components::Render2D{"./resources/background.png"});

    float oui = _ressourcePool.getTexture("./resources/background.png").width;
    std::size_t background2 = _core->createEntity();
    _core->addComponent(background2, ECS::Components::Position{oui, 0.0f});
    _core->addComponent(background2, ECS::Components::Velocity{-0.5f, 0.0f});
    _core->addComponent(background2, ECS::Components::Background{});
    _core->addComponent(background2, ECS::Components::Render2D{"./resources/background.png"});

    std::size_t background3 = _core->createEntity();
    _core->addComponent(background3, ECS::Components::Position{oui * 2, 0.0f});
    _core->addComponent(background3, ECS::Components::Velocity{-0.5f, 0.0f});
    _core->addComponent(background3, ECS::Components::Background{});
    _core->addComponent(background3, ECS::Components::Render2D{"./resources/background.png"});
}

Rtype::Game::~Game()
{
    _ressourcePool.UnloadAll();
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

void Rtype::Game::destroyProjectile(std::size_t entityID)
{
    _core->destroyEntity(entityID);
}

void Rtype::Game::update() {
    auto velocitySystem = _core->getSystem<ECS::Systems::SystemVelocity>();
    auto collisionSystem = _core->getSystem<ECS::Systems::Collision>();
    auto projectileCollisionSystem = _core->getSystem<ECS::Systems::ProjectileCollision>();
    auto inputUpdatesSystem = _core->getSystem<ECS::Systems::InputUpdates>();
    auto patapataSystem = _core->getSystem<ECS::Systems::Patapata>();


    auto patapataEntities = _core->getEntitiesWithSignature(_core->getSystemSignature<ECS::Systems::Patapata>());
    auto velocityEntities = _core->getEntitiesWithSignature(_core->getSystemSignature<ECS::Systems::SystemVelocity>());
    auto collisionEntities = _core->getEntitiesWithSignature(_core->getSystemSignature<ECS::Systems::Collision>());
    auto projectileEntities = _core->getEntitiesWithSignature(_core->getSystemSignature<ECS::Systems::ProjectileCollision>());
    auto inputEntities = _core->getEntitiesWithSignature(_core->getSystemSignature<ECS::Systems::InputUpdates>());

    std::size_t entitesID = inputUpdatesSystem->updateInputs(getAllInputs(),
                                     _core->getComponents<ECS::Components::Input>(),
                                     inputEntities);

    if (entitesID <= 10000)
        createProjectile(entitesID);
    patapataSystem->update(_core->getComponents<ECS::Components::Velocity>(),
                            patapataEntities);
    inputUpdatesSystem->updateInputedVelocity(_core->getComponents<ECS::Components::Input>(),
                                              _core->getComponents<ECS::Components::Velocity>(),
                                              inputEntities);

    velocitySystem->update(_core->getComponents<ECS::Components::Position>(),
                           _core->getComponents<ECS::Components::Velocity>(),
                           velocityEntities);

    collisionSystem->isHit(_core->getComponents<ECS::Components::Position>(),
                           _core->getComponents<ECS::Components::Hitbox>(),
                           collisionEntities);

    std::size_t projectileEntityId = projectileCollisionSystem->projectileIsHit(
        _core->getComponents<ECS::Components::Position>(),
        _core->getComponents<ECS::Components::Hitbox>(),
        projectileEntities, collisionEntities);

    if (projectileEntityId <= 10000)
        destroyProjectile(projectileEntityId);
}

void Rtype::Game::render()
{
    BeginDrawing();
    _window.ClearBackground(RAYWHITE);

    auto &positions = _core->getComponents<ECS::Components::Position>();
    auto &hitboxes = _core->getComponents<ECS::Components::Hitbox>();
    auto &velocities = _core->getComponents<ECS::Components::Velocity>();

    auto toDraw = _core->getEntitiesWithComponent<ECS::Components::Position, ECS::Components::Hitbox>();

    auto renderSystem2D = _core->getSystem<ECS::Systems::SystemRender2D>();
    auto renderEntities2D  = _core->getEntitiesWithSignature(_core->getSystemSignature<ECS::Systems::SystemRender2D>());

    auto renderSystem3D = _core->getSystem<ECS::Systems::SystemRender3D>();
    auto renderEntities3D  = _core->getEntitiesWithSignature(_core->getSystemSignature<ECS::Systems::SystemRender3D>());

    renderSystem2D->update(_core->getComponents<ECS::Components::Position>(),
                        _core->getComponents<ECS::Components::Render2D>(),
                        renderEntities2D,
                        _ressourcePool);

    renderSystem3D->update(_core->getComponents<ECS::Components::Position>(),
                        _core->getComponents<ECS::Components::Render3D>(),
                        renderEntities3D,
                        _ressourcePool,
                        _camera);
    EndDrawing();
}
