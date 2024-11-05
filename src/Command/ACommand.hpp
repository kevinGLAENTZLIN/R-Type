/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ACommand
*/

#pragma once

#if defined(_WIN32)
	#define NOGDI
	#define NOUSER
#endif

#if defined(_WIN32)
	#undef near
	#undef far
#endif

#include <iostream>
#include <cstdarg>
#include <map>
#include <vector>
#include <memory>
#include <ctime>
#include <iomanip>
#include <chrono>
#include <boost/asio.hpp>

#include "./ICommand.hh"
#include "../Utils/ParametersMap/ParametersMap.hpp"
#include "../Utils/Protocol/Protocol.hpp"
#include "../Server/Client_info.hpp"

using boost::asio::ip::udp;

#define CONSOLE_INFO(a, b) std::cout << "\033[1;31m[" << [](){ auto now = std::chrono::system_clock::now(); std::time_t now_time_t = std::chrono::system_clock::to_time_t(now); return std::put_time(std::localtime(&now_time_t), "%H:%M:%S"); }() << "]" << a << b << "\033[0m" << std::endl;

namespace Rtype
{
    namespace Command
    {
        class ACommand: public ICommand {
            public:
                ACommand() = default;
                ~ACommand() = default;

                virtual void execute_client_side() = 0;
                virtual void execute_server_side() = 0;

                /**
                * @brief Sets common attributes for sending a message.
                *
                * This method configures common parameters for sending commands to a client,
                * including the sender socket, the destination endpoint, and the acknowledgment (ack).
                *
                * @param sender_socket The socket used to send the message.
                * @param endpoint The destination endpoint.
                * @param ack The acknowledgment (ack) for the message.
                */
                void setCommonPart(std::shared_ptr<udp::socket> sender_socket, udp::endpoint endpoint, int ack)
                {
                    _senderSocket = sender_socket;
                    _endpoint = endpoint;
                    _ack = ack;
                }

                /**
                * @brief Sets common attributes for sending a message, including the game instance.
                *
                * This method configures common parameters for sending commands to a client,
                * including the sender socket, destination endpoint, acknowledgment (ack),
                * and a pointer to the `Game` object.
                *
                * @param sender_socket The socket used to send the message.
                * @param endpoint The destination endpoint.
                * @param ack The acknowledgment (ack) for the message.
                * @param game A pointer to the `Game` object associated with the command.
                */
                void setCommonPart(std::shared_ptr<udp::socket> sender_socket, udp::endpoint endpoint, int ack, std::shared_ptr<Rtype::Game> game)
                {
                    _senderSocket = sender_socket;
                    _endpoint = endpoint;
                    _ack = ack;
                    _game = game;
                }

                /**
                * @brief Sets common attributes for sending a message with a modifiable acknowledgment.
                *
                * This method configures common parameters for sending commands,
                * including the sender socket, destination endpoint, and an acknowledgment
                * passed by reference, allowing modification outside of the method.
                *
                * @param sender_socket The socket used to send the message.
                * @param endpoint The destination endpoint.
                * @param ack Reference to the acknowledgment (ack) for the message.
                */
                void setCommonPart(std::shared_ptr<udp::socket> sender_socket, udp::endpoint endpoint, int &ack)
                {
                    _senderSocket = sender_socket;
                    _endpoint = endpoint;
                    _ack = ack;
                }

                /**
                * @brief Sets the client information.
                *
                * Assigns a `client_info` object to contain information about the client who
                * sends or receives commands, facilitating tracking of sent or received commands.
                *
                * @param clientInfo Pointer to the `client_info` object of the client.
                */
                void setClientInfo(std::shared_ptr<Rtype::client_info> clientInfo)
                {
                    _clientInfo = clientInfo;
                }

                /**
                * @brief Sets the origin of the command (Client or Server).
                *
                * This method assigns the origin source of the command, facilitating
                * the selection of expected parameter types for each function.
                *
                * @param origins The origin source as a string, "Client" or "Server".
                */
                void setOrigins(std::string origins)
                {
                    _origins = origins;
                }

                /**
                * @brief Sets the game associated with the command.
                *
                * Associates a `Game` object to identify the game context in which
                * the command is executed.
                *
                * @param game Pointer to the `Game` object associated with the command.
                */
                void setGame(std::shared_ptr<Rtype::Game> game)
                {
                    _game = game;
                }

