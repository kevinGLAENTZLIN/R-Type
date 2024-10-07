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
    // Enums representing different categories of functions.
    enum InfoTypeEnum {
        GameInfo = 0,
        Player,
        Enemy,
        Boss,
        PowerUp,
        Projectile,
    };

    // Enums for various game-related functions.
    enum GameInfoEnum {
        NewClientConnected = 0,
        GamesAvailable,
        CreateGame,
        JoinGame,
        GameWonLost,
        SafetyCheck,
        LevelComplete
    };

    // Enums for player-related functions.
    enum PlayerEnum {
        PlayerSpawnOnGame = 0,
        PlayerDie,
        PlayerMove,
        PlayerAttack,
        PlayerGotPowerUp,
        PlayerHitAWall,
        PlayerScore
    };

    // Enums for enemy-related functions.
    enum EnemyEnum {
        EnemySpawn = 0,
        EnemyDie,
        EnemyMove,
        EnemyAttack
    };

    // Enums for boss-related functions.
    enum BossEnum {
        BossSpawn = 0,
        BossDie,
        BossAttack
    };

    // Enums for power-up-related functions.
    enum PowerUpEnum {
        PowerUpSpawn = 0,
        PowerUpDisappear,
        PowerUpAttack
    };

    // Enums for projectile-related functions.
    enum ProjectileEnum {
        ProjectileFired = 0,
        ProjectileHit
    };

    // Class managing a mapping of parameters for all functions of the protocol.
    class ParametersMap {
        public:
            /**
             * @brief Initialize the parameters map with all functions and their parameters.
             * 
             * Sets up the mapping of function types and indexes to their corresponding 
             * parameter types expected by the server and client.
             */
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

            /**
             * @brief Get the number of parameters on the server side.
             * @param function_type The category of the function.
             * @param function_index The index of the function.
             * @return The number of parameters expected by the server.
             */
            static int getNbParameterPerFunctionServer(int function_type, int function_index)
            {
                return _parametersMap[{function_type, function_index}].first.length();
            }

            /**
             * @brief Get the number of parameters on the client side.
             * @param function_type The category of the function.
             * @param function_index The index of the function.
             * @return The number of parameters expected by the client.
             */
            static int getNbParameterPerFunctionClient(int function_type, int function_index)
            {
                return _parametersMap[{function_type, function_index}].second.length();
            }

            /**
             * @brief Get the parameter types for a server function.
             * @param function_type The category of the function.
             * @param function_index The index of the function.
             * @return The parameter types expected by the server as a string.
             */
            static std::string getParameterTypePerFunctionServer(int function_type, int function_index)
            {
                return _parametersMap[{function_type, function_index}].first;
            }

            /**
             * @brief Get the parameter types for a client function.
             * @param function_type The category of the function.
             * @param function_index The index of the function.
             * @return The parameter types expected by the client as a string.
             */
            static std::string getParameterTypePerFunctionClient(int function_type, int function_index)
            {
                return _parametersMap[{function_type, function_index}].second;
            }

        private:
            /**
             * @brief Map of function caategories and indexes to parameter types.
             * 
             * The map key is a pair consisting of the function category & index, 
             * while the value is a pair of strings representing the parameter types 
             * expected by the server & client, respectively.
             * Parameter types are denoted by characters (e.g., b: Bool, c: Char, i: Int, f: Float).
             */
            static std::map<std::pair<int, int>, std::pair<std::string, std::string>> _parametersMap; 
    };
}
