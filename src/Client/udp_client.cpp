/*
** EPITECH PROJECT, 2024
** R-Type
** File description: Client Class
** udp_client
*/

#include "udp_client.hpp"
#include "../Utils/Protocol/Protocol.hpp"

Rtype::udpClient::udpClient(const std::string &serverAddr, const int serverPort):
    _id(-1), _ackToSend(0), _ackToReceive(0), 
    _ioContext(), _socket(std::make_shared<udp::socket>(_ioContext, udp::endpoint(udp::v4(), 0))),
    _serverEndpoint(boost::asio::ip::make_address(serverAddr), serverPort),
    _commandInvoker("Client"), _commandFactory(), _game()
{
    connectClient();
    read_server();
}

Rtype::udpClient::~udpClient()
{
    if (_socket->is_open()) {
        _socket->cancel();
        _socket->close();
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
    _game.run();
}

void Rtype::udpClient::runNetwork()
{
    _ioContext.run();
}


void Rtype::udpClient::read_server()
{
    udp::endpoint sender_endpoint;

    _commandInvoker.executeCommand();
    _socket->async_receive_from(boost::asio::buffer(_receiverBuffer), sender_endpoint,
    [this](const boost::system::error_code& error, std::size_t bytes_recv) {
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

void Rtype::udpClient::handleResponse(Utils::Network::Response clientResponse)
{
    Utils::InfoTypeEnum cmd_category = clientResponse.GetInfoType();

    switch (cmd_category) {
    case Utils::InfoTypeEnum::GameInfo:
        handleGameInfo(clientResponse);
        break;
    default:
        break;
    }
}

void Rtype::udpClient::handleGameInfo(Utils::Network::Response clientResponse)
{
    Utils::GameInfoEnum cmd_index = static_cast<Utils::GameInfoEnum>(clientResponse.GetInfoFunction());

    switch (cmd_index) {
    case Utils::GameInfoEnum::NewClientConnected:
        _id = clientResponse.PopParam<int>();
        CONSOLE_INFO("Id set on client: ", _id);
        break;
    default:
        break;
    }
}

void Rtype::udpClient::connectClient()
{
    std::unique_ptr<Rtype::Command::GameInfo::Client_connection> cmd_connection = CONVERT_ACMD_TO_CMD(Rtype::Command::GameInfo::Client_connection, Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::NewClientConnected);
    cmd_connection->set_client(_serverEndpoint);
    cmd_connection->setCommonPart(_socket, _serverEndpoint, _ackToSend);
    _commandInvoker.addCommand(std::move(cmd_connection));
}
