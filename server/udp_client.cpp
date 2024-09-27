/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** new_udp_client
*/

#include "./new_udp_client.hh"

udpClient::udpClient(const std::string serverAddr, const int serverPort)
    : _id(-1), _ioContext(), _socket(_ioContext, udp::endpoint(udp::v4(), 0)),
      _serverEndpoint(boost::asio::ip::make_address(serverAddr), serverPort)
{
    client_loop();
    std::thread([this]() { _ioContext.run(); }).detach();
}

udpClient::~udpClient()
{
    _ioContext.stop();
}

void udpClient::send_data(const std::string data)
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

void udpClient::recept_data()
{
    udp::endpoint sender_endpoint;

    _socket.async_receive_from(boost::asio::buffer(_recv_buffer), sender_endpoint,
    [this](const boost::system::error_code& error, std::size_t bytes_recv) {
        if (!error && bytes_recv > 0) {
            std::cout << "Received from server: [" << std::string(_recv_buffer.data(), bytes_recv) << "]" << std::endl;
        }
        client_loop();
    });
}

void udpClient::client_loop()
{
    recept_data();
}

int main(int argc, char **argv)
{
    if (argc != 4) {
        std::cout << "Usage: udp_client [server] [port] [Message]" << std::endl;
        exit(84);
    }
    udpClient client(argv[1], std::stoi(argv[2]));

    client.send_data(argv[3]);
    return 0;
}
