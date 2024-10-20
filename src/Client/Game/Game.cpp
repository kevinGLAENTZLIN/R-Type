/*
** EPITECH PROJECT, 2024
** R-Type - Game : Game
** File description:
** Game class is the main class to game.
** Implementation of the main game loop, window, and integration with ECS.
*/

#include "Game.hh"
#include <cstddef>
#include<unistd.h>

std::size_t ECS::CTypeRegistry::nextTypeIndex = 0;
std::unordered_map<std::size_t, std::function<std::type_index()>> ECS::CTypeRegistry::indexToTypeMap;
int menuOption = 0;
std::vector<std::string> options = { "Start Game", "Options", "Quit" };

Rtype::Game::Game()
    : _isRunning(true), _currentState(MENU)
{
    _core = std::make_unique<ECS::Core::Core>();

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(60);
    _window.Init(1280, 720, "R-Type Game");
    _camera = raylib::Camera3D({ 0.0f, 10.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, -1.0f }, 60.0f);
    _ressourcePool.addModel("ship_yellow");
    _ressourcePool.addModel("base_projectile");
    _ressourcePool.addModel("enemy_one");
    _ressourcePool.addTexture("background");
    _ressourcePool.addTexture("background_layer0");
    _ressourcePool.addTexture("background_layer1");
    _ressourcePool.addTexture("background_layer2");

    _core->registerComponent<ECS::Components::Position>();
    _core->registerComponent<ECS::Components::Rotate>();
    _core->registerComponent<ECS::Components::Scale>();
    _core->registerComponent<ECS::Components::Velocity>();
    _core->registerComponent<ECS::Components::Hitbox>();
    _core->registerComponent<ECS::Components::Input>();
    _core->registerComponent<ECS::Components::Render2D>();
    _core->registerComponent<ECS::Components::Render3D>();
    _core->registerComponent<ECS::Components::Projectile>();
    _core->registerComponent<ECS::Components::Background>();
    _core->registerComponent<ECS::Components::AI>();
    _core->registerComponent<ECS::Components::Text>();
    _core->registerComponent<ECS::Components::Button>();

    _core->registerSystem<ECS::Systems::SystemVelocity>();
    _core->registerSystem<ECS::Systems::Collision>();
    _core->registerSystem<ECS::Systems::ProjectileCollision>();
    _core->registerSystem<ECS::Systems::InputUpdates>();
    _core->registerSystem<ECS::Systems::SystemRender2D>();
    _core->registerSystem<ECS::Systems::SystemRender3D>();
    _core->registerSystem<ECS::Systems::SystemBackground>();
    _core->registerSystem<ECS::Systems::UpdateVelocityAI>();
    _core->registerSystem<ECS::Systems::RenderTextSystem>();
    _core->registerSystem<ECS::Systems::RenderButtonSystem>();
    _core->registerSystem<ECS::Systems::ButtonClickSystem>();

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
        ECS::CTypeRegistry::getTypeId<ECS::Components::Rotate>());
    renderSignature3D.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Scale>());
    renderSignature3D.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Render3D>());
    _core->setSystemSignature<ECS::Systems::SystemRender3D>(renderSignature3D);

    Signature renderSignature2D;
    renderSignature2D.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Position>());
    renderSignature2D.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Render2D>());
    _core->setSystemSignature<ECS::Systems::SystemRender2D>(renderSignature2D);

    Signature backgroundSignature;
    backgroundSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Position>());
    backgroundSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Background>());
    _core->setSystemSignature<ECS::Systems::SystemBackground>(backgroundSignature);

    Signature updateVelocityAISignature;
    updateVelocityAISignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Velocity>());
    updateVelocityAISignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::AI>());
    _core->setSystemSignature<ECS::Systems::UpdateVelocityAI>(updateVelocityAISignature);

    Signature renderTextSignature;
    renderTextSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Position>());
    renderTextSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Text>());
    _core->setSystemSignature<ECS::Systems::RenderTextSystem>(renderTextSignature);

    Signature renderButtonSignature;
    renderButtonSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Position>());
    renderButtonSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Button>());
    _core->setSystemSignature<ECS::Systems::RenderButtonSystem>(renderButtonSignature);

    Signature buttonClickSignature;
    buttonClickSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Position>());
    buttonClickSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Button>());
    _core->setSystemSignature<ECS::Systems::ButtonClickSystem>(buttonClickSignature);

    createBackgroundLayers(2.f , "background_layer0");
    createBackgroundLayers(3.f , "background_layer1");
    createBackgroundLayers(5.f , "background_layer2");
}

Rtype::Game::~Game()
{
    _ressourcePool.UnloadAll();
}

