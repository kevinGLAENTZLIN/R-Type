/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** temp
*/

#pragma once

#include <boost/asio.hpp>
#include <iostream>
#include <thread>
#include <vector>
#include <array>

using boost::asio::ip::udp;

class udpClient
{
public:
    udpClient(const std::string &serverAddr, const int serverPort);
    ~udpClient();

    void send_data(const std::string &data);
    void run();

private:
    void start_receive();
    void handle_receive(const boost::system::error_code &error, std::size_t bytes_recv);

    int _id;
    boost::asio::io_context _ioContext;
    udp::socket _socket;
    udp::endpoint _serverEndpoint;
    udp::endpoint _senderEndpoint;
    std::array<char, 1024> _receiverBuffer;
    std::thread _receiverThread;
};
