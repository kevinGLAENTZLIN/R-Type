/*
** EPITECH PROJECT, 2024
** Enemy.hh
** File description:
** Enemy class
*/

#include <cstddef>
#include <iostream>

class Enemy {

    public:
        Enemy(std::size_t id);
        ~Enemy() = default;

        std::size_t getId() const;

    protected:

    private:
        std::size_t _id;

};
