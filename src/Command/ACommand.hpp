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
                ACommand(udp::endpoint endpoint, std::map<int, std::tuple<int, int, std::vector<std::string>>> &history):
                    _endpoint(endpoint), _history(history) {};
                ~ACommand() = default;

                virtual void execute_client_side() = 0;
                virtual void execute_server_side() = 0;

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
                void send_to_client(Utils::InfoTypeEnum function_type, T function_index, ...)
                {
                        // va_list params;

                        // va_start(params, function_index);
                        // _clients[get_sender_client_id()].pushCmdToHistory(function_type, function_index, params);
                        // // Encrypt message
                        // va_end(params);
                        // // _socket.async_send_to(boost::asio::buffer(msg), client_endpoint,
                        // // [this] (boost::system::error_code ec, std::size_t recvd_bytes) {
                        // //     read_clients();
                        // // });
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
                    // int nb_params = Utils::ParametersMap::getNbParameterPerFunctionClient(function_type, function_index);
                    // std::string params_type = Utils::ParametersMap::getParameterTypePerFunctionClient(function_type, function_index);
                    // std::vector<std::string> vector_params;

                    // for (int i = 0; i < nb_params; i++) {
                    //     switch (params_type[i]) {
                    //         case 'b':
                    //             vector_params.push_back(std::to_string(va_arg(params, int)));
                    //             break;
                    //         case 'c':
                    //             vector_params.push_back(std::to_string(va_arg(params, int)));
                    //             break;
                    //         case 'i':
                    //             vector_params.push_back(std::to_string(va_arg(params, int)));
                    //             break;
                    //         case 'f':
                    //             vector_params.push_back(std::to_string(va_arg(params, double)));
                    //             break;
                    //         default:
                    //             std::cerr << "Unsupported type" << std::endl;
                    //             break;
                    //     }
                    // }
                    // _history[_AckToSend] = std::make_tuple(function_type, function_index, vector_params);
                    // setAckToSend();
                }

                udp::endpoint _endpoint;
                std::map<int, std::tuple<int, int, std::vector<std::string>>> _history; // [Ack, (cmd_type, cmd_index, vector_params)] 
        };
    }
}