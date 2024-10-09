/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Game_info
*/

#include "Game_info.hh"

Rtype::Game_info::Game_info():
	_id(-1), _level(0), _nbMaxPlayer(6), _players()
{
}

Rtype::Game_info::Game_info(int id):
	_id(id), _level(0), _nbMaxPlayer(6), _players()
{
}

Rtype::Game_info::~Game_info()
{
}

bool Rtype::Game_info::isGameAvailable(void)
{
	return !(_players.max_size() == _nbMaxPlayer);
}

int Rtype::Game_info::gameStatus(void)
{
}

int Rtype::Game_info::getLevel(void)
{
	return _level;
}

void Rtype::Game_info::connectPlayer(Rtype::client_info &player)
{
	if (!isGameAvailable())
		return;
	_players.push_back(player);
	player.setRoom(_id);
	player.setX(0);
	player.setY(0);
}

void Rtype::Game_info::disconnectPlayer(int id)
{
	for (auto i_player = _players.begin(); i_player != _players.end(); i_player++) {
		Rtype::client_info player = *i_player.base();
		if (id == player.getId()) {
			player.setRoom(-1);
			player.setX(0);
			player.setY(0);
			_players.erase(i_player);
			return;
		}
	}
}
