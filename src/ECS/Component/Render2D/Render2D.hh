#pragma once
#include <iostream>
#include <string>
#include "raylib-cpp.hpp"

namespace ECS {
    namespace Components {

        class Render2D{
        public:
            Render2D(const std::string path);
            Render2D(const Render2D& other);
            Render2D& operator=(const Render2D& other);
            ~Render2D() = default;

            void render(raylib::Texture &texture, raylib::Vector3 position, raylib::Vector3 rotation, raylib::Vector3 scale);
            const raylib::Color &getColor() const;
            void setColor(const raylib::Color &color);
            const std::string getPath() const;

        private:
            raylib::Color _color;
            std::string _path;
        };
    }
}
