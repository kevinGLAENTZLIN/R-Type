/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Score
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
            * @brief The Score class represents a command for updating a player's score in the game.
            *
            * This command handles the synchronization of player scores between the server and clients.
            */
            class Score: public ACommand{
                public:

                    /**
                    * @brief Constructs a Score command object with default values.
                    */
                    Score() = default;

                    /**
                    * @brief Destroys the Score command object, releasing any allocated resources.
                    */
                    ~Score();

                    /**
                    * @brief Configures the Score command for server-side execution.
                    *
                    * This method sets up the necessary information for updating a player's score on the server.
                    *
                    * @param players A shared pointer to a map containing player IDs and their respective `client_info` objects,
                    *        representing the players that need to be updated about the score change.
                    * @param score An integer representing the new score to be assigned to the player.
                    */
                    void set_server(std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> players, int score);

                    /**
                    * @brief Configures the Score command for client-side execution.
                    *
                    * This method sets up client-specific actions related to the score update,
                    * including preparing the endpoint to send the score to the appropriate client.
                    *
                    * @param endpoint An `udp::endpoint` representing the target client to which the score update will be sent.
                    */
                    void set_client(udp::endpoint endpoint);

                    /**
                    * @brief Executes the Score command on the client side.
                    *
                    * This method implements the client-side behavior when a score update is received.
                    */
                    void execute_client_side();

                    /**
                    * @brief Executes the Score command on the server side.
                    *
                    * This method performs server-specific actions when updating a player's score,
                    */
                    void execute_server_side();

                protected:
                private:
                    udp::endpoint _endpoint;
                    std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> _players;
                    int _score;
            };
        }
    }
}
