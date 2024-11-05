/*
** EPITECH PROJECT, 2024
** R-Type - Components : Position
** File description:
** Position Component
*/
#pragma once

#include <iostream>
#include <tuple>

namespace ECS {
    namespace Components {

        class Position {
        public:
            /**
            * @brief Constructor of Position component.
            *
            * @tparam float x, float y, float z.
            * @return void.
            */
            Position(float x, float y, float z = 0);

            /**
            * @brief Destructor of Position component.
            *
            * @return void.
            */
            ~Position() = default;


            /**
            * @brief Getter _X to Position component.
            *
            * @tparam void.
            * @return Float based on private attribute _x which represent position in row of an position entity.
            */
            float getX() const;

            /**
            * @brief Getter _Y to Position component.
            *
            * @tparam void.
            * @return Float based on private attribute _y which represent position in column of an position entity.
            */
            float getY() const;

            /**
            * @brief Getter _Z to Position component.
            *
            * @tparam void.
            * @return Float based on private attribute _z which represent position in depth of an position entity.
            */
            float getZ() const;

            /**
            * @brief Getter _X to Position component.
            *
            * @tparam void.
            * @return Float based on private attribute _xOriginalPos which represent original position in row of an position entity.
            */
            float getOriginalX() const;

            /**
            * @brief Getter _Y to Position component.
            *
            * @tparam void.
            * @return Float based on private attribute _yOriginalPos which represent original position in column of an position entity.
            */
            float getOriginalY() const;

            /**
            * @brief Getter _Z to Position component.
            *
            * @tparam void.
            * @return Float based on private attribute _zOriginalPos which represent original position in depth of an position entity.
            */
            float getOriginalZ() const;

            /**
            * @brief Setter _X to Position component.
            *
            * @tparam float x.
            * @return void.
            */
            void setX(float x);

            /**
            * @brief Setter _Y to Position component.
            *
            * @tparam float y.
            * @return void.
            */
            void setY(float y);

            /**
            * @brief Setter _Z to Position component.
            *
            * @tparam float z.
            * @return void.
            */
            void setZ(float z);

            /**
            * @brief getPosPair to Position component.
            *
            * @tparam void.
            * @return std::pair<float, float> based on private attribute _x and _y which represent position in row and column of an position entity.
            */
            std::pair<float, float> getPosPair() const;

            /**
            * @brief gePosition to Position component.
            *
            * @tparam void.
            * @return std::tuple<float, float, float> based on private attribute _x, _y and _z which represent position in row, column and depth of an position entity.
            */
            std::tuple<float, float, float> getPosition() const;
        private:
            float _xOriginalPos;
            float _yOriginalPos;
            float _zOriginalPos;
            float _x;
            float _y;
            float _z;
        };

        inline std::ostream & operator<< (std::ostream & stream, const Position & position) {
            stream << "(" << position.getX() << ", " << position.getY() << ")";
            return stream;
        }
    }
}
