    /*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Game_info
*/

#pragma once
#if defined(_WIN32)           
	#define NOGDI             // All GDI defines and routines
	#define NOUSER            // All USER defines and routines
#endif

#include "raylib-cpp.hpp"

#if defined(_WIN32)           // raylib uses these names as function parameters
	#undef near
	#undef far
#endif
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <memory>
#include <thread>
#include <vector>
#include "Client_info.hpp"
#include "Parser/LoadData/LoadData.hh"

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

            void computeGame(int currentGameTimeInSeconds);
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
            std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> getPlayers(void);
            int getNbMaxPlayers();

            void connectPlayer(std::shared_ptr<Rtype::client_info> player);
            void disconnectPlayer(int id);

            int getNbProjectiles();
            void accNbProjectiles();

        protected:
        private:
            int _id;
            int _level;
            int _nbMaxPlayer;
            int _nbProjectiles; //! tmp
            unsigned int _tick;
            std::thread _tickThread;
            std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> _players;
            std::shared_ptr<Rtype::Network> _network;
            LoadData _loadData;
            std::vector<Rtype::EnemySpawnData> _enemySpawnData;
            std::size_t _nextEnemyIndex;
            std::shared_ptr<Rtype::Game> _game;
            bool _toSetNetwork;
            std::thread _gameThread;
            // Todo compile with Game class
    };
}
