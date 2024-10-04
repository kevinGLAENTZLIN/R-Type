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

            void UnloadAll();
            raylib::Model &getModel(std::string modelPath);

            void addModel(const std::string &modelPath);
        private:

            std::map<const std::string, raylib::Model> _models;
            std::vector<std::unique_ptr<raylib::Model>> _pitier;
            raylib::Model _defaultModel;
    };
}
