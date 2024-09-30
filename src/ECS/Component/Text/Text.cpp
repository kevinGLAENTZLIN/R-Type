/*
** EPITECH PROJECT, 2024
** R-Type - Components : Text
** File description:
** Text Component
*/

#include "Text.hh"

/**
 * @brief Constructor of Text component.
 *
 * @tparam std::string text.
 * @return void.
 */
ECS::Components::Text::Text(std::string text):
    _text(text)
{}

/**
 * @brief Get the text of the component.
 *
 * @tparam void.
 * @return std::string.
*/
std::string ECS::Components::Text::getText() const
{
    return _text;
}

/**
 * @brief Set the text of the component.
 *
 * @tparam std::string text.
 * @return void.
 */
void ECS::Components::Text::setText(std::string text)
{
    _text = text;
}
