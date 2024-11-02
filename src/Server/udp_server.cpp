/*
** EPITECH PROJECT, 2024
** R-Type
** File description: Server Class
** udp_server
*/

/**
 * @file udp_server.cpp
 * @brief Implementation of the Rtype::udpServer class for UDP server communication.
 */

#include "udp_server.hpp"

Rtype::udpServer::udpServer(boost::asio::io_service& io_service, short port)
{
    _network = std::make_shared<Rtype::Network>(io_service, port, "Server");
    _clients = std::make_shared<std::map<int, std::shared_ptr<Rtype::client_info>>>();
    _games = std::make_shared<std::map<int, std::shared_ptr<Rtype::Game_info>>>();
    Utils::ParametersMap::init_map();
    std::memset(_data, 0, max_length);
    setHandleMaps();
    read_clients();
}

void Rtype::udpServer::read_clients()
{
    _network->executeInvoker();
    _network->getSocket()->async_receive_from(boost::asio::buffer(_data, max_length), _senderEndpoint,
    [this] (boost::system::error_code ec, std::size_t recvd_bytes) {
        Utils::Network::Response clientResponse;
        Utils::Network::bytes data;

        if (!ec && recvd_bytes > 0 && recvd_bytes < max_length) {
            _network->setSenderEndpoint(_senderEndpoint);
            std::memset(_data + recvd_bytes, 0, max_length - recvd_bytes);
            data = Utils::Network::bytes(std::begin(_data), std::end(_data));
            clientResponse = Utils::Network::Protocol::ParseMsg(false, data);
            handleResponse(clientResponse);
        }
        for (auto game: *_games)
            if (game.second->getToSetNetwork()) {
                game.second->setNetwork(_network);
                game.second->runGame();
            }
        read_clients();
    });
}

int Rtype::udpServer::get_sender_id()
{
    return get_client_id_by_addr(_network->getSenderEndpoint().address().to_string(), (int)_network->getSenderEndpoint().port());
}

int Rtype::udpServer::get_client_id_by_addr(std::string addr, int port)
{
    for (auto client: *_clients)
        if (client.second->getAddr() == addr && client.second->getPort() == port)
            return client.first;
    return -1;
}

int Rtype::udpServer::get_sender_client_id()
{
    return get_client_id_by_addr(_network->getSenderEndpoint().address().to_string(), (int)_network->getSenderEndpoint().port());
}

bool Rtype::udpServer::is_client_by_addr(std::string addr, int port)
{
    return get_client_id_by_addr(addr, port) != -1;
}

void Rtype::udpServer::disconnect_client(int client_id)
{
    _clients->erase(client_id);
}

void Rtype::udpServer::setHandleMaps() {
    setHandleGameInfoMap();
    setHandlePlayerMap();
    setHandlePowerUpMap();
    setHandleProjectileMap();
}

