/*
** EPITECH PROJECT, 2024
** R-Type
** File description: Server Class
** udp_server
*/

#include "udp_server.hh"

udpServer::udpServer(boost::asio::io_service& io_service, short port)
: _socket(io_service, udp::endpoint(udp::v4(), port))
{
    read_clients();
}

void udpServer::read_clients()
{
    _socket.async_receive_from(boost::asio::buffer(_data, max_length), _senderEndpoint,
    [this] (boost::system::error_code ec, std::size_t recvd_bytes) {
        if (!ec && recvd_bytes > 0)
            received_data_handler(recvd_bytes);
        else
            read_clients();
    });
}

void udpServer::received_data_handler(std::size_t recvd_bytes)
{
    if (check_ACK()) {
        std::cout << "[" << recvd_bytes << "] " << _data << std::endl;
        send_back_to_client();
    } else {
        read_clients();
    }
}

bool udpServer::check_ACK()
{
    return true;
}

void udpServer::send_back_to_client()
{
    std::string myStr = "Sender endpoint : ";
    myStr += _senderEndpoint.address().to_string().c_str();
    myStr += " port ";
    myStr += std::to_string((int)_senderEndpoint.port());
    myStr += " Message : ";
    myStr += _data; 
    std::cout << "Send back: [" << myStr << "]" << std::endl;

    _socket.async_send_to(boost::asio::buffer(myStr), _senderEndpoint,
    [this] (boost::system::error_code ec, std::size_t recvd_bytes) {
        read_clients();
    });
}