            protected:
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
                void sendToEndpoint(Rtype::client_info &clientInfo, Utils::InfoTypeEnum function_type, T function_index, ...)
                {
                    va_list params;
                    va_list params_copy;
                    Utils::Network::bytes msg;
                    std::string params_type = getParamsType(function_type, function_index);

                    va_start(params, function_index);
                    va_copy(params_copy, params);
                    msg = Utils::Network::Protocol::CreateMsg(clientInfo.getAckToSend(), function_type, function_index, Utils::Network::Protocol::va_listToVector(params_copy, params_type));
                    clientInfo.pushCmdToHistory(msg);
                    va_end(params);
                    if (_senderSocket) {
                        _senderSocket->async_send_to(boost::asio::buffer(msg), _endpoint,
                        [this] (boost::system::error_code ec, std::size_t recvd_bytes) {});
                    }
                }

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
                void sendToEndpoint(Rtype::client_info &clientInfo, udp::endpoint endpoint, Utils::InfoTypeEnum function_type, T function_index, ...)
                {
                    va_list params;
                    va_list params_copy;
                    Utils::Network::bytes msg;
                    std::string params_type = getParamsType(function_type, function_index);

                    va_start(params, function_index);
                    va_copy(params_copy, params);
                    msg = Utils::Network::Protocol::CreateMsg(clientInfo.getAckToSend(), function_type, function_index, Utils::Network::Protocol::va_listToVector(params_copy, params_type));
                    clientInfo.pushCmdToHistory(msg);
                    va_end(params);
                    if (_senderSocket) {
                        _senderSocket->async_send_to(boost::asio::buffer(msg), endpoint,
                        [this] (boost::system::error_code ec, std::size_t recvd_bytes) {});
                    }
                }


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
                void sendToEndpoint(Utils::InfoTypeEnum function_type, T function_index, ...)
                {
                    va_list params;
                    va_list params_copy;
                    Utils::Network::bytes msg;
                    std::string params_type = getParamsType(function_type, function_index);

                    va_start(params, function_index);
                    va_copy(params_copy, params);
                    msg = Utils::Network::Protocol::CreateMsg(_ack, function_type, function_index, Utils::Network::Protocol::va_listToVector(params_copy, params_type));
                    va_end(params);
                    if (_senderSocket) {
                        _senderSocket->async_send_to(boost::asio::buffer(msg), _endpoint,
                        [this] (boost::system::error_code ec, std::size_t recvd_bytes) {});
                    }
                }

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
                void sendToEndpoint(udp::endpoint endpoint, Utils::InfoTypeEnum function_type, T function_index, ...)
                {
                    va_list params;
                    va_list params_copy;
                    Utils::Network::bytes msg;
                    std::string params_type = getParamsType(function_type, function_index);

                    va_start(params, function_index);
                    va_copy(params_copy, params);
                    msg = Utils::Network::Protocol::CreateMsg(_ack, function_type, function_index, Utils::Network::Protocol::va_listToVector(params_copy, params_type));
                    va_end(params);
                    if (_senderSocket) {
                        _senderSocket->async_send_to(boost::asio::buffer(msg), endpoint,
                        [this] (boost::system::error_code ec, std::size_t recvd_bytes) {});
                    }
                }


                /**
                 * @brief Gets the parameter types for a given function.
                 *
                 * This method returns the parameter types for a given function type and index.
                 *
                 * @param function_type The type of the function.
                 * @param function_index The index of the function.
                 * @return The parameter types as a string.
                 */
                template <Utils::FunctionIndex T>
                std::string getParamsType(Utils::InfoTypeEnum function_type, T function_index) const
                {
                    std::string params_type;
                    Utils::ParametersMap::init_map();

                    if (_origins == "Server")
                        params_type = Utils::ParametersMap::getParameterTypePerFunctionClient(function_type, static_cast<uint8_t>(function_index));
                    else if (_origins == "Client")
                        params_type = Utils::ParametersMap::getParameterTypePerFunctionServer(function_type, static_cast<uint8_t>(function_index));
                    else
                        throw std::runtime_error("Unknown origin");
                    return params_type;
                }

                std::shared_ptr<udp::socket> _senderSocket;
                udp::endpoint _endpoint;
                int _ack;
                std::string _origins;
                std::shared_ptr<Rtype::client_info> _clientInfo;
                std::shared_ptr<Rtype::Game> _game;
        };
    }
}
