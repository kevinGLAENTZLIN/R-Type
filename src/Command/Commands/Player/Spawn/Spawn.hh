/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Spawn
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
            * @brief The Spawn class represents a command for spawning players in the game.
            *
            * This command handles the initialization of player entities within the game,
            * including their position in the game world and updating the game state for
            * both server and client.
            */
            class Spawn: public ACommand{
                public:

                    /**
                    * @brief Constructs a Spawn command.
                    */
                    Spawn() = default;

                    /**
                    * @brief Destroys the Spawn command.
                    */
                    ~Spawn();


                    /**
                    * @brief Configures the Spawn command for server-side execution.
                    *
                    * This method sets up the necessary information for spawning a player on the server,
                    * including player ID, room ID, and the coordinates where the player will be placed
                    * in the game.
                    *
                    * @param players A shared pointer to a map containing player IDs and their respective `client_info` objects,
                    *        representing the players that need to be updated about the new player spawn.
                    * @param playerID An integer identifier for the player being spawned.
                    * @param roomId An integer representing the room in which the player is being spawned.
                    * @param x A double representing the x-coordinate where the player will be spawned.
                    * @param y A double representing the y-coordinate where the player will be spawned.
                    */
                    void set_server(std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> players, int playerID, int roomId, double x, double y);

                    /**
                    * @brief Configures the Spawn command for client-side execution.
                    *
                    * This method sets up client-specific actions related to the player spawn.
                    */
                    void set_client();

                    /**
                    * @brief Executes the Spawn command on the client side.
                    *
                    * This method implements the client-side behavior when a player is spawned,
                    * including displaying visual effects and updating the player's status in the game.
                    */
                    void execute_client_side();

                    /**
                    * @brief Executes the Spawn command on the server side.
                    *
                    * This method performs server-specific actions when a player is spawned.
                    */
                    void execute_server_side();

                protected:
                private:
                    std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> _players;
                    int _playerID;
                    int _roomId;
                    double _x;
                    double _y;
            };
        }
    }
}
