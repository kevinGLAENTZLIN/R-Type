/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Spawn
*/

#pragma once
#include "../../../ACommand.hpp"
#include "../../../../Server/Client_info.hpp"

namespace Rtype
{
    namespace Command
    {
        namespace PowerUp
        {
            /**
             * @brief The Spawn class represents a command for spawning power-ups.
             *
             * This command handles the creation and management of power-ups, including their placement
             * in the game.
             */
            class Spawn: public ACommand{
                public:
                    /**
                    * @brief Constructs a Spawn command object with default values.
                    */
                    Spawn() = default;

                    /**
                    * @brief Destroys the Spawn command object, releasing any allocated resources.
                    */
                    ~Spawn();

                    /**
                    * @brief Configures the Spawn command for server-side execution.
                    *
                    * This method sets up server-specific details required for processing the spawning of a power-up,
                    * such as the players affected and the coordinates for placing the power-up in the game world.
                    *
                    * @param players A shared pointer to a map containing player IDs and their respective `client_info` objects,
                    *        representing the players that need to be updated about the power-up.
                    * @param podID An integer identifier for the power-up being spawned.
                    * @param x A double representing the x-coordinate where the power-up will be spawned.
                    * @param y A double representing the y-coordinate where the power-up will be spawned.
                    */
                    void set_server(std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> players, int podID, double x, double y);

                    /**
                    * @brief Configures the Spawn command for client-side execution.
                    *
                    * This method sets up client-specific actions related to the power-up spawning,
                    * including its position in the game.
                    *
                    * @param x A double representing the x-coordinate where the power-up will be displayed.
                    * @param y A double representing the y-coordinate where the power-up will be displayed.
                    */
                    void set_client(double x, double y);

                    /**
                    * @brief Executes the Spawn command on the client side.
                    *
                    * This method implements the client-side behavior when a power-up is spawned.
                    */
                    void execute_client_side();

                    /**
                    * @brief Executes the Spawn command on the server side.
                    *
                    * This method performs server-specific actions when a power-up is spawned.
                    */
                    void execute_server_side();

                protected:
                private:
                    std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> _players;
                    int _podID;
                    double _x;
                    double _y;
            };
        }
    }
}
