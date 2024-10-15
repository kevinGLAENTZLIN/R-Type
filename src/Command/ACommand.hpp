/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ACommand
*/

#pragma once

#include <iostream>
#include <cstdarg>
#include <map>
#include <vector>
#include <boost/asio.hpp>
#include "./ICommand.hh"
#include "../Utils/ParametersMap/ParametersMap.hpp"

using boost::asio::ip::udp;

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

                void setCommonPart(std::shared_ptr<udp::socket> sender_socket, udp::endpoint endpoint, std::map<int, std::tuple<int, int, std::vector<std::string>>> &history, int &ack)
                {
                    _senderSocket = sender_socket;
                    _endpoint = endpoint;
                    _history = history;
                    _ack = ack;
                }

            private:
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
                void send_to_endpoint(Utils::InfoTypeEnum function_type, T function_index, ...)
                {
                        va_list params;

                        va_start(params, function_index);
                        if (!_history.empty())
                            pushCmdToHistory(function_type, function_index, params);
                        else
                            std::cerr << "Warning, the history has not been set" << std::endl;
                        // Encrypt message
                        va_end(params);
                        _senderSocket->async_send_to(boost::asio::buffer("The encrypted message"), _endpoint,
                        [this] (boost::system::error_code ec, std::size_t recvd_bytes) {
                            std::cout << "I have no idea if I have to do stuff to make it works" << std::endl;
                        });
                }

                /**
                 * @brief Adds a command to the client's command history.
                 * 
                 * This method handle a variadic list of parameters, converts them to strings,
                 * and stores them in the client's history.
                 * 
                 * @param function_type The type of the command.
                 * @param function_index The index of the command.
                 * @param params The variadic parameters for the command.
                 */
                template <Utils::FunctionIndex T>
                void pushCmdToHistory(Utils::InfoTypeEnum function_type, T function_index, std::va_list params)
                {
                    int nb_params = Utils::ParametersMap::getNbParameterPerFunctionClient(function_type, function_index);
                    std::string params_type = Utils::ParametersMap::getParameterTypePerFunctionClient(function_type, function_index);
                    std::vector<std::string> vector_params;

                    for (int i = 0; i < nb_params; i++) {
                        switch (params_type[i]) {
                            case 'b':
                                vector_params.push_back(std::to_string(va_arg(params, int)));
                                break;
                            case 'c':
                                vector_params.push_back(std::to_string(va_arg(params, int)));
                                break;
                            case 'i':
                                vector_params.push_back(std::to_string(va_arg(params, int)));
                                break;
                            case 'f':
                                vector_params.push_back(std::to_string(va_arg(params, double)));
                                break;
                            default:
                                std::cerr << "Unsupported type" << std::endl;
                                break;
                        }
                    }
                    _history[_ack] = std::make_tuple(function_type, function_index, vector_params);
                    _ack += 1;
                }

                std::shared_ptr<udp::socket> _senderSocket;
                udp::endpoint _endpoint;
                std::map<int, std::tuple<int, int, std::vector<std::string>>> _history; // [Ack, (cmd_type, cmd_index, vector_params)]
                int _ack;
        };
    }
}