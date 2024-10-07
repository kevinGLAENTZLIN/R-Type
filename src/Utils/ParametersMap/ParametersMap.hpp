/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ParametersMap
*/

#pragma once

#include <iostream>
#include <map>

namespace Utils
{
    enum InfoTypeEnum {
        GameInfo = 0,
        Player,
        Enemy,
        Boss,
        PowerUp,
        Projectile,
    };

    enum GameInfoEnum {
        NewClientConnected = 0,
        GamesAvailable,
        CreateGame,
        JoinGame,
        GameWonLost,
        SafetyCheck,
        LevelComplete
    };

    enum PlayerEnum {
        PlayerSpawnOnGame = 0,
        PlayerDie,
        PlayerMove,
        PlayerAttack,
        PlayerGotPowerUp,
        PlayerHitAWall,
        PlayerScore
    };

    enum EnemyEnum {
        EnemySpawn = 0,
        EnemyDie,
        EnemyMove,
        EnemyAttack
    };

    enum BossEnum {
        BossSpawn = 0,
        BossDie,
        BossAttack
    };

    enum PowerUpEnum {
        PowerUpSpawn = 0,
        PowerUpDisappear,
        PowerUpAttack
    };

    enum ProjectileEnum {
        ProjectileFired = 0,
        ProjectileHit
    };

    class ParametersMap {
        public:
            static void init_map() 
            {
                _parametersMap = {
                    {{InfoTypeEnum::GameInfo, GameInfoEnum::NewClientConnected}, {"bbi", "if"}},
                    {{InfoTypeEnum::GameInfo, GameInfoEnum::GamesAvailable}, {"", ""}},
                    {{InfoTypeEnum::GameInfo, GameInfoEnum::CreateGame}, {"", ""}},
                    {{InfoTypeEnum::GameInfo, GameInfoEnum::JoinGame}, {"", ""}},
                    {{InfoTypeEnum::GameInfo, GameInfoEnum::GameWonLost}, {"", ""}},
                    {{InfoTypeEnum::GameInfo, GameInfoEnum::SafetyCheck}, {"", ""}},
                    {{InfoTypeEnum::GameInfo, GameInfoEnum::LevelComplete}, {"", ""}},

                    {{InfoTypeEnum::Player, PlayerEnum::PlayerSpawnOnGame}, {"", ""}},
                    {{InfoTypeEnum::Player, PlayerEnum::PlayerDie}, {"", ""}},
                    {{InfoTypeEnum::Player, PlayerEnum::PlayerMove}, {"", ""}},
                    {{InfoTypeEnum::Player, PlayerEnum::PlayerAttack}, {"", ""}},
                    {{InfoTypeEnum::Player, PlayerEnum::PlayerGotPowerUp}, {"", ""}},
                    {{InfoTypeEnum::Player, PlayerEnum::PlayerHitAWall}, {"", ""}},
                    {{InfoTypeEnum::Player, PlayerEnum::PlayerScore}, {"", ""}},

                    {{InfoTypeEnum::Enemy, EnemyEnum::EnemySpawn}, {"", ""}},
                    {{InfoTypeEnum::Enemy, EnemyEnum::EnemyDie}, {"", ""}},
                    {{InfoTypeEnum::Enemy, EnemyEnum::EnemyMove}, {"", ""}},
                    {{InfoTypeEnum::Enemy, EnemyEnum::EnemyAttack}, {"", ""}},

                    {{InfoTypeEnum::Boss, BossEnum::BossSpawn}, {"", ""}},
                    {{InfoTypeEnum::Boss, BossEnum::BossDie}, {"", ""}},
                    {{InfoTypeEnum::Boss, BossEnum::BossAttack}, {"", ""}},

                    {{InfoTypeEnum::PowerUp, PowerUpEnum::PowerUpSpawn}, {"", ""}},
                    {{InfoTypeEnum::PowerUp, PowerUpEnum::PowerUpDisappear}, {"", ""}},
                    {{InfoTypeEnum::PowerUp, PowerUpEnum::PowerUpAttack}, {"", ""}},

                    {{InfoTypeEnum::Projectile, ProjectileEnum::ProjectileFired}, {"", ""}},
                    {{InfoTypeEnum::Projectile, ProjectileEnum::ProjectileHit}, {"", ""}},
                };
            }

            static int getNbParameterPerFunctionServer(int function_type, int function_index)
            {
                return _parametersMap[{function_type, function_index}].first.length();
            }

            static int getNbParameterPerFunctionClient(int function_type, int function_index)
            {
                return _parametersMap[{function_type, function_index}].second.length();
            }

            static std::string getParameterTypePerFunctionServer(int function_type, int function_index)
            {
                return _parametersMap[{function_type, function_index}].first;
            }

            static std::string getParameterTypePerFunctionClient(int function_type, int function_index)
            {
                return _parametersMap[{function_type, function_index}].second;
            }


        private:
            // Correspond to the map of all functions available with the protocol.
            //
            // The first pair correspond to the key : function type & function index.
            // Function type and index are set in some Enums
            //
            // The second pair correspond to the type of parameter. (b: Bool, c: Char, i: Int, f: Float)
            // The first string is about parameters awaited on the server side, the second one is by the client side.
            static std::map<std::pair<int, int>, std::pair<std::string, std::string>> _parametersMap; 
    };
}