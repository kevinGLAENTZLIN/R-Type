/*
** EPITECH PROJECT, 2024
** R-Type
** File description: Server Class
** udp_server
*/

/**
 * @file udp_server.hh
 * @brief Declaration of the Rtype::udpServer class for UDP server communication.
 */

#pragma once

#include <cstdlib>
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

namespace Rtype {
    /**
     * @class udpServer
     * @brief Class to manage an UDP server.
     */
    class udpServer
    {
        public:
            /**
             * @brief Constructor for the udpServer class.
             * @param io_service The io_service object for handling asynchronous methods.
             * @param port The port on which the server will listen.
             */
            udpServer(boost::asio::io_service& io_service, short port);

            /**
             * @brief Read asynchronously data from clients.
             */
            void read_clients();

            /**
             * @brief Sends a response back to the client.
             */
            void send_back_to_client();

            /**
             * @brief Handles the received data from clients.
             * @param recvd_bytes Number of bytes received.
             */
            void received_data_handler(std::size_t recvd_bytes);

            /**
             * @brief Checks for an ACK from the client.
             * @return true if ACK is received, false otherwise.
             */
            bool check_ACK();

        private:
            udp::socket _socket;
            udp::endpoint _senderEndpoint;
            enum { max_length = 1024 }; // Maximum length of the receive buffer.
            char _data[max_length];
    };
}
