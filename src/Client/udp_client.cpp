/*
** EPITECH PROJECT, 2024
** R-Type
** File description: Client Class
** udp_client
*/

#include "./udp_client.hpp"
#include "../Utils/Protocol/Protocol.hpp"

Rtype::udpClient::udpClient(const std::string &serverAddr, const int serverPort):
    _id(-1), _ioContext()
{
    _network = std::make_shared<Rtype::Network>(_ioContext, serverAddr, serverPort, "Client");
    _game = std::make_unique<Rtype::Game>(_network, true);
    setHandleMaps();
    connectClient();
    read_server();
}

Rtype::udpClient::~udpClient()
{
    if (_network->getSocket()->is_open()) {
        _network->getSocket()->cancel();
        _network->getSocket()->close();
    }
    _ioContext.stop();
    if (_networkThread.joinable()) {
        _networkThread.join();
    }

    std::cout << "Client disconnected successfully." << std::endl;
}

void Rtype::udpClient::run()
{
    _networkThread = std::thread([this]() {
        this->runNetwork();
    });
    _game->run();
}

void Rtype::udpClient::runNetwork()
{
    _ioContext.run();
}


void Rtype::udpClient::read_server()
{
    auto sender_endpoint = std::make_shared<udp::endpoint>();

    _network->getSocket()->async_receive_from(boost::asio::buffer(_receiverBuffer), *sender_endpoint,
    [this, sender_endpoint](const boost::system::error_code& error, std::size_t bytes_recv) {
        Utils::Network::Response clientResponse;
        Utils::Network::bytes data;

        if (!error && bytes_recv > 0) {
            data = Utils::Network::bytes(std::begin(_receiverBuffer), std::end(_receiverBuffer));
            clientResponse = Utils::Network::Protocol::ParseMsg(true, data);
            handleResponse(clientResponse);
        } else if (error)
            std::cerr << "Error receiving data: " << error.message() << std::endl;
        read_server();
    });
}


void Rtype::udpClient::setHandleMaps()
{
    setHandleGameInfoMap();
    setHandlePlayerMap();
    setHandleEnemyMap();
    setHandleBossMap();
    setHandlePowerUpMap();
    setHandleProjectileMap();
}

void Rtype::udpClient::setHandleGameInfoMap()
{
    _handleGameInfoMap[Utils::GameInfoEnum::NewClientConnected] = [this](Utils::Network::Response response) {
        std::unique_ptr<Rtype::Command::GameInfo::Client_connection> cmd = _network->convertACommandToCommand<Rtype::Command::GameInfo::Client_connection>(_network->createCommand(static_cast<uint8_t>(Utils::InfoTypeEnum::GameInfo), static_cast<uint8_t>(Utils::GameInfoEnum::NewClientConnected)));
        _id = response.PopParam<int>();
        CONSOLE_INFO("Id set on client: ", _id);
    };

    _handleGameInfoMap[Utils::GameInfoEnum::GamesAvailable] = [this](Utils::Network::Response response) {
        int codeRoom = response.PopParam<int>();
        int nbPlayer = response.PopParam<int>();
        int nbMaxPlayer = response.PopParam<int>();
        std::unique_ptr<Rtype::Command::GameInfo::Join_game> join_cmd ;

        if (codeRoom == -1) {
            CONSOLE_INFO("No Room available.", "");
            return;
        }
        CONSOLE_INFO(codeRoom, ": is available");
        if (_game->getJoiningGame()) {
            join_cmd = CONVERT_ACMD_TO_CMD(Rtype::Command::GameInfo::Join_game, Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::JoinGame);
            _game->setIsJoiningGame(false);
            join_cmd->setCommonPart(_network->getSocket(), _network->getSenderEndpoint(), _network->getAckToSend());
            join_cmd->set_client(codeRoom);
            _network->addCommandToInvoker(std::move(join_cmd));
        }
        if (_game->getIsAvailableGames()) {
            _game->addAvailableGames(codeRoom, nbPlayer, nbMaxPlayer);
            _game->joinGame();
        }
    };

    _handleGameInfoMap[Utils::GameInfoEnum::CreateGame] = [this](Utils::Network::Response response) {
        int codeRoom = response.PopParam<int>();
        std::unique_ptr<Rtype::Command::GameInfo::Join_game> cmd = CONVERT_ACMD_TO_CMD(Rtype::Command::GameInfo::Join_game, Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::JoinGame);

        if (codeRoom == -1) {
            CONSOLE_INFO("Game failed to create, too many game.", "")
        }
        CONSOLE_INFO("Game created: ", codeRoom)
        cmd->setCommonPart(_network->getSocket(), _network->getSenderEndpoint(), _network->getAckToSend());
        cmd->set_client(codeRoom);
        _network->addCommandToInvoker(std::move(cmd));
        CONSOLE_INFO("Join game sended: ", codeRoom)
    };

    _handleGameInfoMap[Utils::GameInfoEnum::JoinGame] = [this](Utils::Network::Response response) {
        std::unique_ptr<Rtype::Command::GameInfo::Join_game> cmd = _network->convertACommandToCommand<Rtype::Command::GameInfo::Join_game>(_network->createCommand(static_cast<uint8_t>(Utils::InfoTypeEnum::GameInfo), static_cast<uint8_t>(Utils::GameInfoEnum::JoinGame)));
        bool accepted = response.PopParam<bool>();
        int level = response.PopParam<int>();

        if (!accepted) {
            _game->failToConnect();
            return;
        }
        CONSOLE_INFO("Joining game at level: ", level)
        _game->initGame(_id);
    };

    _handleGameInfoMap[Utils::GameInfoEnum::GameWonLost] = [this](Utils::Network::Response response) {
        std::unique_ptr<Rtype::Command::GameInfo::Game_result> cmd = _network->convertACommandToCommand<Rtype::Command::GameInfo::Game_result>(_network->createCommand(static_cast<uint8_t>(Utils::InfoTypeEnum::GameInfo), static_cast<uint8_t>(Utils::GameInfoEnum::GameWonLost)));
        bool won = response.PopParam<bool>();

        if (won) {
            std::cerr << "You won!" << std::endl;
        } else {
            std::cerr << "You lost!" << std::endl;
        }
    };

    _handleGameInfoMap[Utils::GameInfoEnum::SafetyCheck] = [this](Utils::Network::Response response) {
        std::cerr << "Safety check received." << std::endl;
    };

    _handleGameInfoMap[Utils::GameInfoEnum::LevelComplete] = [this](Utils::Network::Response response) {
        std::unique_ptr<Rtype::Command::GameInfo::Level_complete> cmd = _network->convertACommandToCommand<Rtype::Command::GameInfo::Level_complete>(_network->createCommand(static_cast<uint8_t>(Utils::InfoTypeEnum::GameInfo), static_cast<uint8_t>(Utils::GameInfoEnum::LevelComplete)));
        int level = response.PopParam<int>();

        std::cerr << "Level " << level << " completed." << std::endl;
    };
};


