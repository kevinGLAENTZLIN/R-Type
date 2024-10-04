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
#include "Client_info.hh"

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
            /**
             * @brief Retrieves the ID of the sender.
             * @return Sender's ID.
             */
            int get_sender_id();

            /**
             * @brief Finds an available client ID.
             * @return Available client ID.
             */
            int get_available_client_id();

            /**
             * @brief Retrieves the client ID by its address.
             * @param addr Client's IP address.
             * @param port Client's port number.
             * @return Client ID if found, -1 otherwise.
             */
            int get_client_id_by_addr(std::string addr, int port);

            /**
             * @brief Checks if a client exists by its address.
             * @param addr Client's IP address.
             * @param port Client's port number.
             * @return true if the client exists, false otherwise.
             */
            bool is_client_by_addr(std::string addr, int port);

            /**
             * @brief Disconnects a client by its ID.
             * @param client_id Client's ID.
             */
            void disconnect_client(int client_id);

            /**
             * @brief Sends a message to a client.
             * @param msg Message to send.
             */
            void send_to_client(std::string msg);

            /**
             * @brief Sends a message to a client identified by IP address and port.
             * @param addr_ip Client's IP address.
             * @param port Client's port number.
             * @param msg Message to send.
             */
            void send_to_client(std::string addr_ip, int port, std::string msg);

            /**
             * @brief Sends a message to a client identified by address.
             * @param addr Client's address as a pair of IP and port.
             * @param msg Message to send.
             */
            void send_to_client(std::pair<std::string, int> addr, std::string msg);

            /**
             * @brief Sends a message to all clients.
             * @param msg Message to send.
             */
            void send_to_clients(std::string msg);

            udp::socket _socket;
            udp::endpoint _senderEndpoint;
            enum { max_length = 1024 }; // Maximum length of the receive buffer.
            char _data[max_length];
            std::map<int, std::pair<std::string, int>> _clientsAddr;
            std::map<int, Rtype::client_info> _clients;
    };
}
