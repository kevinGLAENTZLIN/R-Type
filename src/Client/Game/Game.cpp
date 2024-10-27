/*
** EPITECH PROJECT, 2024
** R-Type - Game : Game
** File description:
** Game class is the main class to game.
** Implementation of the main game loop, window, and integration with ECS.
*/

#include "Game.hh"

#include "../../Utils/Network/Network.hpp"
#include <thread>

std::size_t ECS::CTypeRegistry::nextTypeIndex = 0;
std::unordered_map<std::size_t, std::function<std::type_index()>> ECS::CTypeRegistry::indexToTypeMap;
int menuOption = 0;
std::vector<std::string> options = { "Start Game", "Options", "Quit" };

Rtype::Game::Game(std::shared_ptr<Rtype::Network> network, bool render)
    : _network(network), _isRunning(true), _currentState(MENU),
    _isJoiningGame(false), _isAvailableGames(false), _isRendering(render), _modelCreated(false)
{
    _core = std::make_unique<ECS::Core::Core>();

    if (render) {
        SetConfigFlags(FLAG_WINDOW_RESIZABLE);
        SetTargetFPS(60);
        _window.Init(1280, 720, "R-Type Game");
        SetWindowMinSize(1280, 720);
        _camera = raylib::Camera3D({ 0.0f, 10.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, -1.0f }, 60.0f);
        _ressourcePool.addModel("ship_yellow");
        _ressourcePool.addModel("base_projectile");
        _ressourcePool.addModel("enemy_one");
        _ressourcePool.addTexture("bg_menu");
        _ressourcePool.addTexture("background");
        _ressourcePool.addTexture("background_layer0");
        _ressourcePool.addTexture("background_layer1");
        _ressourcePool.addTexture("background_layer2");
    }
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
    _core->registerComponent<ECS::Components::Musica>();
    _core->registerComponent<ECS::Components::SoundEffect>();
    _core->registerComponent<ECS::Components::TextField>();

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
    _core->registerSystem<ECS::Systems::TextFieldInputSystem>();
    _core->registerSystem<ECS::Systems::RenderTextFieldSystem>();

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

    Signature textFieldInputSignature;
    textFieldInputSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::TextField>());
    _core->setSystemSignature<ECS::Systems::TextFieldInputSystem>(textFieldInputSignature);

    Signature renderTextFieldSignature;
    renderTextFieldSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Position>());
    renderTextFieldSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::TextField>());
    renderTextFieldSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Text>());
    _core->setSystemSignature<ECS::Systems::RenderTextFieldSystem>(renderTextFieldSignature);
}

void Rtype::Game::loadMusic()
{
    InitAudioDevice();
    createMusic("./resources/stage1/stage1.mp3", "stage1");
    createMusic("./resources/menuMusic/menuMusic.mp3", "menu");
    createSound("./resources/blasterLego/blasterLego.mp3", "blasterLego");
    createSound("./resources/breakLego/breakLego.mp3", "breakLego");
}

Rtype::Game::~Game()
{
    _ressourcePool.UnloadAll();
}

void Rtype::Game::createEnemy(enemiesTypeEnum_t enemyType, float pos_x, float pos_y)
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
}

void Rtype::Game::movePlayer(int id, double x, double y)
{
    auto &velocity = _core->getComponent<ECS::Components::Velocity>(_mapID[id]);

    velocity.setX(x);
    velocity.setY(y);
}

void Rtype::Game::createPlayer(int id, float pos_x, float pos_y)
{
    if (!_isRendering && !_modelCreated) {
        _ressourcePool.addModel("ship_yellow");
        std::cout << "Model Loaded" << std::endl;
        _modelCreated = true;
    }
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
}

