/*
** EPITECH PROJECT, 2024
** R-Type - Components : Text
** File description:
** Text Component
*/
#pragma once

#include <iostream>
#if defined(_WIN32)
	#define NOGDI
	#define NOUSER
#endif

#include "raylib-cpp.hpp"

#if defined(_WIN32)
	#undef near
	#undef far
#endif
namespace ECS {
    namespace Components {

        class Text {
        public:
            /**
            * @brief Constructor of text component.
            *
            * @tparam std::string text : text to display.
            * @tparam int fontSize : size of the text.
            * @tparam raylib::Color color : color of the text.
            * @return void.
            */
            Text(std::string text, int fontSize, raylib::Color color);

            /**
            * @brief Destructor of text component.
            *
            * @return void.
            */
            ~Text() = default;

            /**
            * @brief Get the text.
            *
            * @return std::string : text.
            */
            std::string getText() const;

            /**
            * @brief Set the text.
            *
            * @tparam std::string text : text to display.
            * @return void.
            */
            void setText(std::string text);

            /**
            * @brief Set the font size.
            *
            * @tparam int size : size of the text.
            * @return void.
            */
            void setFontSize(int size);

            /**
            * @brief Get the font size.
            *
            * @return int : size of the text.
            */
            int getFontSize() const;

            /**
            * @brief Set the color.
            *
            * @tparam raylib::Color color : color of the text.
            * @return void.
            */
            void setColor(raylib::Color color);

            /**
            * @brief Get the color.
            *
            * @return raylib::Color : color of the text.
            */
            raylib::Color getColor() const;

        protected:

        private:
            std::string _text;
            int _fontSize;
            raylib::Color _color;
        };
    }
}
