/*
** EPITECH PROJECT, 2024
** R-Type
** File description: Client Class
** udp_client
*/

#include "udp_client.hpp"
#include "../Utils/Protocol/Protocol.hpp"

Rtype::udpClient::udpClient(const std::string &serverAddr, const int serverPort)
    : _id(-1), _ioContext(), _socket(std::make_shared<udp::socket>(_ioContext, udp::endpoint(udp::v4(), 0))),
      _serverEndpoint(boost::asio::ip::make_address(serverAddr), serverPort),
      _commandInvoker("Client"), _commandFactory(), _game(Rtype::Game())
{
    _receiverThread = std::thread([this]() { _ioContext.run(); });
    read_server();
    send_data("New client trying to connect to the server.");
}

Rtype::udpClient::~udpClient()
{
    if (_socket->is_open()) {
        _socket->cancel();
        _socket->close();
    }
    _ioContext.stop();
    if (_receiverThread.joinable()) {
        _receiverThread.join();
    }
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
    std::cout << "Starting game loop..." << std::endl;
    sleep(1);
    std::cout << "Starting game loop..." << std::endl;
    _game.run();
}

void Rtype::udpClient::runNetwork()
{
    _ioContext.run();
}

void Rtype::udpClient::send_data(const std::string &data)
{
    std::string message = std::to_string(_id) + ": " + data;

    _socket->async_send_to(boost::asio::buffer(message), _serverEndpoint,
    [](const boost::system::error_code& error, std::size_t bytes_transferred) {
        if (error) {
            std::cerr << "Send failed: " << error.message() << std::endl;
        } else {
            std::cout << "Sent " << bytes_transferred << " bytes" << std::endl;
        }
    });
}

void Rtype::udpClient::read_server()
{
    udp::endpoint sender_endpoint;
    Utils::Network::Response clientResponse;
    Utils::Network::bytes data;

    _socket->async_receive_from(boost::asio::buffer(_receiverBuffer), sender_endpoint,
    [this](const boost::system::error_code& error, std::size_t bytes_recv) {
        if (!error && bytes_recv > 0) {
            received_data_handler(bytes_recv);
        } else if (error == boost::asio::error::operation_aborted) {
            std::cout << "Receive operation aborted." << std::endl;
        } else if (error) {
            std::cerr << "Error receiving data: " << error.message() << std::endl;
        }

        if (!error) {
            read_server();
        }
    });
    data = Utils::Network::bytes(std::begin(_receiverBuffer), std::end(_receiverBuffer));
    clientResponse = Utils::Network::Protocol::ParseMsg(true, data);
    handleResponse(clientResponse);
}


void Rtype::udpClient::setHandleMaps()
{
    setHandleGameInfoMap();
}

