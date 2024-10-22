/*
** EPITECH PROJECT, 2024
** R-Type - Components : AI
** File description:
** AI Component
*/
#pragma once

#include "../../../Utils/enemiesTypeEnum.hpp"

namespace ECS {
    namespace Components {

        class AI {
        public:
            AI(enemiesTypeEnum_t enemyType);
            ~AI() = default;

            enemiesTypeEnum_t getEnemyType() const;
            void setEnemyType(enemiesTypeEnum_t enemyType);

            void setFiring(bool isFiring);
            void flipFiring();
            bool isFiring() const;

            void setCooldown(std::size_t cooldown);
            std::size_t getCooldown() const;
        private:
            enemiesTypeEnum_t _enemyType;
            bool _isFiring;
            std::size_t _cooldown;
        };
    }
}
