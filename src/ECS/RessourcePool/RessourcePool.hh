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
#include <algorithm>
#include <filesystem>
#include <queue>
#include <mutex>

namespace ECS {
    class RessourcePool {
    public:
        RessourcePool();
        ~RessourcePool() = default;

        raylib::Model &getModel(std::string modelPath);
        raylib::Texture &getTexture(std::string texturePath);

        void queueModelLoad(const std::string& modelPath);
        void requestLoadTexture(const std::string &texturePath);
        void processLoadQueue();
        void addModel(const std::string &modelPath);
        void addTexture(const std::string &TexturePath);
        void UnloadAll();
    private:

        std::map<const std::string, raylib::Model> _models;
        std::map<const std::string, raylib::Texture> _texturesModels;
        std::map<const std::string, raylib::Texture> _textures;
        std::queue<std::string> _pendingLoads;
        std::queue<std::string> _pendingTextureLoads;
        std::mutex _mutex;
    };
}
