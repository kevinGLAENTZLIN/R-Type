/*
** EPITECH PROJECT, 2024
** R-Type
** File description: Main of the Client
** main
*/

#include "udp_client.hh"
#include "Game/Game.hh"

int main(void)
{
    Rtype::Game game;

    game.run();
    return 0;
}

// int main(int argc, char **argv)
// {
//     if (argc < 3) {
//         std::cout << "Usage: udp_client [server] [port] <Message>" << std::endl;
//         return 1;
//     }
//     Rtype::udpClient client(argv[1], std::stoi(argv[2]));

//     if (argv[3] != NULL)
//         for (int i = 0; i < 5; i++)
//             client.send_data(argv[3]);
//     std::this_thread::sleep_for(std::chrono::seconds(3));
//     return 0;
// }
