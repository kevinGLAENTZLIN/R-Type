/*
** EPITECH PROJECT, 2024
** R-Type - Core : Core
** File description:
** Core class is the main class of the ECS.
** It will coordinate the behaviors of the managers.
*/

#pragma once

#include "../Component/ComponentManager/ComponentManager.hpp"
#include "../System/SystemManager/SystemManager.hpp"
#include "../Entity/EntityManager/EntityManager.hh"
#include <cstddef>
#include <iostream>
#include <memory>

namespace ECS {

    class Core {

        public:
            Core();
            ~Core() = default;
            std::size_t CreateEntity();
            void DestroyEntity(std::size_t entity);

            template<typename T>
            void RegisterComponent() {
                _componentManager->registerComponent<T>();
            }

            template<typename T>
            T& GetComponent(std::size_t entity) {
                return _componentManager->getComponents<T>();
            }

            template<typename T>
            std::shared_ptr<T> RegisterSystem() {
                return _systemManager->RegisterSystem<T>();
            }

            template<typename T>
            void SetSystemSignature(Signature signature) {
                _systemManager->SetSignature<T>(signature);
            }

        protected:

        private:
            std::shared_ptr<ComponentManager::ComponentManager> _componentManager;
            std::shared_ptr<EntityManager> _entityManager;
            std::shared_ptr<SystemManager> _systemManager;
    };
};
