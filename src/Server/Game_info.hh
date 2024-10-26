    /*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Game_info
*/

#pragma once
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <memory>
#include <thread>
#include "Client_info.hpp"

namespace Rtype
{
    class Game;

    class Network;

    class Game_info {
        public:
            Game_info();
            Game_info(int id);
            ~Game_info();

            Game_info(const Game_info&) = delete;
            Game_info& operator=(const Game_info&) = delete;

            Game_info(Game_info&& other) noexcept;
            Game_info& operator=(Game_info&& other) noexcept;

            void computeGame(void);
            void computeTick(void);

            void setNetwork(std::shared_ptr<Rtype::Network> network);
            std::shared_ptr<Rtype::Game> getGame();

            void runGame();

            bool gameStatus(void);
            void goNextLevel(void);
            int getLevel(void);
            int getRoomId(void);
            bool isGameAvailable(void);
            bool getToSetNetwork();
            const std::map<int, std::shared_ptr<Rtype::client_info>> &getPlayers(void) const;

            void connectPlayer(std::shared_ptr<Rtype::client_info> player);
            void disconnectPlayer(int id);

        protected:
        private:
            int _id;
            int _level;
            int _nbMaxPlayer;
            unsigned int _tick;
            std::thread _tickThread;
            std::map<int, std::shared_ptr<Rtype::client_info>> _players;
            std::shared_ptr<Rtype::Network> _network;
            std::shared_ptr<Rtype::Game> _game;
            bool _toSetNetwork;
            std::thread _gameThread;
            // Todo compile with Game class
    };
}
