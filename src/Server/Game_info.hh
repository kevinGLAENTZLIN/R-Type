    /*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Game_info
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
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <memory>
#include <thread>
#include <stack>
#include "Client_info.hpp"
#include "Parser/LoadData/LoadData.hh"

#define MAX_UINT32  (4294967295U)

namespace Rtype
{
    class Game;

    class Network;

    class Game_info {
        public:
            /**
            * @brief GameInfo constructor.
            * @param void
            * @return void
            */
            Game_info();

            /**
            * @brief GameInfo constructor.
            * @param id
            * @param difficulty
            * @param nbMaxPlayer
            * @return void
            */
            Game_info(int id, int difficulty, int nbMaxPlayer);

            /**
            * @brief GameInfo destructor.
            * @param void
            * @return void
            */
            ~Game_info();

            Game_info(const Game_info&) = delete;
            Game_info& operator=(const Game_info&) = delete;

            /**
            * @brief GameInfo move constructor.
            * @param other
            * @return void
            */
            Game_info(Game_info&& other) noexcept;

            /**
            * @brief GameInfo move assignement operator.
            * @param other
            * @return GameInfo&
            */
            Game_info& operator=(Game_info&& other) noexcept;

            /**
            * @brief computeGame function.
            * @param currentGameTimeInSeconds
            * @return void
            */
            void computeGame(int currentGameTimeInSeconds);

            /**
            * @brief computePlayer function.
            * @param void
            * @return void
            */
            void computePlayer(void);

            /**
            * @brief computeTick function.
            * @param void
            * @return void
            */
            void computeTick(void);

            /**
            * @brief setNetwork function.
            * @param std::shared_ptr<Rtype::Network> network
            * @return void
            */
            void setNetwork(std::shared_ptr<Rtype::Network> network);

            /**
            * @brief getNetwork function.
            * @param void
            * @return std::shared_ptr<Rtype::Network>
            */
            std::shared_ptr<Rtype::Game> getGame();

            /**
            * @brief getNetwork function.
            * @param void
            * @return void
            */
            void runGame();

            /**
            * @brief gameStatus function.
            * @param void
            * @return void
            */
            bool gameStatus(void);

            /**
            * @brief goNextLevel function.
            * @param void
            * @return void
            */
            void goNextLevel(void);

            /**
            * @brief getLevel function.
            * @param void
            * @return int
            */
            int getLevel(void);

            /**
            * @brief getRoomId function.
            * @param void
            * @return int
            */
            int getRoomId(void);

            /**
            * @brief isGameAvailable function.
            * @param void
            * @return bool
            */
            bool isGameAvailable(void);

            /**
            * @brief getToSetNetwork function.
            * @param void
            * @return bool
            */
            bool getToSetNetwork();

            /**
            * @brief getPlayers function.
            * @param void
            * @return std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>>
            */
            std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> getPlayers(void);

            /**
            * @brief getNbMaxPlayers function.
            * @param void
            * @return int
            */
            int getNbMaxPlayers();

            /**
            * @brief connectPlayer function.
            * @param std::shared_ptr<Rtype::client_info> player
            * @return void
            */
            void connectPlayer(std::shared_ptr<Rtype::client_info> player);

            /**
            * @brief disconnectPlayer function.
            * @param int id
            * @return void
            */
            void disconnectPlayer(int id);

            /**
            * @brief getNbProjectiles function.
            * @param void
            * @return int
            */
            int getNbProjectiles();

            /**
            * @brief accNbProjectiles function.
            * @param void
            * @return void
            */
            void accNbProjectiles();

        protected:
        private:
            int _id;
            int _level;
            int _difficulty;
            int _nbMaxPlayer;
            int _nbProjectiles; //! tmp
            unsigned int _tick;
            unsigned int _timeLastLevelEnded;
            std::thread _tickThread;
            std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> _players;
            std::shared_ptr<Rtype::Network> _network;
            LoadData _loadData;
            std::stack<Rtype::EnemySpawnData> _enemySpawnData;
            std::size_t _nextEnemyIndex;
            std::shared_ptr<Rtype::Game> _game;
            bool _toSetNetwork;
            std::thread _gameThread;
            std::mutex _playersMutex;
            // Todo compile with Game class
    };
}