std::size_t Rtype::Game::createEnemy(enemiesTypeEnum_t enemyType, float pos_x, float pos_y)
{
    std::pair<float, float> TmpHitbox = ECS::Utils::getModelSize(_ressourcePool.getModel("enemy_one"));
    std::size_t enemy = _core->createEntity();
    _core->addComponent(enemy, ECS::Components::Position{pos_x, pos_y});
    _core->addComponent(enemy, ECS::Components::Rotate{0.0f, 0.0f, 0.0f});
    _core->addComponent(enemy, ECS::Components::Scale{1.0f});
    _core->addComponent(enemy, ECS::Components::Velocity{0.0f, 0.0f});
    _core->addComponent(enemy, ECS::Components::Hitbox{TmpHitbox.first, TmpHitbox.second});
    _core->addComponent(enemy, ECS::Components::Render3D{"enemy_one"});
    _core->addComponent(enemy, ECS::Components::AI{enemyType});
    _mapID[enemy] = enemy;
    return enemy;
}

void Rtype::Game::movePlayer(int id, float x, float y)
{
    auto &velocity = _core->getComponent<ECS::Components::Velocity>(_mapID[id]);
    velocity.setX(x);
    velocity.setY(y);
}

std::size_t Rtype::Game::createPlayer(int id, float pos_x, float pos_y)
{
    std::pair<float, float> TmpHitbox = ECS::Utils::getModelSize(_ressourcePool.getModel("ship_yellow"));
    std::size_t player = _core->createEntity();
    _core->addComponent(player, ECS::Components::Position{pos_x, pos_y});
    _core->addComponent(player, ECS::Components::Rotate{-90.0f, 0.0f, 0.0f});
    _core->addComponent(player, ECS::Components::Scale{1.0f});
    _core->addComponent(player, ECS::Components::Velocity{0.0f, 0.0f});
    _core->addComponent(player, ECS::Components::Hitbox{TmpHitbox.first, TmpHitbox.second});
    _core->addComponent(player, ECS::Components::Input{});
    _core->addComponent(player, ECS::Components::Render3D{"ship_yellow"});
    _mapID[id] = player;
    return player;
}

void Rtype::Game::createOtherPlayer(int id, float pos_x, float pos_y)
{
    std::size_t otherPlayer = _core->createEntity();
    _core->addComponent(otherPlayer, ECS::Components::Position{pos_x, pos_y});
    _core->addComponent(otherPlayer, ECS::Components::Rotate{-90.0f, 0.0f, 0.0f});
    _core->addComponent(otherPlayer, ECS::Components::Scale{1.0f});
    _core->addComponent(otherPlayer, ECS::Components::Velocity{0.0f, 0.0f});
    std::pair<float, float> TmpHitbox = ECS::Utils::getModelSize(_ressourcePool.getModel("ship_yellow"));
    _core->addComponent(otherPlayer, ECS::Components::Hitbox{TmpHitbox.first, TmpHitbox.second});
    _core->addComponent(otherPlayer, ECS::Components::Render3D{"ship_yellow"});
    _mapID[id] = otherPlayer;
}

void Rtype::Game::initMenu(void)
{
    std::size_t text = _core->createEntity();
    _core->addComponent(text, ECS::Components::Position{10.0, 10.0});
    _core->addComponent(text, ECS::Components::Text{"Hello World", 20, RAYWHITE});

    std::size_t startGameButton = _core->createEntity();
    _core->addComponent(startGameButton, ECS::Components::Position{400, 300});
    _core->addComponent(startGameButton, ECS::Components::Text{"Start Game", 30, RAYWHITE});
    _core->addComponent(startGameButton, ECS::Components::Button{Rectangle{400, 300, 200, 50}, true, [this]() {
        initGame();
    }});

    std::size_t quitButton = _core->createEntity();
    _core->addComponent(quitButton, ECS::Components::Position{400, 400});
    _core->addComponent(quitButton, ECS::Components::Text{"Quit", 30, RAYWHITE});
    _core->addComponent(quitButton, ECS::Components::Button{Rectangle{400, 400, 200, 50}, true, [this]() {
        _isRunning = false;
    }});
}

void Rtype::Game::initGame(void)
{
    switchState(GameState::PLAY);
    createPlayer(0, -10.0f, 0.0f);
    createEnemy(PATAPATA, 10.0f, 2.0f);
    createEnemy(PATAPATA, 13.0f, -2.0f);
}

