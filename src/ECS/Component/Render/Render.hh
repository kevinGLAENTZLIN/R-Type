/*
** EPITECH PROJECT, 2024
** R-Type - Components : Render
** File description:
** Render Component
*/

#pragma once

#include <raylib.h>

namespace Components {

    class Render {
        public:
            Render(std::string textureFilePath, float rotation = 0.0f, float scale = 1.0f)
                : _texture(LoadTexture(textureFilePath)), _rotation(rotation), _scale(scale) {}

            ~Render() {
                UnloadTexture(_texture);
            }

            Texture2D& getTexture() {
                return _texture;
            }

            const Texture2D& getTexture() const {
                return _texture;
            }

            float getRotation() const {
                return _rotation;
            }

            void setRotation(float rotation) {
                _rotation = rotation;
            }

            float getScale() const {
                return _scale;
            }

            void setScale(float scale) {
                _scale = scale;
            }

        private:
            Texture2D _texture;
            float _rotation;
            float _scale;
    };
}