void Rtype::udpServer::setHandleGameInfoMap() {

    _handleGameInfoMap[Utils::GameInfoEnum::NewClientConnected] = [this](Utils::Network::Response clientResponse) {
        try {

        std::unique_ptr<Rtype::Command::GameInfo::Client_connection> cmd = convertACommandToCommand<Rtype::Command::GameInfo::Client_connection>(_network->createCommand(static_cast<uint8_t>(Utils::InfoTypeEnum::GameInfo), static_cast<uint8_t>(Utils::GameInfoEnum::NewClientConnected)));
        cmd->set_server(_clients, (int)_network->getSenderEndpoint().port(), _network->getSenderEndpoint().address().to_string());
        cmd->setCommonPart(_network->getSocket(), _network->getSenderEndpoint(), 0);
        _network->addCommandToInvoker(std::move(cmd));
        } catch (std::exception &e) {
            std::cerr << "is from here" << e.what() << std::endl;
            std::cerr << "is from here" << e.what() << std::endl;
            std::cerr << "is from here" << e.what() << std::endl;
            std::cerr << "is from here" << e.what() << std::endl;
            std::cerr << "is from here" << e.what() << std::endl;
        }
 
    };

    _handleGameInfoMap[Utils::GameInfoEnum::CreateGame] = [this](Utils::Network::Response clientResponse) {
        std::unique_ptr<Rtype::Command::GameInfo::Create_game> cmd = convertACommandToCommand<Rtype::Command::GameInfo::Create_game>(_network->createCommand(static_cast<uint8_t>(Utils::InfoTypeEnum::GameInfo), static_cast<uint8_t>(Utils::GameInfoEnum::CreateGame)));
        cmd->set_server(_games);
        cmd->setClientInfo(_clients->at(get_sender_client_id()));
        cmd->setCommonPart(_network->getSocket(), _network->getSenderEndpoint(), _clients->at(get_sender_client_id())->getAckToSend());
        _network->addCommandToInvoker(std::move(cmd));
    };

    _handleGameInfoMap[Utils::GameInfoEnum::GamesAvailable] = [this](Utils::Network::Response clientResponse) {
        std::unique_ptr<Rtype::Command::GameInfo::Games_available> cmd = convertACommandToCommand<Rtype::Command::GameInfo::Games_available>(_network->createCommand(static_cast<uint8_t>(Utils::InfoTypeEnum::GameInfo), static_cast<uint8_t>(Utils::GameInfoEnum::GamesAvailable)));
        cmd->set_server(_games);
        cmd->setClientInfo(_clients->at(get_sender_client_id()));
        cmd->setCommonPart(_network->getSocket(), _network->getSenderEndpoint(), _clients->at(get_sender_client_id())->getAckToSend());
        _network->addCommandToInvoker(std::move(cmd));
    };

    _handleGameInfoMap[Utils::GameInfoEnum::SafetyCheck] = [this](Utils::Network::Response clientResponse) {
        std::cerr << "SafetyCheck" << std::endl;
    };

    _handleGameInfoMap[Utils::GameInfoEnum::JoinGame] = [this](Utils::Network::Response clientResponse) {
        int id_room = clientResponse.PopParam<int>();
        std::unique_ptr<Rtype::Command::GameInfo::Join_game> join_cmd = CONVERT_ACMD_TO_CMD(Rtype::Command::GameInfo::Join_game, Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::JoinGame);
        std::unique_ptr<Rtype::Command::Player::Spawn> spawn_cmd = CONVERT_ACMD_TO_CMD(Rtype::Command::Player::Spawn, Utils::InfoTypeEnum::Player, Utils::PlayerEnum::PlayerSpawnOnGame);
        bool join_game = true;

        if (_games->find(id_room) != _games->end()) {
            join_cmd->set_server(_games->at(id_room), _clients->at(get_sender_client_id()));
            join_game = _games->at(id_room)->isGameAvailable();
        } else {
            join_cmd->set_server();
            join_game = false;
        }
        join_cmd->setCommonPart(_network->getSocket(), _network->getSenderEndpoint(), _clients->at(get_sender_client_id())->getAckToSend());
        join_cmd->setClientInfo(_clients->at(get_sender_client_id()));
        _network->addCommandToInvoker(std::move(join_cmd));
        if (join_game) {
            CONSOLE_INFO("Player is joining game: ", id_room)
            spawn_cmd->set_server(_clients, get_sender_client_id(), -10., 0.);
            spawn_cmd->setCommonPart(_network->getSocket(), _network->getSenderEndpoint(), _clients->at(get_sender_client_id())->getAckToSend(), _games->at(id_room)->getGame());
            spawn_cmd->setClientInfo(_clients->at(get_sender_client_id()));
            _network->addCommandToInvoker(std::move(spawn_cmd));
            CONSOLE_INFO("Player is spawning in game: ", id_room)
        }
    };

    _handleGameInfoMap[Utils::GameInfoEnum::LevelComplete] = [this](Utils::Network::Response clientResponse) {
        std::unique_ptr<Rtype::Command::GameInfo::Level_complete> cmd = convertACommandToCommand<Rtype::Command::GameInfo::Level_complete>(_network->createCommand(static_cast<uint8_t>(Utils::InfoTypeEnum::GameInfo), static_cast<uint8_t>(Utils::GameInfoEnum::LevelComplete)));
        cmd->set_server(_games->at(clientResponse.PopParam<int>()));
        cmd->setCommonPart(_network->getSocket(), _network->getSenderEndpoint(), _clients->at(get_sender_client_id())->getAckToSend());
        cmd->setClientInfo(_clients->at(get_sender_client_id()));
        _network->addCommandToInvoker(std::move(cmd));
    };

    _handleGameInfoMap[Utils::GameInfoEnum::MissingPackages] = [this](Utils::Network::Response clientResponse) {
        int ack = 0;
        Utils::Network::bytes msg;
        std::unique_ptr<Rtype::Command::GameInfo::Missing_packages> cmd;

        for (std::size_t i = 0; i < 4; i++) {
            ack = clientResponse.PopParam<int>();
            if (ack == 0)
                break;
            msg = _clients->at(get_sender_client_id())->getCmdFromHistory(ack);
            cmd = CONVERT_ACMD_TO_CMD(Rtype::Command::GameInfo::Missing_packages, Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::MissingPackages);
            cmd->setCommonPart(_network->getSocket(), _network->getSenderEndpoint(), _network->getAckToSend());
            cmd->set_server(msg);
            _network->addCommandToInvoker(std::move(cmd));
        }
    };
}

