/*
** EPITECH PROJECT, 2024
** R-Type - Components : Velocity
** File description:
** Velocity Component
*/
#pragma once

#include <iostream>

namespace ECS {
    namespace Components {

        class Velocity {
        public:

            /**
            * @brief Constructor of Velocity component.
            *
            * @tparam float x, float y.
            * @return void.
            */
            Velocity(float x, float y);

            /**
            * @brief Constructor of Velocity component.
            *
            * @tparam std::pair<float, float> vel.
            * @return void.
            */
            Velocity(std::pair<float, float> vel);
            ~Velocity() = default;

            /**
            * @brief Getter _x of Velocity component.
            *
            * @tparam void.
            * @return float _x.
            */
            float getX() const;

            /**
            * @brief Getter _y of Velocity component.
            *
            * @tparam void.
            * @return float _y.
            */
            float getY() const;

            /**
            * @brief Setter _x of Velocity component.
            *
            * @tparam float x.
            * @return void.
            */
            void setX(float x);

            /**
            * @brief Setter _y of Velocity component.
            *
            * @tparam float y.
            * @return void.
            */
            void setY(float y);

            /**
            * @brief Getter _x and _y of Velocity component.
            *
            * @tparam void.
            * @return std::pair<float, float> _x and _y.
            */
            std::pair<float, float> getVelPair() const;

            /**
            * @brief Setter _x and _y of Velocity component.
            *
            * @tparam std::pair<float, float> vel.
            * @return void.
            */
            void setVelPair(std::pair<float, float> vel);

        private:
            float _x;
            float _y;
        };

        inline std::ostream & operator<< (std::ostream & stream, const Components::Velocity & velocity) {
            stream << "(" << velocity.getX() << ", " << velocity.getY() << ")";
            return stream;
        }
    }
}
