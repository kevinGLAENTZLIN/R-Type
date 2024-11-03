/*
** EPITECH PROJECT, 2024
** R-Type - Components : Scale
** File description:
** Scale Component
*/
#pragma once

#include <iostream>

namespace ECS {
    namespace Components {

        class Scale {
        public:
            /**
            * @brief Constructor of Scale component.
            *
            * @tparam float scale : scale of the entity.
            * @return void.
            */
            Scale(float scale);

            /**
            * @brief Destructor of Scale component.
            *
            * @return void.
            */
            ~Scale() = default;

            /**
            * @brief Get the scale of the entity.
            *
            * @return float : scale of the entity.
            */
            float getScale() const;

            /**
            * @brief Set the scale of the entity.
            *
            * @param float scale : scale of the entity.
            * @return void.
            */
            void setScale(float scale);

        private:
            float _scale;
        };
    }
}
