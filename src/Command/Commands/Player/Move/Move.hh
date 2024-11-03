/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Move
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
#include "../../../ACommand.hpp"
#include "../../../../Server/Client_info.hpp"

namespace Rtype
{
    namespace Command
    {
        namespace Player
        {
            /**
            * @brief The Move class represents a command for moving a player in the game.
            *
            * This command is responsible for updating the position of a player both on the server
            * and for the client.
            */
            class Move: public ACommand{
                public:

                    /**
                    * @brief Constructs a Move command.
                    */
                    Move() = default;

                    /**
                    * @brief Destroys the Move command.
                    */
                    ~Move();

                    /**
                    * @brief Configures the Move command for server-side execution.
                    *
                    * This method sets the new position of the player on the server and updates
                    * the relevant game state for other players.
                    *
                    * @param players A shared pointer to a map of active players, indexed by their IDs.
                    * @param playerID An integer representing the ID of the player being moved.
                    * @param x A double representing the new X coordinate of the player's position.
                    * @param y A double representing the new Y coordinate of the player's position.
                    */
                    void set_server(std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> players, int playerID, double x, double y);

                    /**
                    * @brief Configures the Move command for client-side execution.
                    *
                    * This method sets the new position for the player on the client.
                    *
                    * @param x A double representing the new X coordinate of the player's position.
                    * @param y A double representing the new Y coordinate of the player's position.
                    */
                    void set_client(double x, double y);

                    /**
                    * @brief Executes the Move command on the client side.
                    *
                    * This method implements the behavior for moving the player locally when
                    * the command is received.
                    */
                    void execute_client_side();

                    /**
                    * @brief Executes the Move command on the server side.
                    *
                    * This method performs server-specific actions when moving a player,
                    * including updating the game state and notifying other players of the movement.
                    */
                    void execute_server_side();

                protected:
                private:
                    udp::endpoint _endpoint;
                    std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> _players;
                    int _playerID;
                    double _x;
                    double _y;
            };
        }
    }
}
