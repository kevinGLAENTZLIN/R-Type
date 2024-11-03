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
        namespace Boss
        {
            /**
            * @brief The Die class represents a command for handling the death of a boss.
            *
            * This command manages both client-side and server-side behavior for the death of a boss.
            */
            class Die: public ACommand{
                public:

                    /**
                    * @brief Constructs a Die command object with default values.
                    */
                    Die() = default;

                    /**
                    * @brief Destroys the Die command.
                    */
                    ~Die();

                    /**
                    * @brief Configures the Die command for server-side execution.
                    *
                    * This method sets up server-specific details for the boss's death event,
                    * including the list of players impacted and the type of boss that died.
                    *
                    * @param players A map of player IDs to their respective `client_info` objects.
                    * @param bossType An integer representing the type of the boss that died.
                    */
                    void set_server(std::map<int, std::shared_ptr<Rtype::client_info>> players, int bossType);

                    /**
                    * @brief Configures the Die command for client-side execution.
                    *
                    * This method sets up client-specific details for handling the boss's death,
                    * such as visual effects and gameplay adjustments.
                    */
                    void set_client();

                    /**
                    * @brief Executes the Die command on the client side.
                    *
                    * This method implements client-specific actions in response to the boss's death,
                    * typically involving visual feedback or score updates for the player.
                    */
                    void execute_client_side();

                    /**
                    * @brief Executes the Die command on the server side.
                    *
                    * This method performs server-specific actions necessary for handling the boss's death,
                    * including updating the state of affected players and managing game progress.
                    */
                    void execute_server_side();

                protected:
                private:
                    std::map<int, std::shared_ptr<Rtype::client_info>> _players;
                    int _bossType;
            };
        }
    }
}
