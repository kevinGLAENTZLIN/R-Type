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
#include <stack>
#include <algorithm>

#include "../EnemySpawnData/EnemySpawnData.hh"
#include "../../../Utils/enemiesTypeEnum.hpp"

namespace Rtype {

    class LoadData {
        public:
            /**
            * @brief Loaddate constructor.
            * @param void
            * @return void
            */
            LoadData();

            /**
            * @brief Loaddate destructor.
           * @param void
           * @return void
           */
            ~LoadData() = default;

            /**
            * @brief Load data from a file.
            * @param const std::string &path
            * @return void
            */
            void LoadDataFromFile(const std::string &path);

            /**
            * @brief Get enemy spawn data.
            * @param void
            * @return std::stack<Rtype::EnemySpawnData>
            */
            std::stack<Rtype::EnemySpawnData> GetEnemySpawnData() const;

            /**
            * @brief Clear enemy spawn data.
            * @param void
            * @return void
            */
            void clearEnemySpawnData();

        private:
            enemiesTypeEnum_t convertStringToEnumType(const std::string &text);
            std::stack<Rtype::EnemySpawnData> _enemySpawnData;

    };
}
