/*
** EPITECH PROJECT, 2024
** R-Type - Game : Game
** File description:
** Ressource class is the class to load one time each model and
** re use them after withtout reloading them.
*/

#include "RessourcePool.hh"

ECS::RessourcePool::RessourcePool()
{}

ECS::RessourcePool::~RessourcePool()
{
    UnloadAll();
}

void ECS::RessourcePool::UnloadAll()
{
    for (auto &model : _models) {
        UnloadModel(model.second);
        std::cout << "Unloaded model: " << model.first << std::endl;
    }
    _models.clear();
}

raylib::Model& ECS::RessourcePool::getModel(std::string modelPath) {
    if (_models.find(modelPath) == _models.end()) {
        _models[modelPath] = LoadModel(modelPath.c_str());
        std::cout << "Loaded model: " << modelPath << std::endl;
    }
    return _models[modelPath];
}
