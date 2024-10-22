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
#include "../Utils/ParametersMap/ParametersMap.hpp"
#include "../Command/Factory/Factory.hh"
#include "../Command/Invoker/Command_invoker.hh"
#include "./Game/Game.hh"

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
         * @brief Run the network thread and the game.
         */
        void run();  // This will now spawn two threads: one for game, one for network.

    private:
        void read_server();

        void received_data_handler(std::size_t bytes_recv);
        /**
         * @brief Handle the response from the server.
         * @param clientResponse The response from the server.
         */
        void handleResponse(Utils::Network::Response clientResponse);


        template <typename T>
        std::unique_ptr<T> convertACommandToCommand(std::unique_ptr<Rtype::Command::ACommand> base) {
            static_assert(std::is_base_of<Rtype::Command::ACommand, T>::value);

            T* derived = dynamic_cast<T*>(base.get());
            if (derived) {
                base.release();
                return std::unique_ptr<T>(derived);
            } else
                return nullptr;
        }

    
        void setHandleMaps();
        void setHandleGameInfoMap();
        void setHandlePlayerMap();
        void setHandlePowerUpMap();
        void setHandleProjectileMap();

        std::unordered_map<Utils::GameInfoEnum, std::function<void(Utils::Network::Response)>> _handleGameInfoMap;
        std::unordered_map<Utils::PlayerEnum, std::function<void(Utils::Network::Response)>> _handlePlayerMap;
        std::unordered_map<Utils::PowerUpEnum, std::function<void(Utils::Network::Response)>> _handlePowerUpMap;
        std::unordered_map<Utils::ProjectileEnum, std::function<void(Utils::Network::Response)>> _handleProjectileMap;

        /**
         * @brief Run the IO context.
         */
        void runNetwork();  // New method to handle the networking thread.

        int _id;
        int _ackToSend;
        int _ackToReceive;
        boost::asio::io_context _ioContext;
        std::shared_ptr<udp::socket> _socket;
        udp::endpoint _serverEndpoint;
        std::array<char, 1024> _receiverBuffer;
        std::thread _receiverThread;
        std::thread _networkThread;  // New thread for the network loop.
        Rtype::Command::Command_invoker _commandInvoker;
        Rtype::Command::Factory _commandFactory;
        Rtype::Game _game;
    };
}
