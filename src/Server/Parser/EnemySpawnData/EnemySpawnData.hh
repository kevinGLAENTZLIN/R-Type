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

namespace Rtype {

    class EnemySpawnData {
        public:
            EnemySpawnData();
            ~EnemySpawnData() = default;

            void setType(const std::string &type);
            void setPositionX(float position_x);
            void setPositionY(float position_y);
            void setModel(std::string model);
            void setSpawnTime(std::pair <int, int> spawnTime);

            std::string getType() const;
            float getPositionX() const;
            float getPositionY() const;
            std::string getModel() const;
            std::pair <int, int> getSpawnTime() const;

        private:

            std::string _type;
            float _position_x;
            float _position_y;
            std::string _model;
            std::pair<int, int> _spawnTime;
    };
}
