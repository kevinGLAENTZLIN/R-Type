/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Level_complete
*/

#include "Level_complete.hh"

void Rtype::Command::GameInfo::Level_complete::set_client()
{
}

void Rtype::Command::GameInfo::Level_complete::set_server(std::shared_ptr<Rtype::Game_info> game)
{
    _gameInfo = game;
}

Rtype::Command::GameInfo::Level_complete::~Level_complete()
{
}

void Rtype::Command::GameInfo::Level_complete::execute_client_side()
{
    std::cerr << "This command have no client side" << std::endl;
}

void Rtype::Command::GameInfo::Level_complete::execute_server_side()
{
    _gameInfo->goNextLevel();
    CONSOLE_INFO(_gameInfo->getRoomId(), " went to the next Level !")
    sendToEndpoint(*_clientInfo, Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::LevelComplete, _gameInfo.get());
}
