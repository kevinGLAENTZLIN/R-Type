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

        enemiesTypeEnum_t type = ecsUtils::getTypeFromString(enemyData["type"].asString());
        int difficulty = enemyData["difficulty"].asInt();
        float positionX = enemyData["position"]["x"].asFloat();
        float positionY = enemyData["position"]["y"].asFloat();
        int health = enemyData["health"].asInt();
        std::string model = enemyData["model"].asString();
        int timeMinute = enemyData["time minute"].asInt();
        int timeSecond = enemyData["time second"].asInt();

        Rtype::EnemySpawnData enemy;
        enemy.setType(type);
        enemy.setDifficulty(difficulty);
        enemy.setPositionX(positionX);
        enemy.setPositionY(positionY);
        enemy.setHealth(health);
        enemy.setModel(model);
        enemy.setSpawnTime({timeMinute, timeSecond});

        _enemySpawnData.push_back(enemy);
    }
}

std::vector<Rtype::EnemySpawnData> Rtype::LoadData::GetEnemySpawnData() const
{
    return _enemySpawnData;
}
