/*
** EPITECH PROJECT, 2024
** R-Type - ECS: enemiesTypeEnum.hpp
** File description:
** enemy type enum
*/
#pragma once

#include <iostream>
#include "../ECS/Component/Position/Position.hpp"
#include <cmath>
#include <optional>
#include <utility>
#include <map>
#include <vector>

typedef enum enemiesTypeEnum_e {
    UNKNOWN,
    MINIKIT,
    PATAPATA,
    BUG,
    BINK,
    SCANT
} enemiesTypeEnum_t;

class ecsUtils {
public:
    static enemiesTypeEnum_t getTypeFromString(const std::string & type) {
        if (type == "MINIKIT")
            return MINIKIT;
        if (type == "PATAPATA")
            return PATAPATA;
        if (type == "BUG")
            return BUG;
        if (type == "BINK")
            return BINK;
        if (type == "SCANT")
            return SCANT;        
        return UNKNOWN;
    };

    static float getDistance(const std::pair<float, float> & pos1,
                             const std::pair<float, float> & pos2) {
        float X1 = pos1.first;
        float Y1 = pos1.second;
        float X2 = pos2.first;
        float Y2 = pos2.second;

        return std::sqrt((X2 - X1) * (X2 - X1) +
                         (Y2 - Y1) * (Y2 - Y1));
    }

    static std::size_t getClosestPlayer(
        const std::pair<float, float> & currentPos,
        std::vector<std::pair<float, float>> posToCompare)
    {
        float dist = 1000;
        float tempDist = 0;
        std::size_t closestId = 0;

        for (size_t i = 0; i < posToCompare.size(); i++) {
            tempDist = ecsUtils::getDistance(currentPos,
                                             posToCompare[i]);
            if (dist > tempDist) {
                dist = tempDist;
                closestId = i;
            }
        }
        return closestId;
    }
};