void Rtype::Game::createOtherPlayer(int id, float pos_x, float pos_y)
{
    if (!_isRendering && !_modelCreated) {
        std::cout << "Model Loaded" << std::endl;
        _ressourcePool.addModel("ship_yellow");
        _modelCreated = true;
    }
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

void Rtype::Game::destroyEntityMenu(void)
{
    std::vector<std::size_t> entitiesMenu = _core->getEntitiesWithComponent<ECS::Components::Button>();

    for (auto &entity : entitiesMenu)
        _core->destroyEntity(entity);
}

void Rtype::Game::destroyEntityLayer(void)
{
    std::vector<std::size_t> entitiesLayer = _core->getEntitiesWithComponent<ECS::Components::Background>();

    for (auto &entity : entitiesLayer)
        _core->destroyEntity(entity);
}

void Rtype::Game::destroyMusic()
{
    std::vector<std::size_t> entitiesMusic = _core->getEntitiesWithComponent<ECS::Components::Musica>();

    for (auto &entity : entitiesMusic)
        _core->destroyEntity(entity);
}

void Rtype::Game::destroyEntityText(void)
{
    std::vector<std::size_t> entitiesText = _core->getEntitiesWithComponent<ECS::Components::Text>();

    for (auto &entity : entitiesText)
        _core->destroyEntity(entity);
}

void Rtype::Game::initOptions(void)
{
    destroyEntityMenu();
    destroyEntityLayer();

    std::size_t back = _core->createEntity();
    _core->addComponent(back, ECS::Components::Position{400, 200});
    _core->addComponent(back, ECS::Components::Text{"Back", 30, RAYWHITE});
    _core->addComponent(back, ECS::Components::Button{Rectangle{350, 190, 300, 60}, true, [this]() {
        initMenu();
    }});
    createBackgroundLayers(0.f, "bg_menu", 1);
}

void Rtype::Game::joinGame(void)
{
    destroyEntityMenu();
    destroyEntityLayer();

    std::vector<std::tuple<int, int, int>> games = {
        {101, 2, 4},
        {102, 1, 4},
        {103, 3, 4},
        {103, 3, 4},
        {103, 3, 4},
        {102, 1, 4},
        {103, 3, 4},
        {103, 3, 4}
    };

    float yOffset = 200.0f;
    short buttonCount = 0;

    for (const auto &game : games) {
        if (buttonCount >= 5)
            break;
        int gameID = std::get<0>(game);
        int currentPlayerCount = std::get<1>(game);
        int maxPlayerCount = std::get<2>(game);

        std::size_t gameButton = _core->createEntity();

        _core->addComponent(gameButton, ECS::Components::Position{400, yOffset});

        std::string buttonText = "Game " + std::to_string(gameID) + " [" +
                                std::to_string(currentPlayerCount) + "/" +
                                 std::to_string(maxPlayerCount) + "]";
        _core->addComponent(gameButton, ECS::Components::Text{buttonText, 20, RAYWHITE});

        _core->addComponent(gameButton, ECS::Components::Button{Rectangle{350, yOffset - 10, 300, 40}, true, [this, gameID]() {
            std::cout << "Joining game " << gameID << std::endl;
        }});

        yOffset += 60.0f;
        buttonCount++;
    }

    std::size_t back = _core->createEntity();
    _core->addComponent(back, ECS::Components::Position{400, 500});
    _core->addComponent(back, ECS::Components::Text{"Back", 30, RAYWHITE});
    _core->addComponent(back, ECS::Components::Button{Rectangle{350, 490, 300, 60}, true, [this]() {
        initPlayOption();
    }});
    for (auto available_game: _availableGames)
        std::cout << "Game available: " << available_game << std::endl;
    createBackgroundLayers(0.f, "bg_menu", 1);
}

void Rtype::Game::joinGameID(void)
{
    destroyEntityMenu();
    destroyEntityLayer();
    destroyEntityText();

    std::size_t textFieldEntity = _core->createEntity();
    _core->addComponent(textFieldEntity, ECS::Components::Position{400, 200});
    _core->addComponent(textFieldEntity, ECS::Components::Text{"", 30, RAYWHITE});

    ECS::Components::TextField textField(Rectangle{350, 190, 300, 60}, true, "");
    textField.onTextChange([this, textFieldEntity](const std::string &newText) {
        auto &text = _core->getComponent<ECS::Components::Text>(textFieldEntity);
        text.setText(newText);
    });
    _core->addComponent(textFieldEntity, std::move(textField));

    std::size_t joinButton = _core->createEntity();
    _core->addComponent(joinButton, ECS::Components::Position{400, 300});
    _core->addComponent(joinButton, ECS::Components::Text{"Join", 30, RAYWHITE});
    _core->addComponent(joinButton, ECS::Components::Button{Rectangle{350, 290, 300, 60}, true, [this, textFieldEntity]() {
        auto &textField = _core->getComponent<ECS::Components::TextField>(textFieldEntity);
        std::string friendGameID = textField.getText();

        if (!friendGameID.empty()) {
            std::cout << "Joining game with ID: " << friendGameID << std::endl;
        }
    }});

    std::size_t back = _core->createEntity();
    _core->addComponent(back, ECS::Components::Position{400, 500});
    _core->addComponent(back, ECS::Components::Text{"Back", 30, RAYWHITE});
    _core->addComponent(back, ECS::Components::Button{Rectangle{350, 490, 300, 60}, true, [this]() {
        initPlayOption();
    }});
    createBackgroundLayers(0.f, "bg_menu", 1);
}

void Rtype::Game::joinRandomGame(void)
{
    destroyEntityMenu();
    destroyEntityLayer();

    std::size_t back = _core->createEntity();
    _core->addComponent(back, ECS::Components::Position{400, 200});
    _core->addComponent(back, ECS::Components::Text{"Back", 30, RAYWHITE});
    _core->addComponent(back, ECS::Components::Button{Rectangle{350, 190, 300, 60}, true, [this]() {
        initPlayOption();
    }});
    createBackgroundLayers(0.f, "bg_menu", 1);
}

void Rtype::Game::updatePlayerCountText(void)
{
    auto &textComponent = _core->getComponent<ECS::Components::Text>(_playerCountTextEntity);
    textComponent.setText(std::to_string(_playerCount));
}

void Rtype::Game::initCreationGame(void)
{
    destroyEntityMenu();
    destroyEntityLayer();

    _playerCount = 2;
    std::size_t easyButtonEntity = _core->createEntity();
    _core->addComponent(easyButtonEntity, ECS::Components::Position{100, 200});
    _core->addComponent(easyButtonEntity, ECS::Components::Text{"Facile", 20, RAYWHITE});
    _core->addComponent(easyButtonEntity, ECS::Components::Button{Rectangle{100, 190, 300, 60}, true, [this]() {
        _selectedDifficulty = 0;
    }});

    std::size_t normalButtonEntity = _core->createEntity();
    _core->addComponent(normalButtonEntity, ECS::Components::Position{100, 250});
    _core->addComponent(normalButtonEntity, ECS::Components::Text{"Normal", 20, RAYWHITE});
    _core->addComponent(normalButtonEntity, ECS::Components::Button{Rectangle{100, 240, 300, 60}, true, [this]() {
        _selectedDifficulty = 1;
    }});

    std::size_t hardButtonEntity = _core->createEntity();
    _core->addComponent(hardButtonEntity, ECS::Components::Position{100, 300});
    _core->addComponent(hardButtonEntity, ECS::Components::Text{"Difficile", 20, RAYWHITE});
    _core->addComponent(hardButtonEntity, ECS::Components::Button{Rectangle{100, 290, 300, 60}, true, [this]() {
        _selectedDifficulty = 2;
    }});

    std::size_t decreaseButtonEntity = _core->createEntity();
    _core->addComponent(decreaseButtonEntity, ECS::Components::Position{400, 400});
    _core->addComponent(decreaseButtonEntity, ECS::Components::Text{"-", 30, RAYWHITE});
    _core->addComponent(decreaseButtonEntity, ECS::Components::Button{Rectangle{370, 390, 60, 60}, true, [this]() {
        if (_playerCount > 1) {
            _playerCount--;
            updatePlayerCountText();
        }
    }});

    std::size_t playerCountTextEntity = _core->createEntity();
    _playerCountTextEntity = playerCountTextEntity;
    _core->addComponent(playerCountTextEntity, ECS::Components::Position{460, 400});
    _core->addComponent(playerCountTextEntity, ECS::Components::Text{std::to_string(_playerCount), 30, RAYWHITE});

    std::size_t increaseButtonEntity = _core->createEntity();
    _core->addComponent(increaseButtonEntity, ECS::Components::Position{520, 400});
    _core->addComponent(increaseButtonEntity, ECS::Components::Text{"+", 30, RAYWHITE});
    _core->addComponent(increaseButtonEntity, ECS::Components::Button{Rectangle{510, 390, 60, 60}, true, [this]() {
        if (_playerCount < 4) {
            _playerCount++;
            updatePlayerCountText();
        }
    }});

    std::size_t createButtonEntity = _core->createEntity();
    _core->addComponent(createButtonEntity, ECS::Components::Position{400, 500});
    _core->addComponent(createButtonEntity, ECS::Components::Text{"Create Game", 30, RAYWHITE});
    _core->addComponent(createButtonEntity, ECS::Components::Button{Rectangle{350, 490, 300, 60}, true, [this]() {
        std::unique_ptr<Rtype::Command::GameInfo::Create_game> cmd = CONVERT_ACMD_TO_CMD(Rtype::Command::GameInfo::Create_game, Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::CreateGame);
        cmd->setCommonPart(_network->getSocket(), _network->getSenderEndpoint(), _network->getAckToSend());
        cmd->set_client();
        _network->addCommandToInvoker(std::move(cmd));
        CONSOLE_INFO("Create game: ", " Sended")
    }});

    std::size_t back = _core->createEntity();
    _core->addComponent(back, ECS::Components::Position{400, 600});
    _core->addComponent(back, ECS::Components::Text{"Back", 30, RAYWHITE});
    _core->addComponent(back, ECS::Components::Button{Rectangle{350, 590, 300, 60}, true, [this]() {
        initPlayOption();
    }});
    createBackgroundLayers(0.f, "bg_menu", 1);
}

void Rtype::Game::initPlayOption(void)
{
    destroyEntityMenu();
    destroyEntityLayer();
    destroyEntityText();

    std::size_t createGame = _core->createEntity();
    _core->addComponent(createGame, ECS::Components::Position{400, 200});
    _core->addComponent(createGame, ECS::Components::Text{"Create Game", 30, RAYWHITE});
    _core->addComponent(createGame, ECS::Components::Button{Rectangle{350, 190, 300, 60}, true, [this]() {
        initCreationGame();
    }});

    std::size_t joinRandomGameEntity = _core->createEntity();
    _core->addComponent(joinRandomGameEntity, ECS::Components::Position{400, 300});
    _core->addComponent(joinRandomGameEntity, ECS::Components::Text{"Join Game", 30, RAYWHITE});
    _core->addComponent(joinRandomGameEntity, ECS::Components::Button{Rectangle{350, 290, 300, 60}, true, [this]() {
        CONSOLE_INFO("Join game", "")
        _isJoiningGame = true;
        std::unique_ptr<Rtype::Command::GameInfo::Games_available> cmd = CONVERT_ACMD_TO_CMD(Rtype::Command::GameInfo::Games_available, Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::GamesAvailable);
        cmd->setCommonPart(_network->getSocket(), _network->getSenderEndpoint(), _network->getAckToSend());
        cmd->set_client();
        _network->addCommandToInvoker(std::move(cmd));
        joinRandomGame();
    }});

    std::size_t joinGameEntity = _core->createEntity();
    _core->addComponent(joinGameEntity, ECS::Components::Position{400, 400});
    _core->addComponent(joinGameEntity, ECS::Components::Text{"Search available game", 30, RAYWHITE});
    _core->addComponent(joinGameEntity, ECS::Components::Button{Rectangle{350, 390, 300, 60}, true, [this]() {
        CONSOLE_INFO("Get available game", "")
        _isJoiningGame = false;
        std::unique_ptr<Rtype::Command::GameInfo::Games_available> cmd = CONVERT_ACMD_TO_CMD(Rtype::Command::GameInfo::Games_available, Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::GamesAvailable);
        cmd->setCommonPart(_network->getSocket(), _network->getSenderEndpoint(), _network->getAckToSend());
        cmd->set_client();
        _network->addCommandToInvoker(std::move(cmd));
        joinGame();
    }});

    std::size_t joinGameId = _core->createEntity();
    _core->addComponent(joinGameId, ECS::Components::Position{400, 500});
    _core->addComponent(joinGameId, ECS::Components::Text{"Join friends game", 30, RAYWHITE});
    _core->addComponent(joinGameId, ECS::Components::Button{Rectangle{350, 490, 300, 60}, true, [this]() {
        CONSOLE_INFO("Join Game by ID", "")
        joinGameID();
    }});

    std::size_t back = _core->createEntity();
        _core->addComponent(back, ECS::Components::Position{400, 600});
        _core->addComponent(back, ECS::Components::Text{"Back", 30, RAYWHITE});
        _core->addComponent(back, ECS::Components::Button{Rectangle{350, 590, 300, 60}, true, [this]() {
        initMenu();
    }});
    createBackgroundLayers(0.f, "bg_menu", 1);
}

void Rtype::Game::initMenu(void)
{
    destroyEntityMenu();
    destroyEntityLayer();
    playMusic("menu");

    std::size_t startGameButton = _core->createEntity();
    _core->addComponent(startGameButton, ECS::Components::Position{400, 200});
    _core->addComponent(startGameButton, ECS::Components::Text{"Play", 30, RAYWHITE});
    _core->addComponent(startGameButton, ECS::Components::Button{Rectangle{350, 190, 300, 60}, true, [this]() {
        initPlayOption();
    }});

    std::size_t option = _core->createEntity();
    _core->addComponent(option, ECS::Components::Position{400, 300});
    _core->addComponent(option, ECS::Components::Text{"Option", 30, RAYWHITE});
    _core->addComponent(option, ECS::Components::Button{Rectangle{350, 290, 300, 60}, true, [this]() {
        initOptions();
    }});

    std::size_t quitButton = _core->createEntity();
    _core->addComponent(quitButton, ECS::Components::Position{400, 400});
    _core->addComponent(quitButton, ECS::Components::Text{"Quit", 30, RAYWHITE});
    _core->addComponent(quitButton, ECS::Components::Button{Rectangle{350, 390, 300, 60}, true, [this]() {
        _isRunning = false;
    }});
    createBackgroundLayers(0.f, "bg_menu", 1);
}

void Rtype::Game::initGame(void)
{
    stopMusic("menu");
    destroyEntityMenu();
    destroyEntityLayer();
    destroyMusic();
    playMusic("stage1");
    createBackgroundLayers(2.f , "background_layer0", 3);
    createBackgroundLayers(3.f , "background_layer1", 3);
    createBackgroundLayers(5.f , "background_layer2", 3);
    switchState(GameState::PLAY);
    createPlayer(0, -10.0f, 0.0f);       //To refactor
    createEnemy(PATAPATA, 10.0f, 2.0f);  //To refactor
    createEnemy(PATAPATA, 13.0f, -2.0f); //To refactor
}

void Rtype::Game::run()
{
    std::thread musicThread(&Rtype::Game::loadMusic, this);

    musicThread.join();
    initMenu();
    while (!_window.ShouldClose() && _isRunning) {
        switch (_currentState) {
            case MENU:
                updateMusic("menu");
                updateMenu();
                renderMenu();
                break;
            case PLAY:
                updateMusic("stage1");
                update();
                render();
                break;
        }
    }
    CloseAudioDevice();
}

void Rtype::Game::runServer()
{
    _currentState = PLAY;

    while (_isRunning)
        switch (_currentState) {
            case PLAY:
                update();
        }
}

void Rtype::Game::sendInput(std::vector<std::size_t> vec)
{
    std::unique_ptr<Rtype::Command::Player::Move> cmd = CONVERT_ACMD_TO_CMD(Rtype::Command::Player::Move, Utils::InfoTypeEnum::Player, Utils::PlayerEnum::PlayerMove);
    double x = 0.;
    double y = 0.;

    if (vec.empty())
        return;
    for (auto input: vec) {
        switch (input) {
        case 1:
            x += 0.1;
            break;
        case 2:
            y -= 0.1;
            break;
        case 3:
            x -= 0.1;
            break;
        case 4:
            y += 0.1;
            break;
        }
    }
    cmd->set_client(x, y);
    cmd->setCommonPart(_network->getSocket(), _network->getSenderEndpoint(), _network->getAckToSend());
    _network->addCommandToInvoker(std::move(cmd));
}

std::vector<std::size_t> Rtype::Game::getAllInputs() {
    std::vector<std::size_t> vec;

    if (IsKeyDown(KEY_RIGHT))
        vec.push_back(1);
    if (IsKeyDown(KEY_UP))
        vec.push_back(2);
    if (IsKeyDown(KEY_LEFT))
        vec.push_back(3);
    if (IsKeyDown(KEY_DOWN))
        vec.push_back(4);
    if (IsKeyPressed(KEY_SPACE))
        vec.push_back(5);
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
    playSound("blasterLego");
}

void Rtype::Game::destroyProjectile(std::size_t entityID)
{
    _core->destroyEntity(entityID);
}

void Rtype::Game::createBackgroundLayers(float speed, std::string modelPath, int numberOfPanel)
{
    float width = _ressourcePool.getTexture(modelPath).GetWidth();

    for (int i = 0; i < numberOfPanel; i++) {
        std::size_t background = _core->createEntity();

        _core->addComponent(background, ECS::Components::Position{0.0f + (width * i) - 1, 0.0f});
        _core->addComponent(background, ECS::Components::Velocity{-speed, 0.0f});
        _core->addComponent(background, ECS::Components::Render2D{modelPath});
        _core->addComponent(background, ECS::Components::Background{width, speed});
    }
}

//!FUNCTIONS TO UPDATE GAME AND MENU -------------------------------------------

void Rtype::Game::updateMenu() {

    auto clicSystem = _core->getSystem<ECS::Systems::ButtonClickSystem>();
    auto inputTextfieldSystem = _core->getSystem<ECS::Systems::TextFieldInputSystem>();

    auto buttonEntities = _core->getEntitiesWithSignature(_core->getSystemSignature<ECS::Systems::ButtonClickSystem>());
    auto textfieldEntities = _core->getEntitiesWithSignature(_core->getSystemSignature<ECS::Systems::TextFieldInputSystem>());

    clicSystem->update(_core->getComponents<ECS::Components::Button>(),
                        buttonEntities);
    inputTextfieldSystem->update(_core->getComponents<ECS::Components::TextField>(),
                                 textfieldEntities);
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

    std::vector<std::size_t> inputs = getAllInputs();
    sendInput(inputs);
    std::size_t entityID = inputUpdatesSystem->updateInputs(inputs,
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
                           _mapID,
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

bool Rtype::Game::getJoiningGame()
{
    return _isJoiningGame;
}

void Rtype::Game::setIsJoiningGame(bool state)
{
    _isJoiningGame = state;
}

bool Rtype::Game::getIsAvailableGames()
{
    return _isAvailableGames;
}

void Rtype::Game::setIsAvailableGames(bool state)
{
    _isAvailableGames = state;
}

std::vector<int> Rtype::Game::getAvailableGames()
{
    return _availableGames;
}

void Rtype::Game::addAvailableGames(int game_id)
{
    _availableGames.push_back(game_id);
}

void Rtype::Game::clearAvailableGames()
{
    _availableGames.clear();
}

//!FUNCTIONS TO RENDER GAME AND MENU -------------------------------------------

void Rtype::Game::renderMenu() {
    BeginDrawing();
    _window.ClearBackground(BLACK);

    float currentWidth = GetScreenWidth();
    float currentHeight = GetScreenHeight();

    float scaleX = currentWidth / 1280.0f;
    float scaleY = currentHeight / 720.0f;

    auto renderSystemText = _core->getSystem<ECS::Systems::RenderTextSystem>();
    auto renderButtons = _core->getSystem<ECS::Systems::RenderButtonSystem>();
    auto renderSystem2D = _core->getSystem<ECS::Systems::SystemRender2D>();
    auto renderTextfield = _core->getSystem<ECS::Systems::RenderTextFieldSystem>();

    auto renderEntities2D  = _core->getEntitiesWithSignature(_core->getSystemSignature<ECS::Systems::SystemRender2D>());
    auto renderEntitiesText  = _core->getEntitiesWithSignature(_core->getSystemSignature<ECS::Systems::RenderTextSystem>());
    auto renderEntitiesButton  = _core->getEntitiesWithSignature(_core->getSystemSignature<ECS::Systems::RenderButtonSystem>());
    auto renderEntitiesTextfield  = _core->getEntitiesWithSignature(_core->getSystemSignature<ECS::Systems::RenderTextFieldSystem>());


    for (auto entity : renderEntitiesButton) {
        auto &buttonPosition = _core->getComponent<ECS::Components::Position>(entity);
        auto &buttonComponent = _core->getComponent<ECS::Components::Button>(entity);
        float x = buttonPosition.getOriginalX();
        float y = buttonPosition.getOriginalY();
        Rectangle rect = buttonComponent.getOriginalBounds();

        buttonPosition.setX(x * scaleX);
        buttonPosition.setY(y * scaleY);
        rect.x *= scaleX;
        rect.y *= scaleY;
        buttonComponent.setBounds(rect);
    }

    renderSystem2D->update(_core->getComponents<ECS::Components::Position>(),
                           _core->getComponents<ECS::Components::Render2D>(),
                           renderEntities2D,
                           _ressourcePool);

    renderTextfield->update(_core->getComponents<ECS::Components::TextField>(),
                            _core->getComponents<ECS::Components::Text>(),
                            _core->getComponents<ECS::Components::Position>(),
                            renderEntitiesTextfield);

    renderSystemText->update(_core->getComponents<ECS::Components::Text>(),
                            _core->getComponents<ECS::Components::Position>(),
                            renderEntitiesText);

    renderButtons->update(_core->getComponents<ECS::Components::Button>(),
                          _core->getComponents<ECS::Components::Text>(),
                          _core->getComponents<ECS::Components::Position>(),
                          renderEntitiesButton);
    EndDrawing();
}

void Rtype::Game::render() {
    BeginDrawing();
    _window.ClearBackground(RAYWHITE);

    float currentWidth = GetScreenWidth();
    float currentHeight = GetScreenHeight();

    float scaleX = currentWidth / 1280.0f;
    float scaleY = currentHeight / 720.0f;

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

//!FUNCTIONS TO HANDLE MUSIC AND SOUND -----------------------------------------


void Rtype::Game::createMusic(std::string path, std::string name) {
    std::size_t musicEntity = _core->createEntity();
    ECS::Components::Musica musicaComponent{path};

    _core->addComponent(musicEntity, musicaComponent);
    _musicMap.emplace(name, std::move(musicaComponent));
}

void Rtype::Game::createSound(std::string path, std::string name) {
    std::size_t soundEntity = _core->createEntity();
    ECS::Components::SoundEffect soundComponent{path};

    _core->addComponent(soundEntity, soundComponent);
    _soundMap.emplace(name, std::move(soundComponent));
}

void Rtype::Game::updateMusic(std::string name) {
    auto it = _musicMap.find(name);

    if (it != _musicMap.end()) {
        it->second.update();
    }
}

void Rtype::Game::playFromMusic(std::string name, float sec) {
    auto it = _musicMap.find(name);

    if (it != _musicMap.end()) {
        it->second.playFrom(sec);
    }
}

void Rtype::Game::stopMusic(std::string name) {
    auto it = _musicMap.find(name);

    if (it != _musicMap.end()) {
        it->second.stop();
    }
}

void Rtype::Game::playMusic(std::string name) {
    auto it = _musicMap.find(name);

    if (it != _musicMap.end()) {
        it->second.play();
    }
}

void Rtype::Game::playSound(std::string name) {
    auto it = _soundMap.find(name);

    if (it != _soundMap.end()) {
        it->second.play();
    } else {
        std::cerr << "Sound not found" << std::endl;
    }
}
