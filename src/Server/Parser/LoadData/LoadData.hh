/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Loaddata
*/

#pragma once
#include <iostream>
#include <fstream>
#include <json/json.h>
#include <vector>

#include "../EnemySpawnData/EnemySpawnData.hh"

namespace Rtype {

    class LoadData {
        public:
            LoadData();
            ~LoadData() = default;

            void LoadDataFromFile(const std::string &path);
            std::vector<Rtype::EnemySpawnData> GetEnemySpawnData() const;

        private:
            enemiesTypeEnum_t convertStringToEnumType(const std::string &text);
            std::vector<Rtype::EnemySpawnData> _enemySpawnData;

    };
}