void Rtype::udpClient::setHandlePlayerMap() {
    _handlePlayerMap[Utils::PlayerEnum::PlayerSpawnOnGame] = [this](Utils::Network::Response response) {
        int new_player_id = response.PopParam<int>();
        float x = response.PopParam<double>();
        float y = response.PopParam<double>();

        _game->createOtherPlayer(new_player_id, x, y);
    };


    _handlePlayerMap[Utils::PlayerEnum::PlayerDie] = [this](Utils::Network::Response response) {
        std::unique_ptr<Rtype::Command::Player::Die> cmd = _network->convertACommandToCommand<Rtype::Command::Player::Die>(_network->createCommand(static_cast<uint8_t>(Utils::InfoTypeEnum::Player), static_cast<uint8_t>(Utils::PlayerEnum::PlayerDie)));
        int playerId = response.PopParam<int>();
    };


    _handlePlayerMap[Utils::PlayerEnum::PlayerMove] = [this](Utils::Network::Response response) {
        int player_id = response.PopParam<int>();
        double x = response.PopParam<double>();
        double y = response.PopParam<double>();

        _game->movePlayer(player_id, x, y);
    };

    _handlePlayerMap[Utils::PlayerEnum::PlayerAttack] = [this](Utils::Network::Response response) {
        std::unique_ptr<Rtype::Command::Player::Attack> cmd = _network->convertACommandToCommand<Rtype::Command::Player::Attack>(_network->createCommand(static_cast<uint8_t>(Utils::InfoTypeEnum::Player), static_cast<uint8_t>(Utils::PlayerEnum::PlayerAttack)));

        int missileId = response.PopParam<int>();

    };


    _handlePlayerMap[Utils::PlayerEnum::PlayerGotPowerUp] = [this](Utils::Network::Response response) {

        int playerId = response.PopParam<int>();

        std::cerr << "Player Move playerId not used" << std::endl;

    };


    _handlePlayerMap[Utils::PlayerEnum::PlayerHitAWall] = [this](Utils::Network::Response response) {
        std::unique_ptr<Rtype::Command::Player::Hit_wall> cmd = _network->convertACommandToCommand<Rtype::Command::Player::Hit_wall>(_network->createCommand(static_cast<uint8_t>(Utils::InfoTypeEnum::Player), static_cast<uint8_t>(Utils::PlayerEnum::PlayerHitAWall)));
        int playerId = response.PopParam<int>();
    };


    _handlePlayerMap[Utils::PlayerEnum::PlayerScore] = [this](Utils::Network::Response response) {
        std::unique_ptr<Rtype::Command::Player::Score> cmd = _network->convertACommandToCommand<Rtype::Command::Player::Score>(_network->createCommand(static_cast<uint8_t>(Utils::InfoTypeEnum::Player), static_cast<uint8_t>(Utils::PlayerEnum::PlayerScore)));        int score = response.PopParam<int>();

        std::cerr << "The unused Score is: " << score << std::endl;

    };


}