void Rtype::Game::run() {
    initMenu();
    while (!_window.ShouldClose() && _isRunning) {
        switch (_currentState) {
            case MENU:
                updateMenu();
                renderMenu();
                break;
            case PLAY:
                update();
                render();
                break;
        }
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

void Rtype::Game::switchState(GameState newState)
{
    _currentState = newState;
}

void Rtype::Game::createEnemyProjectile(int id)
{
    auto &positions = _core->getComponents<ECS::Components::Position>();
    auto &hitboxes = _core->getComponents<ECS::Components::Hitbox>();

    if (!positions[_mapID[id]].has_value()) {
        std::cerr << "Enemy " << id << " does not have a valid position!" << std::endl;
        return;
    }

    const ECS::Components::Position &enemyPos = positions[_mapID[id]].value();
    const ECS::Components::Hitbox &enemyHitbox = hitboxes[_mapID[id]].value();

    std::size_t projectile = _core->createEntity();

    std::pair<float, float> TmpHitbox = ECS::Utils::getModelSize(_ressourcePool.getModel("base_projectile"));

    float projectileStartX = enemyPos.getX() - (enemyHitbox.getWidth() / 2) - TmpHitbox.first;

    _core->addComponent(projectile, ECS::Components::Position{
        projectileStartX,
        enemyPos.getY()
    });
    _core->addComponent(projectile, ECS::Components::Rotate{0.0f, 0.0f, 0.0f});
    _core->addComponent(projectile, ECS::Components::Scale{1.0f});
    _core->addComponent(projectile, ECS::Components::Hitbox{TmpHitbox.first, TmpHitbox.second});

    _core->addComponent(projectile, ECS::Components::Velocity{-0.2f, 0.0f});
    _core->addComponent(projectile, ECS::Components::Projectile{});
    _core->addComponent(projectile, ECS::Components::Render3D{"base_projectile"});
}

void Rtype::Game::createPlayerProjectile(std::size_t entityID)
{
    auto &positions = _core->getComponents<ECS::Components::Position>();
    auto &hitboxes = _core->getComponents<ECS::Components::Hitbox>();

    if (!positions[entityID].has_value()) {
        std::cerr << "Entity " << entityID << " does not have a valid position!" << std::endl;
        return;
    }
    const ECS::Components::Position &entityPos = positions[entityID].value();
    const ECS::Components::Hitbox &entityHitbox = hitboxes[entityID].value();

    std::size_t projectile = _core->createEntity();

    std::pair<float, float> TmpHitbox = ECS::Utils::getModelSize(_ressourcePool.getModel("base_projectile"));
    _core->addComponent(projectile, ECS::Components::Position{entityPos.getX() + entityHitbox.getWidth(), entityPos.getY()});
    _core->addComponent(projectile, ECS::Components::Rotate{0.0f, 0.0f, 0.0f});
    _core->addComponent(projectile, ECS::Components::Scale{1.0f});
    _core->addComponent(projectile, ECS::Components::Hitbox{TmpHitbox.first, TmpHitbox.second});
    _core->addComponent(projectile, ECS::Components::Velocity{0.2f, 0.0f});
    _core->addComponent(projectile, ECS::Components::Projectile{});
    _core->addComponent(projectile, ECS::Components::Render3D{"base_projectile"});
}

void Rtype::Game::destroyProjectile(std::size_t entityID)
{
    _core->destroyEntity(entityID);
}

void Rtype::Game::createBackgroundLayers(float speed, std::string modelPath)
{
    float width = _ressourcePool.getTexture(modelPath).GetWidth();

    for (int i = 0; i < 3; i++) {
        std::size_t background = _core->createEntity();

        _core->addComponent(background, ECS::Components::Position{0.0f + (width * i) - 1, 0.0f});
        _core->addComponent(background, ECS::Components::Velocity{-speed, 0.0f});
        _core->addComponent(background, ECS::Components::Render2D{modelPath});
        _core->addComponent(background, ECS::Components::Background{width, speed});
    }
}

void Rtype::Game::updateMenu() {

    auto clicSystem = _core->getSystem<ECS::Systems::ButtonClickSystem>();

    auto buttonEntities = _core->getEntitiesWithSignature(_core->getSystemSignature<ECS::Systems::ButtonClickSystem>());

    clicSystem->update(_core->getComponents<ECS::Components::Button>(),
                        buttonEntities);
}

void Rtype::Game::update() {
    auto velocitySystem = _core->getSystem<ECS::Systems::SystemVelocity>();
    auto collisionSystem = _core->getSystem<ECS::Systems::Collision>();
    auto projectileCollisionSystem = _core->getSystem<ECS::Systems::ProjectileCollision>();
    auto inputUpdatesSystem = _core->getSystem<ECS::Systems::InputUpdates>();
    auto backgroundSystem = _core->getSystem<ECS::Systems::SystemBackground>();
    auto AISystem = _core->getSystem<ECS::Systems::UpdateVelocityAI>();

    auto velocityEntities = _core->getEntitiesWithSignature(_core->getSystemSignature<ECS::Systems::SystemVelocity>());
    auto collisionEntities = _core->getEntitiesWithSignature(_core->getSystemSignature<ECS::Systems::Collision>());
    auto projectileEntities = _core->getEntitiesWithSignature(_core->getSystemSignature<ECS::Systems::ProjectileCollision>());
    auto inputEntities = _core->getEntitiesWithSignature(_core->getSystemSignature<ECS::Systems::InputUpdates>());
    auto backgroundEntities = _core->getEntitiesWithSignature(_core->getSystemSignature<ECS::Systems::SystemBackground>());
    auto AIEntities = _core->getEntitiesWithSignature(_core->getSystemSignature<ECS::Systems::UpdateVelocityAI>());

    AISystem->update(_core->getComponents<ECS::Components::Velocity>(),
                     _core->getComponents<ECS::Components::Position>(),
                     _core->getComponents<ECS::Components::AI>(),
                     AIEntities);

    std::size_t entityID = inputUpdatesSystem->updateInputs(getAllInputs(),
                                     _core->getComponents<ECS::Components::Input>(),
                                     inputEntities);

    inputUpdatesSystem->updateInputedVelocity(_core->getComponents<ECS::Components::Input>(),
                                              _core->getComponents<ECS::Components::Velocity>(),
                                              inputEntities);

    backgroundSystem->update(_core->getComponents<ECS::Components::Position>(),
                            _core->getComponents<ECS::Components::Background>(),
                            backgroundEntities);

    velocitySystem->update(_core->getComponents<ECS::Components::Position>(),
                           _core->getComponents<ECS::Components::Velocity>(),
                           velocityEntities);

    if (entityID <= 10000)
        createPlayerProjectile(entityID);

    collisionSystem->isHit(_core->getComponents<ECS::Components::Position>(),
                           _core->getComponents<ECS::Components::Hitbox>(),
                           collisionEntities);

    std::vector<std::size_t> projectileEntityId = projectileCollisionSystem->projectileIsHit(
        _core->getComponents<ECS::Components::Position>(),
        _core->getComponents<ECS::Components::Hitbox>(),
        projectileEntities, collisionEntities);

    for (int i = 0; i < projectileEntityId.size(); i++)
        destroyProjectile(projectileEntityId[i]);
    if (false)
        _camera.Update(CAMERA_FREE);
}

void Rtype::Game::renderMenu() {
    BeginDrawing();
    _window.ClearBackground(BLACK);
    auto renderSystemText = _core->getSystem<ECS::Systems::RenderTextSystem>();
    auto renderButtons = _core->getSystem<ECS::Systems::RenderButtonSystem>();

    auto renderEntitiesText  = _core->getEntitiesWithSignature(_core->getSystemSignature<ECS::Systems::RenderTextSystem>());
    auto renderEntitiesButton  = _core->getEntitiesWithSignature(_core->getSystemSignature<ECS::Systems::RenderButtonSystem>());

    renderSystemText->update(_core->getComponents<ECS::Components::Text>(),
                        _core->getComponents<ECS::Components::Position>(),
                        renderEntitiesText);

    renderButtons->update(_core->getComponents<ECS::Components::Button>(),
                        _core->getComponents<ECS::Components::Text>(),
                        _core->getComponents<ECS::Components::Position>(),
                        renderEntitiesButton);
    EndDrawing();
}

void Rtype::Game::render()
{
    BeginDrawing();
    _window.ClearBackground(RAYWHITE);
    auto renderSystem2D = _core->getSystem<ECS::Systems::SystemRender2D>();
    auto renderEntities2D  = _core->getEntitiesWithSignature(_core->getSystemSignature<ECS::Systems::SystemRender2D>());

    auto renderSystem3D = _core->getSystem<ECS::Systems::SystemRender3D>();
    auto renderEntities3D  = _core->getEntitiesWithSignature(_core->getSystemSignature<ECS::Systems::SystemRender3D>());

    renderSystem2D->update(_core->getComponents<ECS::Components::Position>(),
                        _core->getComponents<ECS::Components::Render2D>(),
                        renderEntities2D,
                        _ressourcePool);

    renderSystem3D->update(_core->getComponents<ECS::Components::Position>(),
                        _core->getComponents<ECS::Components::Rotate>(),
                        _core->getComponents<ECS::Components::Scale>(),
                        _core->getComponents<ECS::Components::Render3D>(),
                        renderEntities3D,
                        _ressourcePool,
                        _camera);
    EndDrawing();
}
