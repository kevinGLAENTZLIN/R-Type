/*
** EPITECH PROJECT, 2024
** R-Type - Components : Render
** File description:
** Render Component
*/

#pragma once
#include <iostream>
#include <raylib.h>

namespace Components {

    class Render {
        public:
            Render(std::string textureFilePath, float rotation = 0.0f, float scale = 1.0f);
            ~Render() = default;

            const Texture2D& getTexture() const;
            float getRotation() const;
            float getScale() const;

            void setRotation(float rotation);
            void setScale(float scale);

        private:
            Texture2D _texture;
            float _rotation;
            float _scale;
    };
}
