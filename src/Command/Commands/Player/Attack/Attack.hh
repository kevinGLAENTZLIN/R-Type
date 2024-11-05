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
        namespace Player
        {
            /**
            * @brief The Attack class represents a command for handling a player's attack in the game.
            *
            * This command is responsible for processing the actions related to a player's attack.
            */
            class Attack: public ACommand{
                public:
                    /**
                    * @brief Constructs an Attack command.
                   */
                    Attack() = default;

                    /**
                    * @brief Destroys the Attack command object.
                    */
                    ~Attack();

                    /**
                    * @brief Configures the Attack command for server-side execution.
                    *
                    * This method sets the necessary parameters for processing the attack on the
                    * server.
                    *
                    * @param players A shared pointer to a map of active players, indexed by their IDs.
                    * @param projectileID An integer representing the ID of the projectile involved in the attack.
                    */
                    void set_server(std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> players, int projectileID);

                    /**
                    * @brief Configures the Attack command for client-side execution.
                    *
                    * This method sets the necessary parameters for handling the attack on the client side,
                    * including setting up the endpoint for communication and the projectile ID.
                    *
                    * @param endpoint The UDP endpoint for the client to communicate with the server
                    * @param projectileID An integer representing the ID of the projectile involved in the attack.
                    */
                    void set_client(udp::endpoint endpoint, int projectileID);

                    /**
                    * @brief Executes the Attack command on the client side.
                    *
                    * This method implements the behavior for handling the attack locally
                    * when the command is received.
                    */
                    void execute_client_side();

                    /**
                    * @brief Executes the Attack command on the server side.
                    *
                    * This method performs server-specific actions when a player attacks.
                    */
                    void execute_server_side();

                protected:
                private:
                    udp::endpoint _endpoint;
                    std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> _players;
                    int _projectileID;
            };
        }
    }
}
