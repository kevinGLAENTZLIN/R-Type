/*
** EPITECH PROJECT, 2024
** SystemManager.hpp
** File description:
** SystemManager class
*/
#pragma once

#include <cstddef>
#include <memory>
#include <iostream>
#include <unordered_map>
#include <typeinfo>
#include <bitset>
#include <unordered_set>

#include "../System/System.hpp"

using Signature = std::bitset<32>;

namespace ECS {
    namespace SystemManager {

        class SystemManager {
        public:

            template<typename T>
            std::shared_ptr<T> registerSystem() {
                std::string typeName = typeid(T).name();
                if (_mSystems.find(typeName) != _mSystems.end())
                    return nullptr;
                auto system = std::make_shared<T>();
                _mSystems[typeName] = system;
                return system;
            }

            template<typename T>
            void setSignature(Signature signature) {
                std::string typeName = typeid(T).name();
                if (_mSystems.find(typeName) == _mSystems.end())
                    return;
                _mSignatures[typeName] = signature;
            }

            void entityDestroyed(std::size_t entity) {
                for (auto const& pair : _mSystems) {
                    auto const& system = pair.second;
                    system->_entities.erase(entity);
                }
            }

            void entitySignatureChanged(std::size_t entity, Signature entitySignature) {
                for (auto const& pair : _mSystems) {
                    auto const& type = pair.first;
                    auto const& system = pair.second;
                    auto const& systemSignature = _mSignatures[type];

                    if ((entitySignature & systemSignature) == systemSignature) {
                        system->_entities.insert(entity);
                    } else {
                        system->_entities.erase(entity);
                    }
                }
            }

            template<typename T>
            Signature getSignature() {
                std::string typeName = typeid(T).name();
                if (_mSignatures.find(typeName) != _mSignatures.end()) {
                    return _mSignatures[typeName];
                }
                return Signature();
            }

            template<typename T>
            std::shared_ptr<T> getSystem() {
                std::string typeName = typeid(T).name();
                if (_mSystems.find(typeName) != _mSystems.end()) {
                    return std::static_pointer_cast<T>(_mSystems[typeName]);
                }
                return nullptr;
            }

        private:
            std::unordered_map<std::string, Signature> _mSignatures;
            std::unordered_map<std::string, std::shared_ptr<Systems::System> > _mSystems;
        };
    }
}
