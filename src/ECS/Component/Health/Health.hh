/*
** EPITECH PROJECT, 2024
** R-Type - Components : Health
** File description:
** Health Component
*/
#pragma once

#include <iostream>

namespace ECS {
    namespace Components {

        class Health {
        public:
            Health(int health);
            ~Health() = default;
            int getHealth() const;
            void setHealth(int health);

        protected:

        private:
            int _health;
        };
    }
}
