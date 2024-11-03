#pragma once
#include <iostream>
#include <string>
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

        class Render2D{
        public:
            /**
            * @brief Constructor of render2D component.
            *
            * @tparam path : path to the 2D model.
            * @return void.
            */
            Render2D(const std::string path);

            /**
            * @brief Copy Constructor of render2D component.
            *
            * @tparam other : the render2D component to copy.
            * @return void.
            */
            Render2D(const Render2D& other);

            /**
            * @brief operator= of render2D component.
            *
            * @tparam other : the render2D component to copy.
            * @return Render2D&.
            */
            Render2D& operator=(const Render2D& other);

            /**
            * @brief Destructor of render2D component.
            *
            * @return void.
            */
            ~Render2D() = default;

            /**
            * @brief render the 2D model.
            *
            * @tparam texture : the texture of the 2D model.
            * @tparam position : the position of the 2D model.
            * @tparam rotation : the rotation of the 2D model.
            * @tparam scale : the scale of the 2D model.
            * @return void.
            */
            void render(raylib::Texture &texture, raylib::Vector3 position, raylib::Vector3 rotation, raylib::Vector3 scale);

            /**
            * @brief get the color of the 2D model.
            *
            * @return raylib::Color.
            */
            const raylib::Color &getColor() const;

            /**
            * @brief set the color of the 2D model.
            *
            * @tparam color : the color to set.
            * @return void.
            */
            void setColor(const raylib::Color &color);

            /**
            * @brief get the path of the 2D model.
            *
            * @return std::string.
            */
            const std::string getPath() const;

        private:
            raylib::Color _color;
            std::string _path;
        };
    }
}
