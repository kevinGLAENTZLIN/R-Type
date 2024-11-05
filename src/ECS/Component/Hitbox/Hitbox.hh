/*
** EPITECH PROJECT, 2024
** R-Type - Components : Hitbox
** File description:
** Hitbox Component
*/
#pragma once

#include <iostream>

namespace ECS {
    namespace Components {

        class Hitbox {
        public:
            /**
            * @brief Constructor of Hitbox component.
            *
            * @tparam float width that represents width of an hitbox entity.
            * @tparam float height that represents height of an hitbox entity.
            * @return void.
            */
            Hitbox(float width, float height);

            /**
            * @brief Destructor of Hitbox component.
            *
            * @tparam void.
            * @return void.
            */
            ~Hitbox() = default;

            /**
            * @brief Getter _width to Hitbox component.
            *
            * @tparam void.
            * @return Float based on private attribute _width which represent with of an hitbox entity.
            */
            float getWidth() const;

            /**
            * @brief Getter _height to Hitbox component.
            *
            * @tparam void.
            * @return Float based on private attribute _height which represent height of an hitbox entity.
            */
            float getHeight() const;

            /**
            * @brief Setter _width to Hitbox component.
            *
            * @tparam Float width that represents width of an hitbox entity.
            * @return void.
            */
            void setWidth(float width);

            /**
            * @brief Setter _height to Hitbox component.
            *
            * @tparam Float height that represents height of an hitbox entity.
            * @return void.
            */
            void setHeight(float height);

        private:
            float _width;
            float _height;
        };
    }
}
