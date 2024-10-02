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
            udpClient(const std::string &serverAddr, const int serverPort);
            
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
            void run();

        private:
            /**
             * @brief Start receiving data from server.
             */
            void start_receive();
            
            /**
             * @brief Handle the received data from server.
             * @param error Potential error code while receiving data from server.
             * @param bytes_recv Number of bytes received from server.
             */
            void handle_receive(const boost::system::error_code &error, std::size_t bytes_recv);

            int _id;
            boost::asio::io_context _ioContext;
            udp::socket _socket;
            udp::endpoint _serverEndpoint;
            udp::endpoint _senderEndpoint;
            std::array<char, 1024> _receiverBuffer;
            std::thread _receiverThread;
    };
}
