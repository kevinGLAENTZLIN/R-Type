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

class SystemManager {
    public:
        template<typename T>

        std::shared_ptr<T> RegisterSystem() {
            std::string typeName = typeid(T).name();

            if (_mSystems.find(typeName) == _mSystems.end())
                return nullptr;
            auto system = std::make_shared<T>();
            _mSystems[typeName] = system;
            return system;
        }

        template<typename T>

        void SetSignature(Signature signature) {
            std::string typeName = typeid(T).name();

            if (_mSystems.find(typeName) == _mSystems.end())
                return;
            _mSignatures[typeName] = signature;
        }

        void EntityDestroyed(std::size_t entity) {
            for (auto const& pair : _mSystems) {
                auto const& system = pair.second;
                system->_entities.erase(entity);
            }
        }

        void EntitySignatureChanged(std::size_t entity, Signature entitySignature) {
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

    private:
        std::unordered_map<std::string, Signature> _mSignatures;
        std::unordered_map<std::string, std::shared_ptr<System> > _mSystems;

};
