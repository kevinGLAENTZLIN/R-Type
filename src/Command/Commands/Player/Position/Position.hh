/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Position.hpp
*/

#pragma once
#include "../../../ACommand.hpp"

namespace Rtype
{
    namespace Command
    {
        namespace Player
        {
            /**
            * @brief The Position class represents a command for updating a player's position in the game.
            *
            * This command is responsible for synchronizing the player's position between the server
            * and clients.
            */
            class Position: public ACommand
            {
            private:
                double _x;
                double _y;
                int _player_id;
            public:

                /**
                * @brief Constructs a Position.
                */
                Position() = default;

                /**
                * @brief Destroys the Position command.
                */
                ~Position();

                /**
                * @brief Configures the Position command for client-side execution.
                *
                * This method prepares the necessary data for the client to update its local representation
                * of the player's position.
                */
                void set_client();

                /**
                * @brief Configures the Position command for server-side execution.
                *
                * This method sets the new position for the player on the server.
                *
                * @param x A double representing the new X coordinate of the player's position.
                * @param y A double representing the new Y coordinate of the player's position.
                */
                void set_server(int player_id, double x, double y);

                /**
                * @brief Executes the Position command on the client side.
                *
                * This method implements the behavior for updating the player's position locally when
                * the command is received.
                */
                void execute_client_side();

                /**
                * @brief Executes the Position command on the server side.
                *
                * This method performs server-specific actions when updating a player's position.
                */
                void execute_server_side();
            };
        }
    }
}
