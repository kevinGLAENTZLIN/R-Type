/*
** EPITECH PROJECT, 2024
** R-Type
** File description: Client Class
** udp_client
*/

#include "udp_client.hh"

udpClient::udpClient(const std::string &serverAddr, const int serverPort)
    : _id(-1), _ioContext(), _socket(_ioContext, udp::endpoint(udp::v4(), 0)),
      _serverEndpoint(boost::asio::ip::make_address(serverAddr), serverPort)
{
    _receiverThread = std::thread([this]() { _ioContext.run(); });
    start_receive();
}

udpClient::~udpClient()
{
    _ioContext.stop();
    if (_receiverThread.joinable()) {
        _receiverThread.join();
    }
}

void udpClient::run()
{
    _ioContext.run();
}

void udpClient::send_data(const std::string &data)
{
    std::string message = std::to_string(_id) + ":" + data;

    _socket.async_send_to(boost::asio::buffer(message), _serverEndpoint,
    [](const boost::system::error_code& error, std::size_t bytes_transferred) {
        if (error) {
            std::cerr << "Send failed: " << error.message() << std::endl;
        } else {
            std::cout << "Sent " << bytes_transferred << " bytes" << std::endl;
        }
    });
}

void udpClient::start_receive()
{
    _socket.async_receive_from(boost::asio::buffer(_receiverBuffer), _senderEndpoint,
    [this](const boost::system::error_code& error, std::size_t bytes_recv) {
        handle_receive(error, bytes_recv);
    });
}

void udpClient::handle_receive(const boost::system::error_code& error, std::size_t bytes_recv)
{
    if (!error && bytes_recv > 0) {
        std::cout << "Received from server: [" << std::string(_receiverBuffer.data(), bytes_recv) << "]" << std::endl;
    }
    start_receive();
}
