/*
** EPITECH PROJECT, 2024
** R-Type - Components : Text
** File description:
** Text Component
*/

#include "Text.hh"

Components::Text::Text(std::string text):
    _text(text)
{}

std::string Components::Text::getText() const
{
    return _text;
}

void Components::Text::setText(std::string text)
{
    _text = text;
}
