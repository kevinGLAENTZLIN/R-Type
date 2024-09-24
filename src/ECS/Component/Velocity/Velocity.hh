/*
** EPITECH PROJECT, 2024
** R-Type - Components : Velocity
** File description:
** Velocity Component
*/

#pragma once
#include <iostream>

namespace Components {

    class Velocity {
    public:
        Velocity(float x, float y);
        Velocity(std::pair<float, float> vel);
        ~Velocity() = default;

        float getX() const;
        float getY() const;
        std::pair<float, float> getVelPair() const;

    private:
        float _x;
        float _y;
    };

    std::ostream & operator<< (std::ostream & stream, const Velocity & velocity);
}
