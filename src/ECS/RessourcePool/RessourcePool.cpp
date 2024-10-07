/*
** EPITECH PROJECT, 2024
** R-Type - Game : Game
** File description:
** Ressource class is the class to load one time each model and
** re use them after withtout reloading them.
*/

#include "RessourcePool.hh"

ECS::RessourcePool::RessourcePool()
{
}

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
        //_models[modelPath] = LoadModel(modelPath.c_str());
        std::cout << "Loaded model: " << modelPath << std::endl;
    }
    return _models[modelPath];
}

raylib::Texture& ECS::RessourcePool::getTexture(std::string texturePath) {
    if (_textures.find(texturePath) == _textures.end()) {
        _textures[texturePath] = LoadTexture(texturePath.c_str());
        std::cout << "Loaded texture: " << texturePath << std::endl;
    }
    return _textures[texturePath];
}

void ECS::RessourcePool::addTexture(const std::string &TexturePath)
{
    raylib::Texture texture = LoadTexture(TexturePath.c_str());
    std::cout << "Loaded texture: " << TexturePath << std::endl;
    _textures.emplace(TexturePath, std::move(texture));
}

void ECS::RessourcePool::addModel(const std::string &modelPath) {
    std::string pngTexturePath = modelPath.substr(0, modelPath.find_last_of('.')) + ".png";
    raylib::Texture texture = LoadTexture(pngTexturePath.c_str());
    std::cout << "Loaded texture: " << pngTexturePath << std::endl;

    raylib::Model defaultModel(modelPath);
    //defaultModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    _models.emplace(modelPath,std::move(defaultModel));
}
