/*
** EPITECH PROJECT, 2024
** R-Type
** File description: Server Class
** udp_server
*/

/**
 * @file udp_server.hpp
 * @brief Declaration of the Rtype::udpServer class for UDP server communication.
 */

#pragma once

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <boost/asio.hpp>
#include "Client_info.hpp"
#include "Game_info.hh"
#include "../Utils/ParametersMap/ParametersMap.hpp"
#include "../Command/Factory/Factory.hh"
#include "../Command/Invoker/Command_invoker.hh"

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
             * @brief Retrieves the last sender client ID.
             * @return Client ID if found, -1 otherwise.
             */
            int get_sender_client_id();

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

            /**
             * @brief Sends a command to the last sender client.
             * 
             * This function uses variadic arguments to handle parameters of the command to send.
             * Also it pushes the command with its parameters to the client's history.
             * 
             * @param function_type The type of command to be sent.
             * @param function_index The index of the command to be sent.
             * @param ... Parameters for the command to send in the right order.
             */
            template <Utils::FunctionIndex T>
            void send_to_client(Utils::InfoTypeEnum function_type, T function_index, ...)
            {
                    va_list params;

                    va_start(params, function_index);
                    _clients[get_sender_client_id()].pushCmdToHistory(function_type, function_index, params);
                    // Encrypt message
                    va_end(params);
                    // _socket.async_send_to(boost::asio::buffer(msg), client_endpoint,
                    // [this] (boost::system::error_code ec, std::size_t recvd_bytes) {
                    //     read_clients();
                    // });
            }

            /**
             * @brief Sends a command to a specific client identified by its IP address and port.
             * 
             * This function uses variadic arguments to handle parameters of the command to send.
             * Also it pushes the command with its parameters to the client's history.
             * 
             * @param addr_ip The IP address of the client.
             * @param port The port of the client.
             * @param function_type The type of command to be sent.
             * @param function_index The index of the command to be sent.
             * @param ... Parameters for the command to send in the right order.
             */
            template <Utils::FunctionIndex T>
            void send_to_client(std::string addr_ip, int port, Utils::InfoTypeEnum function_type, T function_index, ...)
            {
                    va_list params;

                    va_start(params, function_index);
                    _clients[get_client_id_by_addr(addr_ip, port)].pushCmdToHistory(function_type, function_index, params);
                    // Encrypt message
                    va_end(params);
                    // _socket.async_send_to(boost::asio::buffer(msg), client_endpoint,
                    // [this] (boost::system::error_code ec, std::size_t recvd_bytes) {
                    //     read_clients();
                    // });
            }

            /**
             * @brief Sends a command to a specific client identified by its IP address and port.
             * 
             * This function uses variadic arguments to handle parameters of the command to send.
             * Also it pushes the command with its parameters to the client's history.
             * 
             * @param addr Client's address as a pair of IP and port.
             * @param function_type The type of command to be sent.
             * @param function_index The index of the command to be sent.
             * @param ... Parameters for the command to send in the right order.
             */
            template <Utils::FunctionIndex T>
            void send_to_client(std::pair<std::string, int> addr, Utils::InfoTypeEnum function_type, T function_index, ...)
            {
                va_list params;

                va_start(params, function_index);
                _clients[get_client_id_by_addr(addr.first, addr.second)].pushCmdToHistory(function_type, function_index, params);
                // Encrypt message
                va_end(params);
                // _socket.async_send_to(boost::asio::buffer(msg), client_endpoint,
                // [this] (boost::system::error_code ec, std::size_t recvd_bytes) {
                //     read_clients();
                // });
            }

            /**
             * @brief Sends a command to a specific client identified by its ID.
             * 
             * This function uses variadic arguments to handle parameters of the command to send.
             * Also it pushes the command with its parameters to the client's history.
             * 
             * @param id ID of the client.
             * @param function_type The type of command to be sent.
             * @param function_index The index of the command to be sent.
             * @param ... Parameters for the command to send in the right order.
             */
            template <Utils::FunctionIndex T>
            void send_to_client(int id, Utils::InfoTypeEnum function_type, T function_index, ...)
            {
                va_list params;

                va_start(params, function_index);
                _clients[id].pushCmdToHistory(function_type, function_index, params);
                // Encrypt message
                va_end(params);
                // _socket.async_send_to(boost::asio::buffer(msg), client_endpoint,
                // [this] (boost::system::error_code ec, std::size_t recvd_bytes) {
                //     read_clients();
                // });
            }

            /**
             * @brief Sends a command to all clients identified.
             * 
             * This function uses variadic arguments to handle parameters of the command to send.
             * Also it pushes the command with its parameters to the client's history.
             * 
             * @param function_type The type of command to be sent.
             * @param function_index The index of the command to be sent.
             * @param ... Parameters for the command to send in the right order.
             */
            template <Utils::FunctionIndex T>
            void send_to_clients(Utils::InfoTypeEnum function_type, T function_index, ...)
            {
                va_list params;
                va_list tmp;

                va_start(params, function_index);
                for(auto client: _clients) {
                    va_copy(tmp, params);
                    client.second.pushCmdToHistory(function_type, function_index, tmp);
                    // Encrypt message
                    va_end(tmp);
                    // _socket.async_send_to(boost::asio::buffer(msg), client_endpoint,
                    // [this] (boost::system::error_code ec, std::size_t recvd_bytes) {
                    //     read_clients();
                    // });
                }
                va_end(params);
            }

            udp::socket _socket;
            udp::endpoint _senderEndpoint;
            enum { max_length = 1024 }; // Maximum length of the receive buffer.
            char _data[max_length];
            std::map<int, Rtype::client_info> _clients;
            std::vector<Rtype::Game_info> _games;
            Rtype::Command::Command_invoker _commandInvoker;
            Rtype::Command::Factory _commandFactory;
    };
}
