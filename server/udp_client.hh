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
        udpClient(const std::string serverAddr, const int serverPort);
        ~udpClient();

        void send_data(const std::string data);

    private:
        void recept_data();
        void client_loop();

        int _id;
        boost::asio::io_context _ioContext;
        udp::socket _socket;
        udp::endpoint _serverEndpoint;
        std::array<char, 1024> _recv_buffer;
};
