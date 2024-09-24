/*
** EPITECH PROJECT, 2024
** R-Type - Components : Health
** File description:
** Health Component
*/

#pragma once
#include <iostream>

namespace Components {

    class Health {
        public:
            Health(int health);
            ~Health() = default;
            int GetHealth() const;
            void SetHealth(int health);

        protected:

        private:
            int _health;
    };
};
