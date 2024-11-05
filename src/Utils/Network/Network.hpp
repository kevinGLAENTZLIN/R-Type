/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Network
*/

#pragma once

#include "../ParametersMap/ParametersMap.hpp"
#include "../../Command/Factory/Factory.hh"
#include "../../Command/Invoker/Command_invoker.hh"

#include <boost/asio.hpp>
#include <iostream>

namespace Rtype
{

    class Network {
        public:
            /**
            * @brief Construct a new Network
            *
            * @tparam void
            * @return float.
            */
            Network();

            /**
            * @brief Construct a new Network
            *
            * @tparam io_service boost::asio::io_service
            * @tparam port short
            * @tparam type std::string
            * @return void.
            */
            Network(boost::asio::io_service &io_service, short port, std::string type);

            /**
            * @brief Construct a new Network
            *
            * @tparam io_context boost::asio::io_context
            * @tparam serverAddr std::string
            * @tparam serverPort int
            * @tparam type std::string
            * @return void.
            */
            Network(boost::asio::io_context &io_context, const std::string &serverAddr, const int serverPort, std::string type);

            /**
            * @brief Destroy the Network
            *
            * @tparam void
            * @return void.
            */
            ~Network();

            /**
            * @brief Send a message
            *
            * @tparam void
            * @return void.
            */
            void accAckToSend();

            /**
            * @brief Receive a message
            *
            * @tparam void
            * @return void.
            */
            void accAckToReceive();

            /**
            * @brief get the ack to send
            *
            * @tparam void
            * @return int.
            */
            int getAckToSend();

            /**
            * @brief get the ack to receive
            *
            * @tparam void
            * @return int.
            */
            int getAckToReceive();

            /**
            * @brief add a command to the invoker
            *
            * @tparam std::unique_ptr<Rtype::Command::ACommand> cmd
            * @return void.
            */
            void addCommandToInvoker(std::unique_ptr<Rtype::Command::ACommand> cmd);

            /**
            * @brief execute the invoker
            *
            * @tparam void
            * @return void.
            */
            void executeInvoker();


            /**
            * @brief create a command
            *
            * @tparam uint8_t category
            * @tparam uint8_t index
            * @return std::unique_ptr<Rtype::Command::ACommand>.
            */
            std::unique_ptr<Rtype::Command::ACommand> createCommand(uint8_t category, uint8_t index);

            /**
            * @brief get the socket
            *
            * @tparam void
            * @return std::shared_ptr<udp::socket>.
            */
            std::shared_ptr<udp::socket> getSocket();

            /**
            * @brief set the endpoint
            *
            * @tparam udp::endpoint endpoint
            * @return void.
            */
            void setSenderEndpoint(udp::endpoint endpoint);

            /**
            * @brief get the endpoint
            *
            * @tparam void
            * @return udp::endpoint.
            */
            udp::endpoint getSenderEndpoint();

            /**
            * @brief convert ACommand to Command
            *
            * @tparam T
            * @tparam std::unique_ptr<Rtype::Command::ACommand> base
            * @return std::unique_ptr<T>.
            */
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
        protected:
        private:
            int _ackToSend;
            int _ackToReceive;
            std::shared_ptr<udp::socket> _socket;
            udp::endpoint _endpoint;
            Rtype::Command::Command_invoker _commandInvoker;
            Rtype::Command::Factory _commandFactory;
    };
} // namespace Rtype
