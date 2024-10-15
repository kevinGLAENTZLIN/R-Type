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
    // try {
    //     boost::asio::io_service io_service;
    //     Rtype::udpClient client(io_service, argv[1], std::stoi(argv[2]));
    //     io_service.run();
    // } catch (std::exception &error) {
    //     std::cerr << "Exception: " << error.what() << "\n";
    // }
    // if (argv[3] != NULL)
    //     for (int i = 0; i < 5; i++)
    //         client.send_data(argv[3]);
    // std::this_thread::sleep_for(std::chrono::seconds(3));
    return 0;
}
