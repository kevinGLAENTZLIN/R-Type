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

            /**
            * @brief Constructor to health component.
            *
            * Constructor for the life component, which will represent the
            * life of the entities in the video game,
            * with an Integer parameter assigned to the private _health attribute.
            *
            * @tparam Integer to create health component.
            * @return void.
            */
            Health(int health, int invincibility = 0);

            /**
            * @brief Destroy the Health object
            *
            */
            ~Health() = default;


            /**
            * @brief Getter _health to health component.
            *
            * @tparam void.
            * @return Integer based on private attribute _health which represent life of an entity.
            */
            int getHealth() const;


            /**
            * @brief Setter _health to health component.
            *
            * @tparam Integer health which represent life of an entity.
            * @return void.
            */
            void setHealth(int health);

            /**
            * @brief modify the health of the entity
            *
            * @param delta : the value to add or decrease to the health
            * @return void
            */
            void modifyHealthBy(int delta);

            /**
            * @brief Getter _invincibility to health component.
            *
            * @tparam void.
            * @return Integer based on private attribute _invincibility which represent invincibility of an entity.
            */
            int getInvincibility() const;

            /**
            * @brief Setter _invincibility to health component.
            *
            * @tparam Integer invincibility which represent invincibility of an entity.
            * @return void.
            */
            void setInvincibility(int invincibility);

            /**
            * @brief modify the invincibility of the entity
            *
            * @param delta : the value to add or decrease to the invincibility
            * @return void
            */
            void modifyInvincibilityBy(int delta);
        private:
            int _health;
            int _invincibility;
        };
    }
}
