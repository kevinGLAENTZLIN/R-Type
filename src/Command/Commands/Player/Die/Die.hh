/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Die
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
            * @brief The Die class represents a command for handling the death of a player in the game.
            *
            * This command is responsible for updating the game state when a player dies.
            */
            class Die: public ACommand{
                public:
                    /**
                    * @brief Constructs a Die command.
                    */
                    Die() = default;

                    /**
                    * @brief Destroys the Die command.
                    */
                    ~Die();

                    /**
                    * @brief Configures the Die command for client-side execution.
                    *
                    * This method sets the necessary parameters for handling the player's death.
                    */
                    void set_client();

                    /**
                    * @brief Configures the Die command for server-side execution.
                    *
                    * This method sets the necessary parameters for handling the player's death
                    * on the server.
                    *
                    * @param players A shared pointer to a map of active players, indexed by their IDs.
                    * @param playerID An integer representing the ID of the player that has died.
                    */
                    void set_server(std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> players, int playerID);

                    /**
                    * @brief Executes the Die command on the client side.
                    *
                    * This method implements the behavior for handling the player's death locally
                    * when the command is received.
                    */
                    void execute_client_side();

                    /**
                    * @brief Executes the Die command on the server side.
                    *
                    * This method performs server-specific actions when a player dies.
                    */
                    void execute_server_side();

                protected:
                private:
                    std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> _players;
                    int _playerID;
            };
        }
    }
}
