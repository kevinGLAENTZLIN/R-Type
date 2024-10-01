/*
** EPITECH PROJECT, 2024
** R-Type - Game : Game
** File description:
** Ressource class is the class to load one time each model and
** re use them after withtout reloading them.
*/

#include "raylib-cpp.hpp"
#include <map>
#include <iostream>
#include <string>

namespace ECS {
    class RessourcePool {
        public:
            RessourcePool();
            ~RessourcePool();

            void UnloadAll();
            raylib::Model &getModel(std::string modelPath);

        private:
            std::map<std::string, raylib::Model> _models;
    };
}
