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
            Rotate(float x, float y, float z);
            ~Rotate() = default;

            float getRotateX() const;
            float getRotateY() const;
            float getRotateZ() const;
            void setRotateX(float x);
            void setRotateY(float y);
            void setRotateZ(float z);

        private:
            float _x;
            float _y;
            float _z;
        };
    }
}
