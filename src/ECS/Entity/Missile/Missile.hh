/*
** EPITECH PROJECT, 2024
** Missile.hh
** File description:
** EntityManeger class
*/

#include <cstddef>
#include <iostream>

class Missile {

    public:
        Missile(std::size_t id);
        ~Missile() = default;

        std::size_t getId() const;

    protected:

    private:
        std::size_t _id;

};
