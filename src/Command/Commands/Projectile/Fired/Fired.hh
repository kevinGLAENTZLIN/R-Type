/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Fired
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
        namespace Projectile
        {
            /**
            * @brief The Fired class represents a command to manage the firing of projectiles in the game.
            *
            * This command handles the behavior associated with a projectile being fired, including
            * notifying relevant players and updating game state accordingly.
            */
            class Fired: public ACommand{
                public:
                    /**
                    * @brief Constructs a Fired command object with default values.
                    */
                    Fired() = default;

                    /**
                    * @brief Destroys the Fired command.
                    */
                    ~Fired();

                    /**
                    * @brief Configures the Fired command for server-side execution.
                    *
                    * This method sets up server-specific details required for processing a projectile's firing,
                    * such as the players affected and the identifiers for the entity and projectile.
                    *
                    * @param players A shared pointer to a map containing player IDs and their respective `client_info` objects,
                    *        representing the players that need to be updated about the projectile.
                    * @param entityID An integer identifier for the entity that is firing the projectile.
                    * @param projectileID An integer identifier for the specific projectile being fired.
                    */
                    void set_server(std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> players, int entityID, int projectileID);

                    /**
                    * @brief Configures the Fired command for client-side execution.
                    *
                    * This method sets up client-specific actions related to the projectile firing.
                    */
                    void set_client();

                    /**
                    * @brief Executes the Fired command on the client side.
                    *
                    * This method implements the client-side behavior when a projectile is fired,
                    * including displaying visual effects or sound associated with the projectile.
                    */
                    void execute_client_side();

                    /**
                    * @brief Executes the Fired command on the server side.
                    *
                    * This method performs server-specific actions when a projectile is fired,
                    * including updating the game state and notifying relevant players about the projectile's status.
                    */
                    void execute_server_side();

                protected:
                private:
                    std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> _players;
                    int _entityID;
                    int _projectileID;
            };
        }
    }
}
