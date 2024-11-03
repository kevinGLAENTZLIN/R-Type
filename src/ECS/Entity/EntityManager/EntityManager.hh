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
#include <stack>
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
            /**
            * @brief Construct a new Entity Manager object
            *
            */
            EntityManager();

            /**
            * @brief Destroy the Entity Manager object
            *
            */
            ~EntityManager() = default;

            /**
            * @brief Create a Entity object
            *
            * @return std::size_t
            */
            std::size_t createEntity();

            /**
            * @brief Destroy a Entity object
            *
            * @param std::size_t entity
            */
            void destroyEntity(std::size_t entity);

            /**
            * @brief Set the Signature object
            *
            * @param std::size_t entity
            * @param Signature signature
            */
            void setSignature(std::size_t entity, Signature signature);

            /**
            * @brief Get the Signature object
            *
            * @param std::size_t entity
            * @return Signature
            */
            Signature getSignature(std::size_t entity) const;

            /**
            * @brief Get the Entities object
            *
            * @return std::vector<std::size_t>
            */
            std::vector<std::size_t> getEntities() const;

        private:
            std::stack<std::size_t> _mAvailableEntities;
            std::array<Signature, MAX_ENTITIES> _mSignatures;
            std::size_t _mLivingEntityCount;
        };
    }
}
