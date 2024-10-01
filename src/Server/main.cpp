/*
** EPITECH PROJECT, 2024
** R-Type
** File description: Main of the Server
** main
*/

#include "udp_server.hh"

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cerr << "Usage: udp_server <port>\n";
        return 1;
    }
    try {
        boost::asio::io_service io_service;
        udpServer server(io_service, std::atoi(argv[1]));
        io_service.run();
    }
    catch (std::exception &error) {
        std::cerr << "Exception: " << error.what() << "\n";
    }
    return 0;
}
