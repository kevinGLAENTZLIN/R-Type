/*
** EPITECH PROJECT, 2024
** R-Type - Components : Positions
** File description:
** Position Component
*/
#pragma once

#include <iostream>

namespace Components {

    class Position {
    public:
        Position(std::size_t row, std::size_t col): _row(row), _col(col){};
        Position(std::pair<size_t, size_t> pos): _row(pos.first), _col(pos.second){};
        ~Position() = default;

        std::size_t getRow() const {
            return _row;
        };
        std::size_t getCol() const {
            return _col;
        };
        std::pair<std::size_t, std::size_t> getPosPair() const {
            return std::make_pair(_row, _col);
        };

    private:
        std::size_t _row;
        std::size_t _col;
    };

    std::ostream & operator<< (std::ostream & stream, const Position & position) {
        stream << "(" << position.getRow() << ", " << position.getCol() << ")";
        return stream;
    };
}
