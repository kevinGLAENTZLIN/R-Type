/*
** EPITECH PROJECT, 2024
** R-Type - Components : Button
** File description:
** Button Component
*/

#pragma once

#include <functional>
#include "raylib-cpp.hpp"

namespace ECS {
    namespace Components {

        class Button {
        public:
            Button(const Rectangle &bounds, bool isSelected = false, std::function<void()> onClick = nullptr);
            ~Button() = default;

            Rectangle getBounds() const;
            void setBounds(const Rectangle &bounds);

            bool isSelected() const;
            void setSelected(bool isSelected);

            void setOnClick(std::function<void()> onClick);

            void onClick();
            bool isMouseOver(int mouseX, int mouseY) const;

        private:
            Rectangle _bounds;
            bool _isSelected;
            std::function<void()> _onClick;
        };

    }
}
