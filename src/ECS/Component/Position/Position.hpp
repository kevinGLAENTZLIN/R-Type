/*
** EPITECH PROJECT, 2024
** R-Type - Components : Position
** File description:
** Position Component
*/
#pragma once

#include <iostream>

namespace ECS {
    namespace Components {

        class Position {
        public:
            Position(float x, float y);
            ~Position() = default;

            float getX() const;
            float getY() const;
            void setX(float x);
            void setY(float y);
            std::pair<float, float> getPosPair() const;

        private:
            float _x;
            float _y;
        };

        inline std::ostream & operator<< (std::ostream & stream, const Position & position) {
            stream << "(" << position.getX() << ", " << position.getY() << ")";
            return stream;
        }
    }
}