void Rtype::udpClient::setHandleEnemyMap() {
    _handleEnemyMap[Utils::EnemyEnum::EnemySpawn] = [this](Utils::Network::Response response) {
        int enemyId = response.PopParam<int>();
        float x = response.PopParam<double>();
        float y = response.PopParam<double>();
    };

    _handleEnemyMap[Utils::EnemyEnum::EnemyDie] = [this](Utils::Network::Response response) {
        int enemyId = response.PopParam<int>();
    };

    _handleEnemyMap[Utils::EnemyEnum::EnemyMove] = [this](Utils::Network::Response response) {
    };

    _handleEnemyMap[Utils::EnemyEnum::EnemyAttack] = [this](Utils::Network::Response response) {
        int enemyId = response.PopParam<int>();
    };
};

void Rtype::udpClient::setHandlePowerUpMap() {
    _handlePowerUpMap[Utils::PowerUpEnum::PowerUpSpawn] = [this](Utils::Network::Response response) {
        //TODO: Implement PowerUpSpawn
    };
    _handlePowerUpMap[Utils::PowerUpEnum::PowerUpDisappear] = [this](Utils::Network::Response response) {
        //TODO: Implement PowerUpDisappear
    };
    _handlePowerUpMap[Utils::PowerUpEnum::PowerUpAttack] = [this](Utils::Network::Response response) {
        //TODO Implemnt PowerUpAttack
    };
}


void Rtype::udpClient::setHandleProjectileMap() {
    _handleProjectileMap[Utils::ProjectileEnum::ProjectileFired] = [this](Utils::Network::Response response) {
        int entityID = response.PopParam<int>();
        int projectileID = response.PopParam<int>();

        _game->createProjectile(entityID, projectileID);
    };

    _handleProjectileMap[Utils::ProjectileEnum::ProjectileHit] = [this](Utils::Network::Response response) {
    };
}

void Rtype::udpClient::setHandleBossMap() {
    _handleBossMap[Utils::BossEnum::BossSpawn] = [this](Utils::Network::Response response) {
        int BossType = response.PopParam<int>();
        float X = response.PopParam<double>();
        float Y = response.PopParam<double>();
    };

    _handleBossMap[Utils::BossEnum::BossDie] = [this](Utils::Network::Response response) {
        int BossType = response.PopParam<int>();
    };

    _handleBossMap[Utils::BossEnum::BossAttack] = [this](Utils::Network::Response response) {
        int BossType = response.PopParam<int>();
        int BossAttackType = response.PopParam<int>();
    };

    _handleBossMap[Utils::BossEnum::BossAttack] = [this](Utils::Network::Response response) {
        int BossID = response.PopParam<int>();
    };
}


void Rtype::udpClient::handleResponse(Utils::Network::Response clientResponse)
{
    Utils::InfoTypeEnum cmd_category = clientResponse.GetInfoType();

    if (((int)cmd_category != 1 && (int)clientResponse.GetInfoFunction() != 2) &&
        ((int)cmd_category != 5 && (int)clientResponse.GetInfoFunction() != 0)) {
        CONSOLE_INFO("Handle Response: ", (int)cmd_category)
        CONSOLE_INFO("Handle Response: ", (int)clientResponse.GetInfoFunction())
    }
    switch (cmd_category) {
    case Utils::InfoTypeEnum::GameInfo:
        _handleGameInfoMap[static_cast<Utils::GameInfoEnum>(clientResponse.GetInfoFunction())](clientResponse);
        break;
    case Utils::InfoTypeEnum::Player:
        _handlePlayerMap[static_cast<Utils::PlayerEnum>(clientResponse.GetInfoFunction())](clientResponse);
        break;
    case  Utils::InfoTypeEnum::Enemy:
        _handleEnemyMap[static_cast<Utils::EnemyEnum>(clientResponse.GetInfoFunction())](clientResponse);
        break;
    case  Utils::InfoTypeEnum::PowerUp:
        _handlePowerUpMap[static_cast<Utils::PowerUpEnum>(clientResponse.GetInfoFunction())](clientResponse);
        break;
    case  Utils::InfoTypeEnum::Projectile:
        _handleProjectileMap[static_cast<Utils::ProjectileEnum>(clientResponse.GetInfoFunction())](clientResponse);
        break;
    case  Utils::InfoTypeEnum::Boss:
        _handleBossMap[static_cast<Utils::BossEnum>(clientResponse.GetInfoFunction())](clientResponse);
        break;
    default:
        std::cerr << "Unknown command category." << std::endl;
        break;
    }
}

void Rtype::udpClient::connectClient()
{
    std::unique_ptr<Rtype::Command::GameInfo::Client_connection> cmd_connection = CONVERT_ACMD_TO_CMD(Rtype::Command::GameInfo::Client_connection, Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::NewClientConnected);
    cmd_connection->setCommonPart(_network->getSocket(), _network->getSenderEndpoint(), _network->getAckToSend());
    _network->addCommandToInvoker(std::move(cmd_connection));
}
