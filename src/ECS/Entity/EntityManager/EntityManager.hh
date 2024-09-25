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
#include <cstdint>

#define MAX_ENTITIES 10000

using ComponentType = std::uint8_t;
const ComponentType MAX_COMPONENTS = 32;
using Signature = std::bitset<MAX_COMPONENTS>;

namespace ECS {
    namespace EntityManager {
        class EntityManager {
        public:
            EntityManager();
            ~EntityManager() = default;

            std::size_t createEntity();
            void destroyEntity(std::size_t entity);
            void setSignature(std::size_t entity, Signature signature);
            Signature getSignature(std::size_t entity) const;

        private:
            std::queue<std::size_t> _mAvailableEntities;
            std::array<Signature, MAX_ENTITIES> _mSignatures;
            std::size_t _mLivingEntityCount;
        };
    }
}
