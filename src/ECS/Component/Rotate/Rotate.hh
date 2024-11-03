/*
** EPITECH PROJECT, 2024
** R-Type - Components : Rotate
** File description:
** Position Component
*/
#pragma once

#include <iostream>

namespace ECS {
    namespace Components {

        class Rotate {
        public:
            /**
            * @brief Constructor of Rotate component.
            *
            * @tparam float x : x value of the scale.
            * @tparam float y : y value of the scale.
            * @tparam float z : z value of the scale.
            * @return void.
            */
            Rotate(float x, float y, float z);

            /**
            * @brief Destructor of Rotate component.
            *
            * @return void.
            */
            ~Rotate() = default;

            /**
            * @brief Get the roll value of the rotate.
            *
            * @return float : roll value of the rotate.
            */
            float getRoll() const;

            /**
            * @brief Get the pitch value of the rotate.
            *
            * @return float : pitch value of the rotate.
            */
            float getPitch() const;

            /**
            * @brief Get the yaw value of the rotate.
            *
            * @return float : yaw value of the rotate.
            */
            float getYaw() const;

            /**
            * @brief Set the rotate value of the rotate.
            *
            * @tparam float roll : roll value of the rotate.
            * @tparam float pitch : pitch value of the rotate.
            * @tparam float yaw : yaw value of the rotate.
            * @return void.
            */
            void setRotate(float roll, float pitch, float yaw);

            /**
            * @brief Set the roll value of the rotate.
            *
            * @tparam float roll : roll value of the rotate.
            * @return void.
            */
            void setRoll(float roll);

            /**
            * @brief Set the pitch value of the rotate.
            *
            * @tparam float pitch : pitch value of the rotate.
            * @return void.
            */
            void setPitch(float pitch);

            /**
            * @brief Set the yaw value of the rotate.
            *
            * @tparam float yaw : yaw value of the rotate.
            * @return void.
            */
            void setYaw(float yaw);

        private:
            float _roll;
            float _pitch;
            float _yaw;
        };
    }
}
