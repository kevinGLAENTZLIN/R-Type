/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Game_info
*/

#include "../Utils/Network/Network.hpp"
#include "../Client/Game/Game.hh"
#include "Game_info.hh"
#include <iostream>
#include <memory>
#include <vector>

Rtype::Game_info::Game_info():
	_id(-1), _level(0), _nbMaxPlayer(6), _nbProjectiles(10), _tick(0), _players(), _toSetNetwork(true)
{
    _loadData.LoadDataFromFile("stage1.json");
    _enemySpawnData = _loadData.GetEnemySpawnData();
	_tickThread = std::thread([this]() { computeTick(); });
}

Rtype::Game_info::Game_info(int id):
	_id(id), _level(0), _nbMaxPlayer(6), _nbProjectiles(10), _tick(0), _players(), _toSetNetwork(true)
{}

Rtype::Game_info::~Game_info()
{
	if (_tickThread.joinable()) {
        _tickThread.join();
    }
	if (_gameThread.joinable()) {
        _gameThread.join();
    }
}

Rtype::Game_info::Game_info(Game_info &&other) noexcept:
	_id(other._id), _level(other._level), _nbMaxPlayer(other._nbMaxPlayer), _tick(other._tick),
    _tickThread(std::move(other._tickThread)), _players(std::move(other._players)), _toSetNetwork(other._toSetNetwork)
{
    other._id = -1;
    other._level = 0;
    other._nbMaxPlayer = 6;
    other._nbProjectiles = 10;
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
		_toSetNetwork = other._toSetNetwork;
        _nbProjectiles = other._nbProjectiles;

        other._id = -1;
        other._level = 0;
        other._nbMaxPlayer = 6;
        other._tick = 0;
    }
    return *this;
}

bool Rtype::Game_info::getToSetNetwork()
{
	return _toSetNetwork;
}

void Rtype::Game_info::setNetwork(std::shared_ptr<Rtype::Network> network)
{
	_toSetNetwork = false;
	_network = network;
    _game = std::make_shared<Rtype::Game>(_network, false);
}

std::shared_ptr<Rtype::Game> Rtype::Game_info::getGame()
{
	return _game;
}

void Rtype::Game_info::runGame()
{
	_gameThread = std::thread([this]() { _game->runServer(); });
}

void Rtype::Game_info::computeGame(int currentGameTimeInSeconds)
{
    if (_nextEnemyIndex < _enemySpawnData.size()) {
        const auto& enemyData = _enemySpawnData[_nextEnemyIndex];

        if (currentGameTimeInSeconds >= enemyData.getSpawnTimeInSeconds()) {
            _game->createEnemy(
                enemyData.getType(),
                enemyData.getPositionX(),
                enemyData.getPositionY(),
                enemyData.getHealth()
            );
            _nextEnemyIndex += 1;
        }
    }
}

void Rtype::Game_info::computePlayer(void)
{
    std::unique_ptr<Command::Player::Position> cmd;

    for (auto i_player = _players->begin(); i_player != _players->end(); i_player++) {
        std::shared_ptr<Rtype::client_info> player = i_player->second;
        cmd = CONVERT_ACMD_TO_CMD(Rtype::Command::Player::Position, Utils::InfoTypeEnum::Player, Utils::PlayerEnum::PlayerMove);
        cmd->setCommonPart(_network->getSocket(), _network->getSenderEndpoint(), player->getAckToSend());
        cmd->set_server(player->getX(), player->getY());
        _network->addCommandToInvoker(std::move(cmd));
    }
}

void Rtype::Game_info::computeTick(void)
{
    int currentGameTimeInSeconds = 0;

	while (!_players->empty()) {
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		_tick += 1;
		currentGameTimeInSeconds = _tick / 20;
		computeGame(currentGameTimeInSeconds);
        if (_tick % 20 == 0)
            computePlayer();
	}
}

bool Rtype::Game_info::isGameAvailable(void)
{
	return !(_players->max_size() == _nbMaxPlayer);
}

bool Rtype::Game_info::gameStatus(void)
{
	return true;
}

void Rtype::Game_info::goNextLevel(void)
{
    const std::string nextLevel = "stage" + std::to_string(_level + 1) + ".json";

    _loadData.clearEnemySpawnData();
    _enemySpawnData.clear();
    _level += 1;
    _loadData.LoadDataFromFile(nextLevel);
    _enemySpawnData = _loadData.GetEnemySpawnData();
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
	if (!_players)
		_players = std::make_shared<std::map<int, std::shared_ptr<Rtype::client_info>>>();
	_players->insert({player->getId(), player});
	player->setRoom(_id);
	player->setX(-10.);
	player->setY(0.);
}

std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> Rtype::Game_info::getPlayers(void) {
    return _players;
}

void Rtype::Game_info::disconnectPlayer(int id)
{
	for (auto i_player = _players->begin(); i_player != _players->end(); i_player++) {
		std::shared_ptr<Rtype::client_info> player = i_player->second;
		if (id == player->getId()) {
			player->setRoom(-1);
			player->setX(42.);
			player->setY(42.);
			_players->erase(i_player);
			return;
		}
	}
}

int Rtype::Game_info::getNbMaxPlayers()
{
    return _nbMaxPlayer;
}

int Rtype::Game_info::getNbProjectiles()
{
    return _nbProjectiles;
}

void Rtype::Game_info::accNbProjectiles()
{
    _nbProjectiles += 1;
}

