/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Destroy
*/

#pragma once
#include "../../../ACommand.hpp"
#include "../../../../Server/Client_info.hpp"

namespace Rtype
{
    namespace Command
    {
        namespace Enemy
        {
            /**
            * @brief The Destroy class represents a command to handle the destruction of an enemy entity.
            *
            * This command manages actions and state updates associated with an enemy being destroyed,
            * including notifications to relevant players and updates to the game state.
            */
            class Destroy: public ACommand{
                public:
                    /**
                    * @brief Constructs a Destroy command..
                    */
                    Destroy() = default;

                    /**
                    * @brief Destroys a Destroy command.
                    */
                    ~Destroy();

                    /**
                    * @brief Configures the Destroy command for server-side execution.
                    *
                    * This method sets up server-specific details for handling an enemy's destruction,
                    *
                    * @param players A shared pointer to a map of player IDs and their respective `client_info` objects.
                    * @param mobID An integer identifier representing the specific enemy instance to be destroyed.
                    * @param roomId An integer identifier representing the room in which the enemy is destroyed.
                    */
                    void set_server(std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> players, int mobID, int roomId);

                    /**
                    * @brief Executes the Destroy command on the client side.
                    *
                    * This method implements the client-side behavior when an enemy is destroyed,
                    * typically involving visual feedback or scoring updates for the player.
                    */
                    void set_client();

                    /**
                    * @brief Executes the Destroy command on the client side.
                    *
                    * This method implements the client-side behavior when an enemy is destroyed,
                    * typically involving visual feedback or scoring updates for the player.
                    */
                    void execute_client_side();

                    /**
                    * @brief Executes the Destroy command on the server side.
                    *
                    * This method performs server-specific actions required when an enemy is destroyed,
                    * including updating the game state and notifying relevant players.
                    */
                    void execute_server_side();

                protected:
                private:
                    std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> _players;
                    int _mobID;
                    int _roomID;
            };
        }
    }
}
