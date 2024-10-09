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
#include "Client_info.hh"

namespace Rtype
{
    class Game_info {
        public:
            Game_info();
            Game_info(int id);
            ~Game_info();

            bool isGameAvailable(void);

            int gameStatus(void);

            int getLevel(void);

            void connectPlayer(Rtype::client_info &player);
            void disconnectPlayer(int id);

        protected:
        private:
            int _id;
            int _level;
            int _nbMaxPlayer;
            std::vector<Rtype::client_info> _players;

    };
}
