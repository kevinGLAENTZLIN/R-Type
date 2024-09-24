/*
** EPITECH PROJECT, 2024
** EntityManeger.hh
** File description:
** EntityManeger class
*/

#pragma once
#include <cstddef>
#include <vector>
#include <iostream>
#include <queue>
#include <array>
#include <bitset>
#define MAX_ENTITIES 10000
#include <cstdint>


using ComponentType = std::uint8_t;
const ComponentType MAX_COMPONENTS = 32;
using Signature = std::bitset<MAX_COMPONENTS>;

class EntityManager {
    public:
        EntityManager();
        ~EntityManager() = default;

        std::size_t CreateEntity();
        void DestroyEntity(std::size_t entity);
        void SetSignature(std::size_t entity, Signature signature);
        Signature GetSignature(std::size_t entity) const;

        private:
            std::queue<std::size_t> mAvailableEntities;
            std::array<Signature, MAX_ENTITIES> mSignatures;
            std::size_t mLivingEntityCount;
};
