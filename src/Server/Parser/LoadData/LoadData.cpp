/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Loaddata
*/

#include "LoadData.hh"

Rtype::LoadData::LoadData()
{}

void Rtype::LoadData::LoadDataFromFile(const std::string &path)
{
    Json::Reader reader;
    Json::Value root;
    std::string newPath = "src/Server/Parser/Stage/";

    newPath += path;
    std::ifstream file(newPath);
    file.open(newPath);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << newPath << std::endl;
        return;
    }

    if (!reader.parse(file, root)) {
        std::cerr << "Error: Failed to parse file " << newPath << std::endl;
        return;
    }

    for (const auto& enemyKey : root.getMemberNames()) {
        const Json::Value& enemyData = root[enemyKey];

        std::string type = enemyData["type"].asString();
        std::cout << "type: " << type << std::endl;
        enemiesTypeEnum_t enemyType = convertStringToEnumType(type);
        float positionX = enemyData["position"]["x"].asFloat();
        float positionY = enemyData["position"]["y"].asFloat();
        std::string model = enemyData["model"].asString();
        int timeMinute = enemyData["time minute"].asInt();
        int timeSecond = enemyData["time second"].asInt();

        Rtype::EnemySpawnData enemy;
        enemy.setType(enemyType);
        enemy.setPositionX(positionX);
        enemy.setPositionY(positionY);
        enemy.setModel(model);
        enemy.setSpawnTime({timeMinute, timeSecond});

        _enemySpawnData.push_back(enemy);
    }
}

enemiesTypeEnum_t Rtype::LoadData::convertStringToEnumType(const std::string &text)
{
    if (text == "PATAPATA")
        return PATAPATA;
    if (text == "BINK")
        return BINK;
    return PATAPATA;
}

void Rtype::LoadData::clearEnemySpawnData()
{
    _enemySpawnData.clear();
}

std::vector<Rtype::EnemySpawnData> Rtype::LoadData::GetEnemySpawnData() const
{
    return _enemySpawnData;
}
