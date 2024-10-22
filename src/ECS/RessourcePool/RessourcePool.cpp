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

raylib::Model& ECS::RessourcePool::getModel(const std::string &modelPath)
{
    return _models.at(modelPath);
}

raylib::Texture& ECS::RessourcePool::getTexture(const std::string &texturePath)
{
    return _textures.at(texturePath);
}

raylib::Shader& ECS::RessourcePool::getShader(const std::string &shaderPath)
{
    return _shaders.at(shaderPath);
}

void ECS::RessourcePool::addShader(const std::string &shaderPath)
{
    std::string pathRessourcesVs = "./resources/shaders/" + shaderPath + ".vs";
    std::string pathRessourcesFs = "./resources/shaders/" + shaderPath + ".fs";
    raylib::Shader defaultShader(pathRessourcesVs, pathRessourcesFs);

    defaultShader.locs[SHADER_LOC_VECTOR_VIEW] = defaultShader.GetLocation("viewPos");
    int ambientLoc = defaultShader.GetLocation("ambient");
    std::array<float, 4> ambientValues = {1.0f, 1.0f, 1.0f, 1.0f};
    defaultShader.SetValue(ambientLoc, ambientValues.data(), SHADER_UNIFORM_VEC4);
    _shaders.emplace(shaderPath, std::move(defaultShader));
}

void ECS::RessourcePool::addTexture(const std::string &TexturePath)
{
    std::string pathRessources = "./resources/" + TexturePath + "/" + TexturePath + ".png";
    raylib::Texture defaultTexture(pathRessources);

    _textures.emplace(TexturePath, std::move(defaultTexture));
}

void ECS::RessourcePool::addModel(const std::string &modelPath)
{
    std::string pathRessources = "./resources/" + modelPath + "/" + modelPath + ".obj";
    std::string pngTexturePath = pathRessources.substr(0, pathRessources.find_last_of('.')) + ".png";
    raylib::Model defaultModel(pathRessources);

    if (std::filesystem::exists(pngTexturePath)) {
        raylib::Texture texture(pngTexturePath.c_str());
        defaultModel.materials[0].shader = _shaders.at("lighting");
        defaultModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
        _texturesModels.emplace(pngTexturePath, std::move(texture));
    }

    _models.emplace(modelPath, std::move(defaultModel));
}
