/*
** EPITECH PROJECT, 2024
** R-Type
** File description: Client Class
** udp_client
*/

#include "udp_client.hh"

/**
 * @file udp_client.cpp
 * @brief Implementation of the Rtype::udpClient class for UDP communication with a server.
 */

Rtype::udpClient::udpClient(const std::string &serverAddr, const int serverPort)
    : _id(-1), _ioContext(), _socket(std::make_shared<udp::socket>(udp::socket(_ioContext, udp::endpoint(udp::v4(), 0)))),
      _serverEndpoint(boost::asio::ip::make_address(serverAddr), serverPort),
      _commandInvoker("Client"), _commandFactory(), _game(Rtype::Game())
{
    _receiverThread = std::thread([this]() { _ioContext.run(); });// Added
    read_server();
    send_data("New client trying to connect to the server."); //! To refactor by the protocol control
}

Rtype::udpClient::~udpClient()
{
    _ioContext.stop();// Added
    if (_receiverThread.joinable()) {// Added
        _receiverThread.join();// Added
    }
    send_data("Client is disconnecting."); //! To refactor by the protocol control
}

void Rtype::udpClient::run()// Added
{
    _ioContext.run();
    _game.run();
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

    _socket->async_receive_from(boost::asio::buffer(_receiverBuffer), sender_endpoint,
    [this](const boost::system::error_code& error, std::size_t bytes_recv) {
        if (!error && bytes_recv > 0) {
            received_data_handler(bytes_recv);
        }
        read_server();
    });
}

void Rtype::udpClient::received_data_handler(std::size_t bytes_recv)
{
    std::string msg(_receiverBuffer.data(), bytes_recv);

    std::cout << "Received from server: [" << msg << "]" << std::endl;
    if (std::strncmp("Your new ID is ", msg.c_str(), 15) == 0) { //! To refactor by the protocol control
        _id = atoi(msg.c_str() + 15);
    }
}
