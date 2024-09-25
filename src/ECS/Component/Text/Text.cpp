/*
** EPITECH PROJECT, 2024
** R-Type - Components : Text
** File description:
** Text Component
*/

#include "Text.hh"

ECS::Components::Text::Text(std::string text):
    _text(text)
{}

std::string ECS::Components::Text::getText() const
{
    return _text;
}

void ECS::Components::Text::setText(std::string text)
{
    _text = text;
}
