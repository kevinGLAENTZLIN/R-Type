/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Client_connection
*/

#include "Client_connection.hh"

void Rtype::Command::GameInfo::Client_connection::set_client(udp::endpoint endpoint)
{
	_endpoint = endpoint;
}

void Rtype::Command::GameInfo::Client_connection::set_server(udp::endpoint endpoint, std::map<int, std::shared_ptr<Rtype::client_info>> &clients)
{
	_endpoint = endpoint;
    _clients = clients;
}

Rtype::Command::GameInfo::Client_connection::~Client_connection()
{
}

void Rtype::Command::GameInfo::Client_connection::execute_client_side()
{
	sendToEndpoint(Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::NewClientConnected);
}

void Rtype::Command::GameInfo::Client_connection::execute_server_side()
{
	sendToEndpoint(Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::NewClientConnected, get_available_client_id());
}

int Rtype::Command::GameInfo::Client_connection::get_available_client_id()
{
    bool available = false;

    for (int i = 0; i < INT32_MAX; i++) {
        available = true;
        for (auto client: _clients)
            available &= client.second->getId() != i;
        if (available)
            return i;
    }
    return -1;
}
