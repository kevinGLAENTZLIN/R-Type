/*
** EPITECH PROJECT, 2024
** R-Type
** File description: Main of the Server
** main
*/

#include "udp_server.hpp"

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cerr << "Usage: udp_server <port>\n";
        return 1;
    }
    try {
        Rtype::udpServer server(std::atoi(argv[1]));
        server.run();
    }
    catch (std::exception &error) {
        std::cerr << "Exception: " << error.what() << "\n";
    }
    return 0;
}
