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
                    {{InfoTypeEnum::GameInfo, GameInfoEnum::NewClientConnected}, {0, 0}},
                    {{InfoTypeEnum::GameInfo, GameInfoEnum::GamesAvailable}, {0, 0}},
                    {{InfoTypeEnum::GameInfo, GameInfoEnum::CreateGame}, {0, 0}},
                    {{InfoTypeEnum::GameInfo, GameInfoEnum::JoinGame}, {0, 0}},
                    {{InfoTypeEnum::GameInfo, GameInfoEnum::GameWonLost}, {0, 0}},
                    {{InfoTypeEnum::GameInfo, GameInfoEnum::SafetyCheck}, {0, 0}},
                    {{InfoTypeEnum::GameInfo, GameInfoEnum::LevelComplete}, {0, 0}},

                    {{InfoTypeEnum::Player, PlayerEnum::PlayerSpawnOnGame}, {0, 0}},
                    {{InfoTypeEnum::Player, PlayerEnum::PlayerDie}, {0, 0}},
                    {{InfoTypeEnum::Player, PlayerEnum::PlayerMove}, {0, 0}},
                    {{InfoTypeEnum::Player, PlayerEnum::PlayerAttack}, {0, 0}},
                    {{InfoTypeEnum::Player, PlayerEnum::PlayerGotPowerUp}, {0, 0}},
                    {{InfoTypeEnum::Player, PlayerEnum::PlayerHitAWall}, {0, 0}},
                    {{InfoTypeEnum::Player, PlayerEnum::PlayerScore}, {0, 0}},

                    {{InfoTypeEnum::Enemy, EnemyEnum::EnemySpawn}, {0, 0}},
                    {{InfoTypeEnum::Enemy, EnemyEnum::EnemyDie}, {0, 0}},
                    {{InfoTypeEnum::Enemy, EnemyEnum::EnemyMove}, {0, 0}},
                    {{InfoTypeEnum::Enemy, EnemyEnum::EnemyAttack}, {0, 0}},

                    {{InfoTypeEnum::Boss, BossEnum::BossSpawn}, {0, 0}},
                    {{InfoTypeEnum::Boss, BossEnum::BossDie}, {0, 0}},
                    {{InfoTypeEnum::Boss, BossEnum::BossAttack}, {0, 0}},

                    {{InfoTypeEnum::PowerUp, PowerUpEnum::PowerUpSpawn}, {0, 0}},
                    {{InfoTypeEnum::PowerUp, PowerUpEnum::PowerUpDisappear}, {0, 0}},
                    {{InfoTypeEnum::PowerUp, PowerUpEnum::PowerUpAttack}, {0, 0}},

                    {{InfoTypeEnum::Projectile, ProjectileEnum::ProjectileFired}, {0, 0}},
                    {{InfoTypeEnum::Projectile, ProjectileEnum::ProjectileHit}, {0, 0}},
                };
            }

            static int getParameterPerFunctionServer(int function_type, int function_index)
            {
                return _parametersMap[{function_type, function_index}].first;
            }

            static int getParameterPerFunctionClient(int function_type, int function_index)
            {
                return _parametersMap[{function_type, function_index}].second;
            }


        private:
            // Correspond to the map of all functions available with the protocol.
            // The first pair of int correspond to the key : function type & function index.
            // Function type and index are set in various Enum
            // The second pair of int correspond to the number of parameter.
            // The first int is about parameters awaited on the server side, the second one is by the client side.
            static std::map<std::pair<int, int>, std::pair<int, int>> _parametersMap; 
    };
}