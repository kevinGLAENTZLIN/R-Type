/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Game_info
*/

#include "Game_info.hh"

Rtype::Game_info::Game_info():
	_id(-1), _level(0), _nbMaxPlayer(6), _tick(0), _players()
{
	_tickThread = std::thread([this]() { computeTick(); });
}

Rtype::Game_info::Game_info(int id):
	_id(id), _level(0), _nbMaxPlayer(6), _tick(0), _players()
{
}

Rtype::Game_info::~Game_info()
{
	if (_tickThread.joinable()) {
        _tickThread.join();
    }
}

Rtype::Game_info::Game_info(Game_info &&other) noexcept:
	_id(other._id), _level(other._level), _nbMaxPlayer(other._nbMaxPlayer), _tick(other._tick),
    _tickThread(std::move(other._tickThread)), _players(std::move(other._players))
{
    other._id = -1;
    other._level = 0;
    other._nbMaxPlayer = 6;
    other._tick = 0;
}

Rtype::Game_info &Rtype::Game_info::operator=(Game_info &&other) noexcept
{
    if (this != &other) {
        if (_tickThread.joinable()) {
            _tickThread.join();
        }

        _id = other._id;
        _level = other._level;
        _nbMaxPlayer = other._nbMaxPlayer;
        _tick = other._tick;
        _tickThread = std::move(other._tickThread);
        _players = std::move(other._players);

        other._id = -1;
        other._level = 0;
        other._nbMaxPlayer = 6;
        other._tick = 0;
    }
    return *this;
}

void Rtype::Game_info::computeGame(void)
{
	if (_tick % 200 == 0)
		std::cout << "Spawn a mob" << std::endl; //! To refactor by the commands
}

void Rtype::Game_info::computeTick(void)
{
	while (!_players.empty()) {
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		_tick += 1;
		computeGame();
	}
}

bool Rtype::Game_info::isGameAvailable(void)
{
	return !(_players.max_size() == _nbMaxPlayer);
}

bool Rtype::Game_info::gameStatus(void)
{
	return true;
}

void Rtype::Game_info::goNextLevel(void)
{
	_level += 1;
}

int Rtype::Game_info::getLevel(void)
{
	return _level;
}

int Rtype::Game_info::getRoomId(void)
{
	return _id;
}

void Rtype::Game_info::connectPlayer(std::shared_ptr<Rtype::client_info> player)
{
	if (!isGameAvailable())
		return;
	_players[player->getId()] = player;
	player->setRoom(_id);
	player->setX(42);
	player->setY(42);
}

const std::map<int, std::shared_ptr<Rtype::client_info>>& Rtype::Game_info::getPlayers(void) const {
    return _players;
}

void Rtype::Game_info::disconnectPlayer(int id)
{
	for (auto i_player = _players.begin(); i_player != _players.end(); i_player++) {
		std::shared_ptr<Rtype::client_info> player = i_player->second;
		if (id == player->getId()) {
			player->setRoom(-1);
			player->setX(0);
			player->setY(0);
			_players.erase(i_player);
			return;
		}
	}
}
