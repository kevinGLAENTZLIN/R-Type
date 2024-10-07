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
{}

void ECS::RessourcePool::UnloadAll()
{
    for (auto &model : _models) {
        if (model.second.meshes != nullptr) {
            model.second.Unload();
            std::cout << "Unloaded model: " << model.first << std::endl;
        } else {
            std::cout << "Model: " << model.first << " already unloaded" << std::endl;
        }
    }
    for (auto &texture : _textures) {
        if (texture.second.id != 0) {
            texture.second.Unload();
            std::cout << "Unloaded texture: " << texture.first << std::endl;
        } else {
            std::cout << "Texture: " << texture.first << " already unloaded" << std::endl;
        }
    }
}

raylib::Model& ECS::RessourcePool::getModel(std::string modelPath)
{
    return _models[modelPath];
}

raylib::Texture& ECS::RessourcePool::getTexture(std::string texturePath)
{
    return _textures[texturePath];
}

void ECS::RessourcePool::addTexture(const std::string &TexturePath)
{
    raylib::Image image(TexturePath);
    raylib::Texture texture(image);

    _textures.emplace(TexturePath, std::move(texture));
    _texturesImages.emplace(TexturePath, std::move(image));
}

void ECS::RessourcePool::addModel(const std::string &modelPath)
{
    std::string pngTexturePath = modelPath.substr(0, modelPath.find_last_of('.')) + ".png";
    raylib::Texture texture(pngTexturePath.c_str());
    raylib::Model defaultModel(modelPath);

    defaultModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    _texturesModels.emplace(pngTexturePath, std::move(texture));
    _models.emplace(modelPath, std::move(defaultModel));
}
