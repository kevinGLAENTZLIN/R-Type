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
        namespace Boss
        {
            /**
            * @brief The Spawn class represents a command to spawn a boss.
            *
            * This command initializes the spawn details for a boss entity, specifying its position,
            * health, and type.
            */
            class Spawn: public ACommand{
                public:

                    /**
                    * @brief Constructs a Spawn command object with default values.
                    */
                    Spawn() = default;

                    /**
                    * @brief Destroys the Spawn command object.
                    */
                    ~Spawn();

                    /**
                    * @brief Configures the Spawn command for server-side execution.
                    *
                    * This method sets up server-specific details for spawning a boss entity, including
                    * player data, boss type, position coordinates, and initial health of the entity.
                    *
                    * @param players A shared pointer to a map of player IDs and their respective `client_info` objects.
                    * @param bossType An integer representing the type of the boss or entity to be spawned.
                    * @param bossMob An integer identifier for the specific mob or boss entity.
                    * @param x The x-coordinate where the boss entity will spawn.
                    * @param y The y-coordinate where the boss entity will spawn.
                    * @param health The health value assigned to the boss or entity at spawn.
                    */
                    void set_server(std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> players, int bossType, int bossMob, double x, double y, int health);

                    /**
                    * @brief Configures the Spawn command for client-side execution.
                    *
                    * This method sets up client-specific details for displaying the spawned entity,
                    * including visual effects or animations.
                    */
                    void set_client();

                    /**
                    * @brief Executes the Spawn command on the client side.
                    *
                    * This method implements client-side actions related to the spawning of the boss.
                    */
                    void execute_client_side();

                    /**
                    * @brief Executes the Spawn command on the server side.
                    *
                    * This method performs server-side logic for spawning the boss, updating
                    * relevant gameplay data for affected players and tracking the new entity.
                    */
                    void execute_server_side();

                protected:
                private:
                    std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> _players;
                    int _mobType;
                    int _mobID;
                    int _health;
                    double _x;
                    double _y;
            };
        }
    }
}
