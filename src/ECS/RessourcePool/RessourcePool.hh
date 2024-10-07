/*
** EPITECH PROJECT, 2024
** R-Type - Game : Game
** File description:
** Ressource class is the class to load one time each model and
** re use them after withtout reloading them.
*/
#pragma once
#include "raylib-cpp.hpp"
#include <map>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace ECS {
    class RessourcePool {
        public:
            RessourcePool();
            ~RessourcePool();

            raylib::Model &getModel(std::string modelPath);
            raylib::Texture &getTexture(std::string texturePath);

            void addModel(const std::string &modelPath);
            void addTexture(const std::string &TexturePath);
            void UnloadAll();
        private:

            std::map<const std::string, raylib::Model> _models;
            std::map<const std::string, raylib::Texture> _texturesModels;
            std::map<const std::string, raylib::Texture> _textures;
            std::map<const std::string, raylib::Image> _texturesImages;
    };
}
