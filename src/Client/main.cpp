/*
** EPITECH PROJECT, 2024
** R-Type
** File description: Main of the Client
** main
*/

#include "Game/Game.hh"

int main(int argc, char **argv)
{
    if (argc != 3) {
        std::cout << "Usage: udp_client [server] [port] <Message>" << std::endl;
        return 84;
    }
    Rtype::Game game;
    game.run(argv[1], std::stoi(argv[2]));
    return 0;
}
