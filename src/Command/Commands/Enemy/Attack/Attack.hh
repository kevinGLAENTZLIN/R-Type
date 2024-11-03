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
        namespace Enemy
        {
            class Attack: public ACommand{
                public:
                    /**
                    * @brief Constructs an Attack command object with default values.
                    */
                    Attack() = default;

                    /**
                    * @brief Destroys the Attack command/
                    */
                    ~Attack();

                    /**
                    * @brief Configures the Attack command for server-side execution.
                    *
                    * This method sets up server-specific details required for processing an enemy's attack,
                    * such as the players affected and the attacking enemy’s identifier.
                    *
                    * @param players A map containing player IDs and their respective `client_info` objects,
                    *        representing the players potentially affected by the enemy's attack.
                    * @param mobID An integer identifier for the specific enemy instance that is attacking.
                    */
                    void set_server(std::map<int, std::shared_ptr<Rtype::client_info>> players, int mobID);

                    /**
                    * @brief Configures the Attack command for client-side execution.
                    *
                    * This method sets up client-specific actions related to the enemy attack.
                    */
                    void set_client();

                    /**
                    * @brief Executes the Attack command on the client side.
                    *
                    * This method implements the client-side behavior when an enemy attacks,
                    */
                    void execute_client_side();

                    /**
                    * @brief Executes the Attack command on the server side.
                    *
                    * This method performs server-specific actions when an enemy attacks,
                    * including updating the game state and notifying relevant players.
                    */
                    void execute_server_side();

                protected:
                private:
                    std::map<int, std::shared_ptr<Rtype::client_info>> _players;
                    int _mobID;
            };
        }
    }
}
