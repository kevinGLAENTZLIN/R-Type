/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Factory
*/

#include "Factory.hh"

Rtype::Command::Factory::Factory()
{
    _commandMap[{Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::NewClientConnected}] = []() {return std::make_unique<GameInfo::Client_connection>();};
    _commandMap[{Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::CreateGame}] = []() {return std::make_unique<GameInfo::Create_game>();};
    _commandMap[{Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::GameWonLost}] = []() {return std::make_unique<GameInfo::Game_result>();};
    _commandMap[{Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::GamesAvailable}] = []() {return std::make_unique<GameInfo::Games_available>();};
    _commandMap[{Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::JoinGame}] = []() {return std::make_unique<GameInfo::Join_game>();};
    _commandMap[{Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::LevelComplete}] = []() {return std::make_unique<GameInfo::Level_complete>();};

    _commandMap[{Utils::InfoTypeEnum::Player, Utils::PlayerEnum::PlayerAttack}] = []() {return std::make_unique<Player::Attack>();};
    _commandMap[{Utils::InfoTypeEnum::Player, Utils::PlayerEnum::PlayerDie}] = []() {return std::make_unique<Player::Die>();};
    _commandMap[{Utils::InfoTypeEnum::Player, Utils::PlayerEnum::PlayerHitAWall}] = []() {return std::make_unique<Player::Hit_wall>();};
    _commandMap[{Utils::InfoTypeEnum::Player, Utils::PlayerEnum::PlayerMove}] = []() {return std::make_unique<Player::Move>();};
    _commandMap[{Utils::InfoTypeEnum::Player, Utils::PlayerEnum::PlayerGotPowerUp}] = []() {return std::make_unique<Player::Power_up>();};
    _commandMap[{Utils::InfoTypeEnum::Player, Utils::PlayerEnum::PlayerScore}] = []() {return std::make_unique<Player::Score>();};
    _commandMap[{Utils::InfoTypeEnum::Player, Utils::PlayerEnum::PlayerSpawnOnGame}] = []() {return std::make_unique<Player::Spawn>();};

    _commandMap[{Utils::InfoTypeEnum::Enemy, Utils::EnemyEnum::EnemyAttack}] = []() {return std::make_unique<Enemy::Attack>();};
    _commandMap[{Utils::InfoTypeEnum::Enemy, Utils::EnemyEnum::EnemyDie}] = []() {return std::make_unique<Enemy::Die>();};
    _commandMap[{Utils::InfoTypeEnum::Enemy, Utils::EnemyEnum::EnemySpawn}] = []() {return std::make_unique<Enemy::Spawn>();};

    _commandMap[{Utils::InfoTypeEnum::Boss, Utils::BossEnum::BossAttack}] = []() {return std::make_unique<Boss::Attack>();};
    _commandMap[{Utils::InfoTypeEnum::Boss, Utils::BossEnum::BossDie}] = []() {return std::make_unique<Boss::Die>();};
    _commandMap[{Utils::InfoTypeEnum::Boss, Utils::BossEnum::BossSpawn}] = []() {return std::make_unique<Boss::Spawn>();};

    _commandMap[{Utils::InfoTypeEnum::Projectile, Utils::ProjectileEnum::ProjectileFired}] = []() {return std::make_unique<Projectile::Fired>();};
    _commandMap[{Utils::InfoTypeEnum::Projectile, Utils::ProjectileEnum::ProjectileHit}] = []() {return std::make_unique<Projectile::Hit>();};
}

std::unique_ptr<Rtype::Command::ICommand> Rtype::Command::Factory::createCommand(int cmd_category, int cmd_index)
{
    auto it = _commandMap.find({cmd_category, cmd_index});

    if (it != _commandMap.end())
        return it->second();
    return nullptr;
}
