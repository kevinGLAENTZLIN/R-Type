/*
** EPITECH PROJECT, 2024
** R-Type - ComponentManager : ComponentTypeRegistry
** File description:
** The Component Registry assigns a unique index to each component type when the static function getTypeId<T> is called.
*/
#pragma once

#include <iostream>

namespace ECS {
    namespace ComponentManager {
    
        class ComponentTypeRegistry {
        public:
            template <typename Component>
            static std::size_t getTypeId() {
                static std::size_t index = nextTypeIndex++;
                return index;
            }
        
        private:
            static std::size_t nextTypeIndex;
        };
    }
}
