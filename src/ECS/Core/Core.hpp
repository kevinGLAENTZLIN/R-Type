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
#include "../Component/ComponentManager/ComponentTypeRegistry.hpp"
#include <cstddef>
#include <iostream>
#include <memory>

namespace ECS {
    namespace Core {

        class Core {

        public:
            Core();
            ~Core() = default;
            std::size_t createEntity();
            void destroyEntity(std::size_t entity);
            Signature getSignature(std::size_t entity) const;

            template<typename T>
            void registerComponent() {
                _componentManager->registerComponent<T>();
            }

            template<typename T>
            T& getComponent(std::size_t entity) {
                return _componentManager->getComponents<T>()[entity].value();
            }
        
            template<typename T>
            ComponentManager::SparseArray<T>& getComponents() {
                return _componentManager->getComponents<T>();
            }

            template<typename T>
            std::shared_ptr<T> registerSystem() {
                return _systemManager->registerSystem<T>();
            }

            template<typename T>
            void addComponent(std::size_t entity, T component) {
                auto signature = _entityManager->getSignature(entity);

                signature.set(
                    ComponentManager::ComponentTypeRegistry::getTypeId<T>(), true);
                _entityManager->setSignature(entity, signature);
                _systemManager->entitySignatureChanged(entity, signature);
                _componentManager->getComponents<T>().insertAt(entity, component);
            }

            template<typename T>
            void setSystemSignature(Signature signature) {
                _systemManager->setSignature<T>(signature);
            }

            void setEntitySignature(std::size_t entity, Signature signature) {
                _entityManager->setSignature(entity, signature);
                _systemManager->entitySignatureChanged(entity, signature);
            }

        protected:

        private:
            std::shared_ptr<ComponentManager::ComponentManager> _componentManager;
            std::shared_ptr<EntityManager::EntityManager> _entityManager;
            std::shared_ptr<SystemManager::SystemManager> _systemManager;
        };
    }
}
