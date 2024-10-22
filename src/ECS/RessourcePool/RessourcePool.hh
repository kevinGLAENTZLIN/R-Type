/*
** EPITECH PROJECT, 2024
** R-Type - Game : Game
** File description:
** Ressource class is the class to load one time each model and
** re use them after withtout reloading them.
*/
#pragma once
#include <map>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include <filesystem>
#include "raylib-cpp.hpp"

namespace ECS {
    class RessourcePool {
    public:
        RessourcePool();
        ~RessourcePool() = default;

        raylib::Model &getModel(const std::string &modelPath);
        raylib::Texture &getTexture(const std::string &texturePath);
        raylib::Shader &getShader(const std::string &shaderPath);

        void addModel(const std::string &modelPath);
        void addTexture(const std::string &TexturePath);
        void addShader(const std::string &shaderPath);
        void UnloadAll();
    private:
        std::map<const std::string, raylib::Model> _models;
        std::map<const std::string, raylib::Texture> _texturesModels;
        std::map<const std::string, raylib::Texture> _textures;
        std::map<const std::string, raylib::Shader> _shaders;
    };
}
