/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** EnemySpawnData.hh
*/

#pragma once
#include <iostream>
#include <numeric>
#include <utility>
#include "../../../Utils/enemiesTypeEnum.hpp"

#include "../../../Utils/enemiesTypeEnum.hpp"

namespace Rtype {

    class EnemySpawnData {
    public:
        /**
        * @brief EnemySpawnData constructor.
        * @param void
        * @return void
        */
        EnemySpawnData();

        /**
        * @brief set the type of the enemy
        * @param enemiesTypeEnum_t type
        * @return void
        */
        ~EnemySpawnData() = default;

        /**
        * @brief set the type of the enemy
        * @param enemiesTypeEnum_t type
        * @return void
        */
        void setType(enemiesTypeEnum_t type);

        /**
        * @brief set the difficulty of the enemy
        * @param int difficulty
        * @return void
        */
        void setDifficulty(int difficulty);

        /**
        * @brief set the position x of the enemy
        * @param float position_x
        * @return void
        */
        void setPositionX(float position_x);

        /**
        * @brief set the position y of the enemy
        * @param float position_y
        * @return void
        */
        void setPositionY(float position_y);

        /**
        * @brief set the health of the enemy
        * @param int health
        * @return void
        */
        void setHealth(int health);

        /**
        * @brief set the model of the enemy
        * @param std::string model
        * @return void
        */
        void setModel(std::string model);

        /**
        * @brief set the spawn time of the enemy
        * @param std::pair <int, int> spawnTime
        * @return void
        */
        void setSpawnTime(std::pair <int, int> spawnTime);

        /**
        * @brief set the spawn time in seconds of the enemy
        * @param int spawnTimeInSeconds
        * @return void
        */
        int getSpawnTimeInSeconds() const;

        /**
        * @brief get the type of the enemy
        * @param void
        * @return enemiesTypeEnum_t
        */
        enemiesTypeEnum_t getType() const;

        /**
        * @brief get the difficulty of the enemy
        * @param void
        * @return int
        */
        int getDifficulty() const;

        /**
        * @brief get the position x of the enemy
        * @param void
        * @return float
        */
        float getPositionX() const;

        /**
        * @brief get the position y of the enemy
        * @param void
        * @return float
        */
        float getPositionY() const;

        /**
        * @brief get the health of the enemy
        * @param void
        * @return int
        */
        int getHealth() const;

        /**
        * @brief get the model of the enemy
        * @param void
        * @return std::string
        */
        std::string getModel() const;

        /**
        * @brief get the spawn time of the enemy
        * @param void
        * @return std::pair <int, int>
        */
        std::pair <int, int> getSpawnTime() const;

    private:

        enemiesTypeEnum_t _type;
        int _difficulty;
        float _position_x;
        float _position_y;
        int _health;
        std::string _model;
        int _spawnTimeInSeconds;
        std::pair<int, int> _spawnTime;
    };
}