void Rtype::udpServer::setHandlePlayerMap() {
    _handlePlayerMap[Utils::PlayerEnum::PlayerSpawnOnGame] = [this](Utils::Network::Response clientResponse) {
        std::unique_ptr<Rtype::Command::Player::Spawn> cmd = convertACommandToCommand<Rtype::Command::Player::Spawn>(_network->createCommand(static_cast<uint8_t>(Utils::InfoTypeEnum::Player), static_cast<uint8_t>(Utils::PlayerEnum::PlayerSpawnOnGame)));
        int gameID = _clients->at(get_sender_client_id())->getRoom();

        cmd->set_server(_games->at(gameID)->getPlayers(),get_sender_client_id(), _clients->at(get_sender_client_id())->getX(), _clients->at(get_sender_client_id())->getY());
        cmd->setCommonPart(_network->getSocket(), _network->getSenderEndpoint(), _clients->at(get_sender_client_id())->getAckToSend());
        _network->addCommandToInvoker(std::move(cmd));
    };

    _handlePlayerMap[Utils::PlayerEnum::PlayerDie] = [this](Utils::Network::Response clientResponse) {
        std::unique_ptr<Rtype::Command::Player::Die> cmd = convertACommandToCommand<Rtype::Command::Player::Die>(_network->createCommand(static_cast<uint8_t>(Utils::InfoTypeEnum::Player), static_cast<uint8_t>(Utils::PlayerEnum::PlayerDie)));
        int gameID = _clients->at(get_sender_client_id())->getRoom();

        cmd->set_server(_games->at(gameID)->getPlayers(),get_sender_client_id());
        cmd->setCommonPart(_network->getSocket(), _network->getSenderEndpoint(), _clients->at(get_sender_client_id())->getAckToSend());
        _network->addCommandToInvoker(std::move(cmd));
    };

    _handlePlayerMap[Utils::PlayerEnum::PlayerMove] = [this](Utils::Network::Response clientResponse) {
        std::unique_ptr<Rtype::Command::Player::Move> cmd = CONVERT_ACMD_TO_CMD(Rtype::Command::Player::Move, Utils::InfoTypeEnum::Player, Utils::PlayerEnum::PlayerMove);
        int gameID = _clients->at(get_sender_client_id())->getRoom();
        double x = clientResponse.PopParam<double>();
        double y = clientResponse.PopParam<double>();

        cmd->set_server(_games->at(gameID)->getPlayers(), get_sender_client_id(), x, y);
        cmd->setCommonPart(_network->getSocket(), udp::endpoint(), _clients->at(get_sender_client_id())->getAckToSend());
        _network->addCommandToInvoker(std::move(cmd));
    };

    _handlePlayerMap[Utils::PlayerEnum::PlayerAttack] = [this](Utils::Network::Response clientResponse) {
        std::unique_ptr<Rtype::Command::Player::Attack> cmd = convertACommandToCommand<Rtype::Command::Player::Attack>(_network->createCommand(static_cast<uint8_t>(Utils::InfoTypeEnum::Player), static_cast<uint8_t>(Utils::PlayerEnum::PlayerAttack)));
        int gameID = _clients->at(get_sender_client_id())->getRoom();

        cmd->set_server(_games->at(gameID)->getPlayers(), clientResponse.PopParam<int>());
        cmd->setCommonPart(_network->getSocket(), _network->getSenderEndpoint(), _clients->at(get_sender_client_id())->getAckToSend());
        _network->addCommandToInvoker(std::move(cmd));
    };

    _handlePlayerMap[Utils::PlayerEnum::PlayerGotPowerUp] = [this](Utils::Network::Response clientResponse) {
        std::unique_ptr<Rtype::Command::Player::Power_up> cmd = convertACommandToCommand<Rtype::Command::Player::Power_up>(_network->createCommand(static_cast<uint8_t>(Utils::InfoTypeEnum::Player), static_cast<uint8_t>(Utils::PlayerEnum::PlayerGotPowerUp)));
        int gameID = _clients->at(get_sender_client_id())->getRoom();


        cmd->set_server(_games->at(gameID)->getPlayers(), get_sender_client_id(), clientResponse.PopParam<int>());
        cmd->setCommonPart(_network->getSocket(), _network->getSenderEndpoint(), _clients->at(get_sender_client_id())->getAckToSend());
        _network->addCommandToInvoker(std::move(cmd));
    };

    _handlePlayerMap[Utils::PlayerEnum::PlayerHitAWall] = [this](Utils::Network::Response clientResponse) {
        std::unique_ptr<Rtype::Command::Player::Hit_wall> cmd = convertACommandToCommand<Rtype::Command::Player::Hit_wall>(_network->createCommand(static_cast<uint8_t>(Utils::InfoTypeEnum::Player), static_cast<uint8_t>(Utils::PlayerEnum::PlayerHitAWall)));
        int gameID = _clients->at(get_sender_client_id())->getRoom();

        cmd->set_server(_games->at(gameID)->getPlayers(), get_sender_client_id());
        cmd->setCommonPart(_network->getSocket(), _network->getSenderEndpoint(), _clients->at(get_sender_client_id())->getAckToSend());
        _network->addCommandToInvoker(std::move(cmd));
    };

    _handlePlayerMap[Utils::PlayerEnum::PlayerScore] = [this](Utils::Network::Response clientResponse) {
        std::unique_ptr<Rtype::Command::Player::Score> cmd = convertACommandToCommand<Rtype::Command::Player::Score>(_network->createCommand(static_cast<uint8_t>(Utils::InfoTypeEnum::Player), static_cast<uint8_t>(Utils::PlayerEnum::PlayerScore)));
        int gameID = _clients->at(get_sender_client_id())->getRoom();
        
        std::cerr <<  "Hardcoded score" << std::endl;
        cmd->set_server(_games->at(gameID)->getPlayers(), 4242);
        _network->addCommandToInvoker(std::move(cmd));
    };
}

