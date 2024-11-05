/*
** EPITECH PROJECT, 2024
** Utils.hh
** File description:
** Utils class
*/

#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <filesystem>
#include "raylib-cpp.hpp"
#include "../Component/Position/Position.hpp"
#include "../Component/Hitbox/Hitbox.hh"

namespace ECS {

    class Utils {
    public:

        /**
        * @brief Enum of the different file types
        */
        enum FileType {
            Unknown = 0,
            Texture,
            Model,
            Audio,
            Font,
            Shader,
            Data
        };

        /**
        * @brief Check if two entities are colliding
        * @param posA Position of the first entity
        * @param hitboxA Hitbox of the first entity
        * @param posB Position of the second entity
        * @param hitboxB Hitbox of the second entity
        * @return true if the entities are colliding, false otherwise
        */
        static bool checkCollision(
            const ECS::Components::Position &posA,
            const ECS::Components::Hitbox &hitboxA,
            const ECS::Components::Position &posB,
            const ECS::Components::Hitbox &hitboxB);

        /**
        * @brief get the file type of a file
        * @param path path to the file
        * @return the file type
        */
        static FileType getRaylibFileType(const std::string& path);

        /**
        * @brief get the model size of a model
        * @param model the model
        * @return the model size
        */
        static std::pair<float, float> getModelSize(const raylib::Model &model);
    };
}
