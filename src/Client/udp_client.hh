/*
** EPITECH PROJECT, 2024
** R-Type
** File description: Client Class
** udp_client
*/

/**
 * @file udp_client.hh
 * @brief Declaration of the Rtype::udpClient class for UDP communication with a server.
 */

#pragma once

#include <boost/asio.hpp>
#include <iostream>
#include <thread>
#include <vector>
#include <array>
#include "../../Utils/ParametersMap/ParametersMap.hpp"
#include "../../Command/Factory/Factory.hh"
#include "../../Command/Invoker/Command_invoker.hh"
#include "Game/Game.hh"

using boost::asio::ip::udp;

namespace Rtype {
    /**
     * @class udpClient
     * @brief Class to manage a UDP client.
     */
    class udpClient
    {
    public:
        /**
         * @brief Constructor for the udpClient class.
         * @param serverAddr Server's IP address.
         * @param serverPort Server's port.
         */
        udpClient(const std::string &serverAddr, const int serverPort);// Added
            
        /**
         * @brief Destructor for the udpClient class.
         */
        ~udpClient();

        /**
         * @brief Send data to the server.
         * @param data The data to send.
         */
        void send_data(const std::string &data);
            
        /**
         * @brief Run the IO context.
         */
        void run();// Added

    private:
        /**
         * @brief Receiving data from server.
         */
        void read_server();
            
        /**
         * @brief Handle the received data from server.
         * @param bytes_recv Number of bytes received from server.
         */
        void received_data_handler(std::size_t bytes_recv);

        void runGame();

        int _id;
        boost::asio::io_context _ioContext;// Added
        std::shared_ptr<udp::socket> _socket;
        udp::endpoint _serverEndpoint;
        std::array<char, 1024> _receiverBuffer;
        std::thread _receiverThread;// Added
        Rtype::Command::Command_invoker _commandInvoker;
        Rtype::Command::Factory _commandFactory;
        Rtype::Game _game;
    };
}
