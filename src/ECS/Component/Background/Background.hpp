/*
** EPITECH PROJECT, 2024
** R-Type - Components : Background
** File description:
** Background Component
*/

#pragma once

#include <iostream>

namespace ECS {
    namespace Components {

        class Background {
        public:
            /**
            * @brief Background constructor
            * @param width
            * @param speed
            */
            Background(float width, float speed) {
                _width = width;
                _speed = speed;
            }

            /**
            * @brief Background destructor
            */
            ~Background() = default;

            /**
            * @brief set width
            * @param float width
            */
            void setWidth(float width) { _width = width; }

            /**
            * @brief set speed
            * @param float speed
            */
            void setSpeed(float speed) { _speed = speed; }

            /**
            * @brief get width
           * @return float
           */
            float getWidth() const { return _width; }

            /**
            * @brief get speed
            * @return float
            */
            float getSpeed() const { return _speed; }

        private:
            float _width;
            float _speed;
        };
    }
}
