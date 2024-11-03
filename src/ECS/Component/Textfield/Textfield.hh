/*
** EPITECH PROJECT, 2024
** R-Type - Components : TextField
** File description:
** TextField Component
*/

#pragma once

#include <string>
#include <functional>
#include "raylib-cpp.hpp"

namespace ECS {
    namespace Components {

        class TextField {
        public:
            /**
            * @brief Textfield constructor component.
            *
            * @param bounds Rectangle of the textfield.
            * @param isActive If the textfield is active.
            * @param initialText Initial text of the textfield.
            * @param fontSize Font size of the textfield.
            * @param color Color of the textfield.
            */
            TextField(const Rectangle &bounds, bool isActive = false, const std::string &initialText = "", int fontSize = 20, Color color = RAYWHITE);

            /**
            * @brief Textfield destructor component.
            */
            ~TextField() = default;

            /**
            * @brief getBounds of the textfield.
            *
            * @return Rectangle of the textfield.
            */
            Rectangle getBounds() const;

            /**
            * @brief getText of the textfield.
            *
            * @return Text of the textfield.
            */
            std::string getText() const;

            /**
            * @brief setText of the textfield.
            *
            * @param text Text to set.
            */
            void setText(const std::string &text);

            /**
            * @brief isActive of the textfield.
            *
            * @return If the textfield is active.
            */
            bool isActive() const;

            /**
            * @brief setActive of the textfield.
            *
            * @param isActive If the textfield is active.
            */
            void setActive(bool isActive);

            /**
            * @brief onTextChange of the textfield.
            *
            * @param callback Callback to call when the text change.
            */
            void onTextChange(std::function<void(const std::string&)> callback);

            /**
            * @brief is Mouse Over the textfield.
            *
            * @param mouseX Mouse X position.
            * @param mouseY Mouse Y position.
            * @return If the mouse is over the textfield.
            */
            bool isMouseOver(int mouseX, int mouseY) const;

            /**
            * @brief addCharacter to the textfield.
            *
            * @param newChar Character to add.
            */
            bool canAddCharacter(char newChar, int fontSize) const;

            /**
            * @brief getFontSize of the textfield.
            *
            * @return Font size of the textfield.
            */
            int getFontSize() const;

        private:
            Rectangle _bounds;
            bool _isActive;
            std::string _text;
            std::function<void(const std::string&)> _onTextChange;
            int _fontSize;
            Color _color;

        };

    }
}
