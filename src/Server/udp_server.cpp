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

Rtype::udpServer::udpServer(boost::asio::io_service& io_service, short port):
    _socket(std::make_shared<udp::socket>(udp::socket(io_service, udp::endpoint(udp::v4(), port)))), _clients(), _games(),
    _commandInvoker("Server"), _commandFactory()
{
    Utils::ParametersMap::init_map();
    std::memset(_data, 0, max_length);
    read_clients();
}

void Rtype::udpServer::read_clients()
{
    _commandInvoker.executeCommand();
    _socket->async_receive_from(boost::asio::buffer(_data, max_length), _senderEndpoint,
    [this] (boost::system::error_code ec, std::size_t recvd_bytes) {
        Utils::Network::Response clientResponse;
        Utils::Network::bytes data;

        if (!ec && recvd_bytes > 0 && recvd_bytes < max_length) {
            std::memset(_data + recvd_bytes, 0, max_length - recvd_bytes);
            data = Utils::Network::bytes(std::begin(_data), std::end(_data));
            clientResponse = Utils::Network::Protocol::ParseMsg(false, data);
            handleResponse(clientResponse);
        }
        read_clients();
    });
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
        _clients[id] = std::make_shared<Rtype::client_info>(Rtype::client_info(id, (int)_senderEndpoint.port(), _senderEndpoint.address().to_string()));
        connect_client_to_game(id, 4242); //! To refactor by the protocol control & for Defense purpose only
    }
    return id;
}

// ! Refactor: to remove -> handle by Command
int Rtype::udpServer::get_available_client_id()
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

int Rtype::udpServer::get_client_id_by_addr(std::string addr, int port)
{
    for (auto client: _clients)
        if (client.second->getAddr() == addr && client.second->getPort() == port)
            return client.first;
    return -1;
}

int Rtype::udpServer::get_sender_client_id()
{
    return get_client_id_by_addr(_senderEndpoint.address().to_string(), (int)_senderEndpoint.port());
}

bool Rtype::udpServer::is_client_by_addr(std::string addr, int port)
{
    return get_client_id_by_addr(addr, port) != -1;
}

void Rtype::udpServer::disconnect_client(int client_id)
{
    _clients.erase(client_id);
}

void Rtype::udpServer::connect_client_to_game(int client_id, int game_room)
{
    if (client_id == -1 || game_room <= 0 || _clients[client_id]->getRoom() != -1)
        return;
    for (auto game = _games->begin(); game != _games->end(); ++game) {
        if (game->get()->getRoomId() == game_room) {
            game->get()->connectPlayer(_clients[client_id]);
            return;
        }
    }
    Game_info tmp(game_room);
    _games->push_back(std::make_shared<Game_info>(std::move(tmp)));
    _games->back()->connectPlayer(_clients[client_id]);
}

void Rtype::udpServer::handleResponse(Utils::Network::Response clientResponse)
{
    Utils::InfoTypeEnum cmd_category = clientResponse.GetInfoType();

    switch (cmd_category)
    {
    case Utils::InfoTypeEnum::GameInfo:
        handleGameInfo(clientResponse);
        break;
    default:
        break;
    }
}

void Rtype::udpServer::handleGameInfo(Utils::Network::Response clientResponse)
{
    Utils::GameInfoEnum cmd_index = static_cast<Utils::GameInfoEnum>(clientResponse.GetInfoFunction());

    switch (cmd_index)
    {
    case Utils::GameInfoEnum::NewClientConnected :
        CONSOLE_INFO("New client is connecting: ", "");
        std::unique_ptr<Rtype::Command::GameInfo::Client_connection> cmd_connection = convertACommandToCommand<Rtype::Command::GameInfo::Client_connection>(_commandFactory.createCommand(static_cast<uint8_t>(Utils::InfoTypeEnum::GameInfo), static_cast<uint8_t>(cmd_index)));
        cmd_connection->set_server(_senderEndpoint, _clients);
        cmd_connection->setCommonPart(_socket, _senderEndpoint, 0);
        _commandInvoker.addCommand(std::move(cmd_connection));

        // std::unique_ptr<Rtype::Command::GameInfo::Join_game> cmd_join_game = convertACommandToCommand<Rtype::Command::GameInfo::Join_game>(_commandFactory.createCommand(static_cast<uint8_t>(Utils::InfoTypeEnum::GameInfo), static_cast<uint8_t>(Utils::GameInfoEnum::JoinGame)));
        // cmd_join_game->set_server(_senderEndpoint, );
        // cmd_join_game->setCommonPart(_socket, _senderEndpoint, _clients[get_sender_client_id()]->getAckToSend());
        // _commandInvoker.addCommand(std::move(cmd_join_game));
        break;
    }
}
