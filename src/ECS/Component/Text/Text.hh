/*
** EPITECH PROJECT, 2024
** R-Type - Components : Text
** File description:
** Text Component
*/
#pragma once

#include <iostream>

namespace ECS {
    namespace Components {

        class Text {
        public:
            Text(std::string text);
            ~Text() = default;
            std::string getText() const;
            void setText(std::string text);

        protected:

        private:
            std::string _text;
        };
    }
}
