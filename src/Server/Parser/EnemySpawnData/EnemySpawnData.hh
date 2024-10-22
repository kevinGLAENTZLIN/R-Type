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

namespace Rtype {

    class EnemySpawnData {
    public:
        EnemySpawnData();
        ~EnemySpawnData() = default;

        void setType(enemiesTypeEnum_t type);
        void setPositionX(float position_x);
        void setPositionY(float position_y);
        void setModel(std::string model);
        void setSpawnTime(std::pair <int, int> spawnTime);

        enemiesTypeEnum_t getType() const;
        float getPositionX() const;
        float getPositionY() const;
        std::string getModel() const;
        std::pair <int, int> getSpawnTime() const;

    private:

        enemiesTypeEnum_t _type;
        int difficulty;
        float _position_x;
        float _position_y;
        std::string _model;
        std::pair<int, int> _spawnTime;
    };
}
