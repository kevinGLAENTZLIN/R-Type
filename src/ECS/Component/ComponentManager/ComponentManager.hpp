/*
** EPITECH PROJECT, 2024
** R-Type - ComponentManager : ComponentManager
** File description:
** ComponentManager handles the management of component SparseArrays.
*/
#pragma once

#include "SparseArray.hpp"
#include <unordered_map>
#include <typeindex>
#include <any>

namespace ComponentManager {

    class ComponentManager {
    public:        
        template <class Component>
        SparseArray<Component> &registerComponent() {
            if (_sparseArrays.count(std::type_index(typeid(Component))) != 0) {
                std::cerr << "A SparseArray of this type already exists." << std::endl;
                throw std::runtime_error("SparseArray for this component type already registered.");
            }
            _sparseArrays[std::type_index(typeid(Component))] = SparseArray<Component>();
            return std::any_cast<SparseArray<Component>&>(_sparseArrays[std::type_index(typeid(Component))]);
        };

        template <class Component>
        SparseArray<Component> &getComponents(){
            return std::any_cast<SparseArray<Component>&>(_sparseArrays.at(std::type_index(typeid(Component))));
        };

        template <class Component>
        SparseArray<Component> const &getComponents() const{
            return std::any_cast<const SparseArray<Component>&>(_sparseArrays.at(std::type_index(typeid(Component))));
        };

    private:
        std::unordered_map<std::type_index, std::any> _sparseArrays;
    };
}
