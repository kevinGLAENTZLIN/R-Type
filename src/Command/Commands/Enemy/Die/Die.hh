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
        namespace Enemy
        {
            /**
            * @brief The Die class represents a command to handle the death of an enemy entity.
            *
            * This command manages the actions and updates required when an enemy dies, including
            * notifications to players and any associated changes to the game state.
            */
            class Die: public ACommand{
                public:

                    /**
                    * @brief Constructs a Die command.
                    */
                    Die() = default;

                    /**
                    * @brief Destroys the Die command object.
                    */
                    ~Die();

                    /**
                    * @brief Configures the Die command for server-side execution.
                    *
                    * This method sets up server-specific details required when an enemy dies.
                    *
                    * @param players A shared pointer to a map of player IDs and their respective `client_info` objects.
                    * @param mobID An integer identifier representing the specific enemy instance that has died.
                    */
                    void set_server(std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> players, int mobID);

                    /**
                    * @brief Configures the Die command for client-side execution.
                    *
                    * This method sets up client-specific actions related to the enemy's death,
                    * including visual effects and feedback for the player.
                    */
                    void set_client();

                    /**
                    * @brief Executes the Die command on the client side.
                    *
                    * This method implements the client-side behavior when an enemy dies,
                    */
                    void execute_client_side();

                    /**
                    * @brief Executes the Die command on the server side.
                    *
                    * This method performs server-specific actions required when an enemy dies,
                    * including updating game state and notifying relevant players.
                    */
                    void execute_server_side();

                protected:
                private:
                    std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> _players;
                    int _mobID;
            };
        }
    }
}
