/*
** EPITECH PROJECT, 2024
** R-Type
** File description: Main of the Client
** main
*/

#include "udp_client.hh"

int main(int argc, char **argv)
{
    if (argc != 3) {
        std::cout << "Usage: udp_client [server] [port] <Message>" << std::endl;
        return 84;
    }
    Rtype::udpClient localClient(argv[1], std::atoi(argv[2]));
    localClient.run();
    return 0;
}
