/*
** EPITECH PROJECT, 2024
** Player.hh
** File description:
** Player class
*/

#include <cstddef>
#include <iostream>

class Player {

    public:
        Player(std::size_t id);
        ~Player() = default;

        std::size_t getId() const;

    protected:

    private:
        std::size_t _id;

};