void Rtype::udpClient::setHandleGameInfoMap()
{
    _handleGameInfoMap[Utils::GameInfoEnum::NewClientConnected] = [this](Utils::Network::Response response) {
        std::unique_ptr<Rtype::Command::GameInfo::Client_connection> cmd = convertACommandToCommand<Rtype::Command::GameInfo::Client_connection>(_commandFactory.createCommand(static_cast<uint8_t>(Utils::InfoTypeEnum::GameInfo), static_cast<uint8_t>(Utils::GameInfoEnum::NewClientConnected)));
        _id = response.PopParam<int>();

        cmd->set_client(_serverEndpoint);
        cmd->setCommonPart(_socket, _serverEndpoint, _ackToSend);
        _commandInvoker.addCommand(std::move(cmd));
    };

    _handleGameInfoMap[Utils::GameInfoEnum::GamesAvailable] = [this](Utils::Network::Response response) {
        std::unique_ptr<Rtype::Command::GameInfo::Games_available> cmd = convertACommandToCommand<Rtype::Command::GameInfo::Games_available>(_commandFactory.createCommand(static_cast<uint8_t>(Utils::InfoTypeEnum::GameInfo), static_cast<uint8_t>(Utils::GameInfoEnum::GamesAvailable)));
        int codeRoom = response.PopParam<int>();
        (void) codeRoom;
        std::cerr << "WARNING: Unused variable codeRoom in udpClient::setHandleGameInfoMap" << codeRoom << std::endl;

        cmd->set_client(_serverEndpoint);
        cmd->setCommonPart(_socket, _serverEndpoint, _ackToSend);
        _commandInvoker.addCommand(std::move(cmd));
    };

    _handleGameInfoMap[Utils::GameInfoEnum::CreateGame] = [this](Utils::Network::Response response) {
        std::unique_ptr<Rtype::Command::GameInfo::Create_game> cmd = convertACommandToCommand<Rtype::Command::GameInfo::Create_game>(_commandFactory.createCommand(static_cast<uint8_t>(Utils::InfoTypeEnum::GameInfo), static_cast<uint8_t>(Utils::GameInfoEnum::CreateGame)));
        int codeRoom = response.PopParam<int>();
        (void) codeRoom;
        std::cerr << "WARNING: Unused variable codeRoom in udpClient::setHandleGameInfoMap" << codeRoom << std::endl;

        cmd->set_client(_serverEndpoint);
        cmd->setCommonPart(_socket, _serverEndpoint, _ackToSend);
        _commandInvoker.addCommand(std::move(cmd));
    };

    _handleGameInfoMap[Utils::GameInfoEnum::JoinGame] = [this](Utils::Network::Response response) {
        std::unique_ptr<Rtype::Command::GameInfo::Join_game> cmd = convertACommandToCommand<Rtype::Command::GameInfo::Join_game>(_commandFactory.createCommand(static_cast<uint8_t>(Utils::InfoTypeEnum::GameInfo), static_cast<uint8_t>(Utils::GameInfoEnum::JoinGame)));
        bool accepted = response.PopParam<bool>();
        int codeRoom = response.PopParam<int>();

        if (!accepted) {
            std::cerr << "Joining game failed." << std::endl;
            return;
        }
        cmd->set_client(_serverEndpoint, codeRoom);
        cmd->setCommonPart(_socket, _serverEndpoint, _ackToSend);
        _commandInvoker.addCommand(std::move(cmd));
    };

    _handleGameInfoMap[Utils::GameInfoEnum::GameWonLost] = [this](Utils::Network::Response response) {
        std::unique_ptr<Rtype::Command::GameInfo::Game_result> cmd = convertACommandToCommand<Rtype::Command::GameInfo::Game_result>(_commandFactory.createCommand(static_cast<uint8_t>(Utils::InfoTypeEnum::GameInfo), static_cast<uint8_t>(Utils::GameInfoEnum::GameWonLost)));
        bool won = response.PopParam<bool>();

        if (won) {
            std::cerr << "You won!" << std::endl;
        } else {
            std::cerr << "You lost!" << std::endl;
        }

        cmd->set_client();
        cmd->setCommonPart(_socket, _serverEndpoint, _ackToSend);
        _commandInvoker.addCommand(std::move(cmd));
    };

    _handleGameInfoMap[Utils::GameInfoEnum::SafetyCheck] = [this](Utils::Network::Response response) {
        std::cerr << "Safety check received." << std::endl;
    };

    _handleGameInfoMap[Utils::GameInfoEnum::LevelComplete] = [this](Utils::Network::Response response) {
        std::unique_ptr<Rtype::Command::GameInfo::Level_complete> cmd = convertACommandToCommand<Rtype::Command::GameInfo::Level_complete>(_commandFactory.createCommand(static_cast<uint8_t>(Utils::InfoTypeEnum::GameInfo), static_cast<uint8_t>(Utils::GameInfoEnum::LevelComplete)));
        int level = response.PopParam<int>();

        std::cerr << "Level " << level << " completed." << std::endl;
        std::cerr << "Unused variable level in udpClient::setHandleGameInfoMap: " << level << std::endl;

        cmd->set_client();
        cmd->setCommonPart(_socket, _serverEndpoint, _ackToSend);
        _commandInvoker.addCommand(std::move(cmd));
    };
};


