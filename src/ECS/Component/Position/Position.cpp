/*
** EPITECH PROJECT, 2024
** R-Type - Components : Position
** File description:
** Position Component
*/

#include "Position.hpp"
#include <ostream>

/**
 * @brief Constructor of Position component.
 *
 * @tparam float x, float y.
 * @return void.
 */
ECS::Components::Position::Position(float x, float y):
    _x(x), _y(y)
{}

/**
 * @brief Getter _X to Position component.
 *
 * @tparam void.
 * @return Float based on private attribute _x which represent position in row of an position entity.
 */
float ECS::Components::Position::getX() const
{
    return _x;
}

/**
 * @brief Getter _Y to Position component.
 *
 * @tparam void.
 * @return Float based on private attribute _y which represent position in column of an position entity.
 */
float ECS::Components::Position::getY() const
{
    return _y;
}

/**
 * @brief Setter _X to Position component.
 *
 * @tparam float x.
 * @return void.
 */
void ECS::Components::Position::setX(float x)
{
    _x = x;
}

/**
 * @brief Setter _Y to Position component.
 *
 * @tparam float y.
 * @return void.
 */
void ECS::Components::Position::setY(float y)
{
    _y = y;
}

/**
 * @brief Getter _X and _Y to Position component.
 *
 * @tparam void.
 * @return std::pair<float, float> based on private attribute _x and _y
 * which represent position in row and column of an position entity
 */
std::pair<float, float> ECS::Components::Position::getPosPair() const
{
    return std::make_pair(_x, _y);
}
