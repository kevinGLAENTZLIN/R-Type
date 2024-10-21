/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** client_info
*/

#pragma once

#include <iostream>
#include <string>
#include <cstdarg>
#include <map>
#include <vector>
#include "../Utils/ParametersMap/ParametersMap.hpp"
#include <boost/asio.hpp>

using boost::asio::ip::udp;
using boost::asio::ip::address;

/**
 * @file Client_info.cpp
 * @brief Declaration of the client info class in order to handle information of the clients in the R-Type Game
 */


namespace Rtype {

    /**
     * @brief The client_info class represents information about a client in the R-Type game.
     * 
     * This class stores various attributes of a client such as their ID, position, address, 
     * and connection information. It also provides methods to manipulate and retrieve these attributes.
     */
    class client_info {
        public:
            /**
             * @brief Default constructor for client_info.
             */
            client_info();

            /**
             * @brief Parameterized constructor for client_info.
             * 
             * @param id The unique identifier for the client.
             * @param port The port number used by the client.
             * @param addr The IP address of the client.
             */
            client_info(int id, int port, std::string addr);

            /**
             * @brief Destructor for client_info.
             */
            ~client_info();

            /**
             * @brief Gets the unique identifier of the client.
             * 
             * @return The client's ID.
             */
            int getId() const;

            /**
             * @brief Sets the unique identifier of the client.
             * 
             * @param id The new ID for the client.
             */
            void setId(int id);

            /**
             * @brief Gets the X coordinate of the client.
             * 
             * @return The X coordinate.
             */
            int getX() const;

            /**
             * @brief Sets the X coordinate of the client.
             * 
             * @param x The new X coordinate.
             */
            void setX(int x);

            /**
             * @brief Gets the Y coordinate of the client.
             * 
             * @return The Y coordinate.
             */
            int getY() const;

            /**
             * @brief Sets the Y coordinate of the client.
             * 
             * @param y The new Y coordinate.
             */
            void setY(int y);

            /**
             * @brief Gets the expected ACK number for the client.
             * 
             * @return The expected ACK number.
             */
            int getAckToExpect() const;

            /**
             * @brief Increments the expected ACK number for the client.
             */
            void setAckToExpect();

            /**
             * @brief Gets the ACK number to be sent to the client.
             * 
             * @return The ACK number to be sent.
             */
            int getAckToSend() const;

            /**
             * @brief Increments the ACK number to be sent to the client.
             */
            void setAckToSend();

            /**
             * @brief Gets the game room number the client is in.
             * 
             * @return The game room number.
             */
            int getRoom() const;

            /**
             * @brief Sets the game room number for the client.
             * 
             * @param room The new game room number.
             */
            void setRoom(int room);

            /**
             * @brief Gets the port number used by the client.
             * 
             * @return The client's port number.
             */
            int getPort() const;

            /**
             * @brief Sets the port number for the client.
             * 
             * @param port The new port number.
             */
            void setPort(int port);

            /**
             * @brief Gets the IP address of the client.
             * 
             * @return The client's IP address.
             */
            std::string getAddr() const;

            /**
             * @brief Sets the IP address of the client.
             * 
             * @param address The new IP address.
             */
            void setAddr(std::string address);

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
                Utils::ParametersMap::init_map();
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
                _history[_AckToSend] = std::make_tuple(function_type, function_index, vector_params);
                setAckToSend();
            }

        private:
            int _id;
            int _x;
            int _y;
            int _AckExpected;
            int _AckToSend;
            int _gameRoom;
            bool _inGame;
            bool _isAlive;
            int _port;
            std::string _addr;
            std::map<int, std::tuple<int, int,  std::vector<std::string>>> _history;
    };
}
