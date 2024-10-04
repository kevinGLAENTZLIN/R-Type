/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** client_info
*/

#pragma once

#include <iostream>
#include <string>

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

            int getACK() const;
            void setACK();

            int getRoom() const;
            void setRoom(int room);

            int getPort() const;
            void setPort(int port);

            std::string getAddr() const;
            void setAddr(std::string address);

        private:
            int _id;
            int _x;
            int _y;
            int _AckExpected;
            int _gameRoom;
            bool _inGame;
            int _port;
            std::string _addr;
    };
}
