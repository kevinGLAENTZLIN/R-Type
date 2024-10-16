/*
** EPITECH PROJECT, 2024
** R-Type
** File description: Client Class
** udp_client
*/

#include "udp_client.hh"
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

void Rtype::udpClient::handleResponse(Utils::Network::Response clientResponse)
{
    Utils::InfoTypeEnum cmd_category = clientResponse.GetInfoType();
    uint8_t cmd_index = clientResponse.GetInfoFunction();

    if (cmd_category == Utils::InfoTypeEnum::GameInfo && cmd_index == static_cast<uint8_t>(Utils::GameInfoEnum::NewClientConnected)) {
        _id = clientResponse.PopParam<int>();
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
