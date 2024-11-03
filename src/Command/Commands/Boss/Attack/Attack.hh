/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Attack
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
            * @brief The Attack class represents an attack command initiated by a boss character.
            *
            * This command handles boss-specific attack behaviors, with functionality for both
            * server-side and client-side execution.
            */
            class Attack: public ACommand{
                public:
                    /**
                    * @brief Constructs an Attack command object with default values.
                    */
                    Attack() = default;

                    /**
                    * @brief Destroys the Attack command object, releasing any allocated resources.
                    */
                    ~Attack();

                    /**
                    * @brief Configures the Attack command for server-side execution.
                    *
                    * This method sets up server-side details for the command, including
                    * the map of players affected by the attack, the type of boss performing
                    * the attack, and the type of attack executed.
                    *
                    * @param players A map of player IDs to their corresponding `client_info` objects.
                    * @param bossType An integer representing the type of the boss.
                    * @param bossAttackType An integer specifying the type of attack used by the boss.
                    */
                    void set_server(std::map<int, std::shared_ptr<Rtype::client_info>> players, int bossType, int bossAttackType);

                    /**
                    * @brief Configures the Attack command for client-side execution.
                    *
                    * This method sets up client-specific details for the command execution.
                    */
                    void set_client();

                    /**
                    * @brief Executes the Attack command on the client side.
                    *
                    * This method implements client-specific actions.
                    */
                    void execute_client_side();

                    /**
                    * @brief Executes the Attack command on the server side.
                    *
                    * This method performs the server-side actions needed for a boss attack,
                    * including updating affected players and tracking the state of the boss.
                    */
                    void execute_server_side();

                protected:
                private:
                    std::map<int, std::shared_ptr<Rtype::client_info>> _players;
                    int _bossType;
                    int _bossAttackType;
            };
        }
    }
}
