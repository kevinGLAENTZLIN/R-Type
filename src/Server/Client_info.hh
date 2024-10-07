/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** client_info
*/

#pragma once

#include <iostream>
#include <string>
#include <cstdarg>
#include <map>
#include <vector>
#include "../Utils/ParametersMap/ParametersMap.hpp"

namespace Rtype {
    class client_info {
        public:
            client_info();
            client_info(int id, int port, std::string addr);
            ~client_info();

            int getId() const;
            void setId(int id);

            int getX() const;
            void setX(int x);

            int getY() const;
            void setY(int y);

            int getAckToExpect() const;
            void setAckToExpect();

            int getAckToSend() const;
            void setAckToSend();

            int getRoom() const;
            void setRoom(int room);

            int getPort() const;
            void setPort(int port);

            std::string getAddr() const;
            void setAddr(std::string address);

            void pushCmdToHistory(int function_type, int function_index, std::va_list params);

        private:
            int _id;
            int _x;
            int _y;
            int _AckExpected;
            int _AckToSend;
            int _gameRoom;
            bool _inGame;
            bool _isAlive;
            int _port;
            std::string _addr;
            std::map<int, std::tuple<int, int,  std::vector<std::string>>> _history;
    };
}
