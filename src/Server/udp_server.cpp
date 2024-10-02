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

#include "udp_server.hh"

Rtype::udpServer::udpServer(boost::asio::io_service& io_service, short port)
: _socket(io_service, udp::endpoint(udp::v4(), port)), _clientsAddr()
{
    std::memset(_data, 0, max_length);
    read_clients();
}

void Rtype::udpServer::read_clients()
{
    _socket.async_receive_from(boost::asio::buffer(_data, max_length), _senderEndpoint,
    [this] (boost::system::error_code ec, std::size_t recvd_bytes) {
        if (!ec && recvd_bytes > 0 && recvd_bytes < max_length) {
            std::memset(_data + recvd_bytes, 0, max_length - recvd_bytes);
            received_data_handler(recvd_bytes);
        } else
            read_clients();
    });
}

void Rtype::udpServer::received_data_handler(std::size_t recvd_bytes)
{
    std::cout << "[" << recvd_bytes << "] " << _data << std::endl;
    int client_id = get_sender_id();

    if (check_ACK()) {
        if (std::strstr(_data, "Client is disconnecting.") != 0)
            disconnect_client(client_id);
    } else {
        std::cout << "/!\\ Warning ACK is not respected" << std::endl;
    }
    read_clients();
}

bool Rtype::udpServer::check_ACK()
{
    return true; //! To refactor by the protocol control
}

int Rtype::udpServer::get_sender_id()
{
    int id = get_client_id_by_addr(_senderEndpoint.address().to_string(), (int)_senderEndpoint.port());

    if (id == -1) {
        id = get_available_client_id();
        _clientsAddr[id] = std::make_pair<std::string, int>(_senderEndpoint.address().to_string(), (int)_senderEndpoint.port());
        send_to_client("Your new ID is " + std::to_string(id)); //! To refactor by the protocol control
    }
    return id;
}

int Rtype::udpServer::get_available_client_id()
{
    bool available = false;

    for (int i = 0; i < INT32_MAX; i++) {
        available = true;
        for (auto client: _clientsAddr)
            available &= client.first != i; 
        if (available)
            return i;
    }
    return -1;
}

int Rtype::udpServer::get_client_id_by_addr(std::string addr, int port)
{
    for (auto client: _clientsAddr)
        if (client.second.first == addr && client.second.second == port)
            return client.first;
    return -1;
}

bool Rtype::udpServer::is_client_by_addr(std::string addr, int port)
{
    return get_client_id_by_addr(addr, port) != -1;
}

void Rtype::udpServer::disconnect_client(int client_id)
{
    _clientsAddr.erase(client_id);
}

void Rtype::udpServer::send_to_client(std::string msg)
{
    _socket.async_send_to(boost::asio::buffer(msg), _senderEndpoint,
    [this] (boost::system::error_code ec, std::size_t recvd_bytes) {
        read_clients();
    });
}

void Rtype::udpServer::send_to_client(std::string addr_ip, int port, std::string msg)
{
    boost::asio::ip::port_type client_port(port);
    address client_addr(address::from_string(addr_ip));
    udp::endpoint client_endpoint(client_addr, client_port);

    _socket.async_send_to(boost::asio::buffer(msg), client_endpoint,
    [this] (boost::system::error_code ec, std::size_t recvd_bytes) {
        read_clients();
    });
}

void Rtype::udpServer::send_to_client(std::pair<std::string, int> addr, std::string msg)
{
    boost::asio::ip::port_type client_port(addr.second);
    address client_addr(address::from_string(addr.first));
    udp::endpoint client_endpoint(client_addr, client_port);

    _socket.async_send_to(boost::asio::buffer(msg), client_endpoint,
    [this] (boost::system::error_code ec, std::size_t recvd_bytes) {
        read_clients();
    });
}

void Rtype::udpServer::send_to_clients(std::string msg)
{
    for(auto client: _clientsAddr)
        send_to_client(client.second, msg);
}