void Rtype::udpClient::setHandlePlayerMap() {
    _handlePlayerMap[Utils::PlayerEnum::PlayerSpawnOnGame] = [this](Utils::Network::Response response) {
        std::unique_ptr<Rtype::Command::Player::Spawn> cmd = convertACommandToCommand<Rtype::Command::Player::Spawn>(_commandFactory.createCommand(static_cast<uint8_t>(Utils::InfoTypeEnum::Player), static_cast<uint8_t>(Utils::PlayerEnum::PlayerSpawnOnGame)));

        std::cerr << "Warning Player Spawn Not Handle" << std::endl;

        cmd->set_client();
        cmd->setCommonPart(_socket, _serverEndpoint, _ackToSend);
        _commandInvoker.addCommand(std::move(cmd));
    };


    _handlePlayerMap[Utils::PlayerEnum::PlayerDie] = [this](Utils::Network::Response response) {
        std::unique_ptr<Rtype::Command::Player::Die> cmd = convertACommandToCommand<Rtype::Command::Player::Die>(_commandFactory.createCommand(static_cast<uint8_t>(Utils::InfoTypeEnum::Player), static_cast<uint8_t>(Utils::PlayerEnum::PlayerDie)));

        std::cerr << "Warning Player Die Not Handle" << std::endl;

        cmd->set_client();
        cmd->setCommonPart(_socket, _serverEndpoint, _ackToSend);
        _commandInvoker.addCommand(std::move(cmd));

    };


    _handlePlayerMap[Utils::PlayerEnum::PlayerMove] = [this](Utils::Network::Response response) {
        std::unique_ptr<Rtype::Command::Player::Move> cmd = convertACommandToCommand<Rtype::Command::Player::Move>(_commandFactory.createCommand(static_cast<uint8_t>(Utils::InfoTypeEnum::Player), static_cast<uint8_t>(Utils::PlayerEnum::PlayerMove)));

        int playerId = response.PopParam<int>();

        std::cerr << "Player Move playerId not used" << std::endl;

        cmd->set_client(_serverEndpoint, response.PopParam<int>(), response.PopParam<int>());
        cmd->setCommonPart(_socket, _serverEndpoint, _ackToSend);
        _commandInvoker.addCommand(std::move(cmd));

    };

    _handlePlayerMap[Utils::PlayerEnum::PlayerAttack] = [this](Utils::Network::Response response) {
        std::unique_ptr<Rtype::Command::Player::Attack> cmd = convertACommandToCommand<Rtype::Command::Player::Attack>(_commandFactory.createCommand(static_cast<uint8_t>(Utils::InfoTypeEnum::Player), static_cast<uint8_t>(Utils::PlayerEnum::PlayerAttack)));

        int playerId = response.PopParam<int>();

        std::cerr << "Player Move playerId not used" << std::endl;

        cmd->set_client(_serverEndpoint, response.PopParam<int>());
        cmd->setCommonPart(_socket, _serverEndpoint, _ackToSend);
        _commandInvoker.addCommand(std::move(cmd));

    };


    _handlePlayerMap[Utils::PlayerEnum::PlayerGotPowerUp] = [this](Utils::Network::Response response) {
        std::unique_ptr<Rtype::Command::Player::Power_up> cmd = convertACommandToCommand<Rtype::Command::Player::Power_up>(_commandFactory.createCommand(static_cast<uint8_t>(Utils::InfoTypeEnum::Player), static_cast<uint8_t>(Utils::PlayerEnum::PlayerGotPowerUp)));

        int playerId = response.PopParam<int>();

        std::cerr << "Player Move playerId not used" << std::endl;

        cmd->set_client(_serverEndpoint, response.PopParam<int>());
        cmd->setCommonPart(_socket, _serverEndpoint, _ackToSend);
        _commandInvoker.addCommand(std::move(cmd));

    };


    _handlePlayerMap[Utils::PlayerEnum::PlayerHitAWall] = [this](Utils::Network::Response response) {
        std::unique_ptr<Rtype::Command::Player::Hit_wall> cmd = convertACommandToCommand<Rtype::Command::Player::Hit_wall>(_commandFactory.createCommand(static_cast<uint8_t>(Utils::InfoTypeEnum::Player), static_cast<uint8_t>(Utils::PlayerEnum::PlayerHitAWall)));
    
        int playerId = response.PopParam<int>();

        std::cerr << "Player Move playerId not used" << std::endl;
    
        cmd->set_client(_serverEndpoint);
        cmd->setCommonPart(_socket, _serverEndpoint, _ackToSend);
        _commandInvoker.addCommand(std::move(cmd));

    };


    _handlePlayerMap[Utils::PlayerEnum::PlayerScore] = [this](Utils::Network::Response response) {
        std::unique_ptr<Rtype::Command::Player::Score> cmd = convertACommandToCommand<Rtype::Command::Player::Score>(_commandFactory.createCommand(static_cast<uint8_t>(Utils::InfoTypeEnum::Player), static_cast<uint8_t>(Utils::PlayerEnum::PlayerScore)));

        int score = response.PopParam<int>();

        std::cerr << "The unused Score is: " << score << std::endl;

        cmd->set_client(_serverEndpoint);
        cmd->setCommonPart(_socket, _serverEndpoint, _ackToSend);
        _commandInvoker.addCommand(std::move(cmd));

    };


}


void Rtype::udpClient::handleResponse(Utils::Network::Response clientResponse)
{
    Utils::InfoTypeEnum cmd_category = clientResponse.GetInfoType();

    switch (cmd_category) {
    case Utils::InfoTypeEnum::GameInfo:
        _handleGameInfoMap[static_cast<Utils::GameInfoEnum>(clientResponse.GetInfoFunction())](clientResponse);
        break;
    case Utils::InfoTypeEnum::Player:
        _handlePlayerMap[static_cast<Utils::PlayerEnum>(clientResponse.GetInfoFunction())](clientResponse);
        break;
    case 
    default:
        break;
    }
}



void Rtype::udpClient::received_data_handler(std::size_t bytes_recv)
{
    std::string msg(_receiverBuffer.data(), bytes_recv);
    std::cout << "Received from server: [" << msg << "]" << std::endl;

    if (std::strncmp("Your new ID is ", msg.c_str(), 15) == 0) {
        _id = atoi(msg.c_str() + 15);
    }
}
