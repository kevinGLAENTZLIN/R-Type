#pragma once
#include <iostream>
#include <string>
#include "raylib-cpp.hpp"

namespace ECS {
    namespace Components {

        class Render {
        public:
            Render(const std::string path, float rotation = 0.0f, float scale = 1.0f);
            Render(const Render& other);
            Render& operator=(const Render& other);
            ~Render() = default;

            void render(raylib::Model &model, raylib::Vector3 position);
            void renderBackground(raylib::Texture2D texture, raylib::Vector3 position)
            const std::string getPath() const;
        private:
            raylib::Model _model;
            raylib::Texture _texture;
            raylib::Color _color;
            std::string _path;
            float _rotation;
            float _scale;
        };
    }
}
