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
#include <map>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::udp;
using boost::asio::ip::address;

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
            int get_sender_id();
            int get_available_client_id();
            int get_client_id_by_addr(std::string addr, int port);
            bool is_client_by_addr(std::string addr, int port);

            void disconnect_client(int client_id);

            void send_to_client(std::string msg);
            void send_to_client(std::string addr_ip, int port, std::string msg);
            void send_to_client(std::pair<std::string, int> addr, std::string msg);
            void send_to_clients(std::string msg);


            udp::socket _socket;
            udp::endpoint _senderEndpoint;
            enum { max_length = 1024 }; // Maximum length of the receive buffer.
            char _data[max_length];
            std::map<int, std::pair<std::string, int>> _clientsAddr;

    };
}
