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

        class Render3D {
        public:
            /**
            * @brief Constructor of render3D component.
            *
            * @tparam path : path to the 3D model.
            * @return void.
            */
            Render3D(const std::string &path);

            /**
            * @brief Constructor of render3D component.
            *
            * @tparam other : another render3D component.
            * @return void.
            */
            Render3D(const Render3D& other);

            /**
            * @brief Operator= of render3D component.
            *
            * @tparam other : another render3D component.
            * @return Render3D&.
            */
            Render3D& operator=(const Render3D& other);

            /**
            * @brief Destructor of render3D component.
            *
            * @return void.
            */
            ~Render3D() = default;

            /**
            * @brief Render the 3D model.
            *
            * @tparam model : the 3D model.
            * @tparam position : the position of the model.
            * @tparam rotation : the rotation of the model.
            * @tparam scale : the scale of the model.
            * @return void.
            */
            void render(raylib::Model &model, raylib::Vector3 position, raylib::Vector3 rotation, raylib::Vector3 scale);

            /**
            * @brief Get the color of the model.
            *
            * @return raylib::Color.
            */
            const raylib::Color &getColor() const;

            /**
            * @brief Set the color of the model.
            *
            * @tparam color : the color of the model.
            * @return void.
            */
            void setColor(const raylib::Color &color);

            /**
            * @brief Get the path of the model.
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