void Rtype::udpServer::setHandlePowerUpMap() {
    std::cerr << "PowerUpNotImplemented" << std::endl;
}

void Rtype::udpServer::setHandleProjectileMap() {
    _handleProjectileMap[Utils::ProjectileEnum::ProjectileFired] = [this](Utils::Network::Response clientResponse) {
        std::unique_ptr<Rtype::Command::Projectile::Fired> cmd = CONVERT_ACMD_TO_CMD(Rtype::Command::Projectile::Fired, Utils::InfoTypeEnum::Projectile, Utils::ProjectileEnum::ProjectileFired);
        int gameID = _clients->at(get_sender_client_id())->getRoom();

        cmd->set_server(_games->at(gameID)->getPlayers(), get_sender_client_id(), _games->at(gameID)->getNbProjectiles()); //! tmp
        cmd->setCommonPart(_network->getSocket(), _network->getSenderEndpoint(), _clients->at(get_sender_client_id())->getAckToSend());
        _network->addCommandToInvoker(std::move(cmd));
        _games->at(gameID)->accNbProjectiles();
    };

    _handleProjectileMap[Utils::ProjectileEnum::ProjectileHit] = [this](Utils::Network::Response clientResponse) {
        (void)clientResponse;
        std::cerr << "ProjectileHitNotImplemented" << std::endl;
    };
}

void Rtype::udpServer::handleResponse(Utils::Network::Response clientResponse)
{
    Utils::InfoTypeEnum cmd_category = clientResponse.GetInfoType();
    std::cout << "Handle Response: " << (int)cmd_category << std::endl;

    if (((int)cmd_category != 1 && (int)clientResponse.GetInfoFunction() != 2) &&
        ((int)cmd_category != 5 && (int)clientResponse.GetInfoFunction() != 0)) {
        CONSOLE_INFO("Handle Response: ", (int)cmd_category)
        CONSOLE_INFO("Handle Response: ", (int)clientResponse.GetInfoFunction())
    }
    switch (cmd_category)
    {
    case Utils::InfoTypeEnum::GameInfo:
        _handleGameInfoMap[static_cast<Utils::GameInfoEnum>(clientResponse.GetInfoFunction())](clientResponse);
        break;
    case Utils::InfoTypeEnum::Player:
        _handlePlayerMap[static_cast<Utils::PlayerEnum>(clientResponse.GetInfoFunction())](clientResponse);
        break;
    case Utils::InfoTypeEnum::PowerUp:
        _handlePowerUpMap[static_cast<Utils::PowerUpEnum>(clientResponse.GetInfoFunction())](clientResponse);
        break;
    case Utils::InfoTypeEnum::Projectile:
        _handleProjectileMap[static_cast<Utils::ProjectileEnum>(clientResponse.GetInfoFunction())](clientResponse);
        break;
    case Utils::InfoTypeEnum::Enemy:
        std::cerr << "EnemyNotImplemented" << std::endl;
        break;
    case Utils::InfoTypeEnum::Boss:
        std::cerr << "BossNotImplemented" << std::endl;
    default:
        std::cerr << "Unknown command" << std::endl;
        break;
    }
}
