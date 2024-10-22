/*
** EPITECH PROJECT, 2024
** R-Type - ECS: enemiesTypeEnum.hpp
** File description:
** enemy type enum
*/
#pragma once

#include <iostream>

typedef enum enemiesTypeEnum_e {
    UNKNOWN,
    POWARMOR,
    PATAPATA,
    BUG,
    BINK,
    SCANT
} enemiesTypeEnum_t;

class enemiesTypeUtils {
public:
    static enemiesTypeEnum_t getTypeFromString(const std::string & type) {
        if (type == "POWARMOR")
            return POWARMOR;
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
};
