/*
** EPITECH PROJECT, 2024
** R-Type - ComponentManager : ComponentManager
** File description:
** ComponentManager handles the management of component SparseArrays.
*/
#pragma once

#include "SparseArray.hpp"
#include "ComponentTypeRegistry.hpp"
#include <cstddef>
#include <unordered_map>
#include <typeindex>
#include <any>

using Signature = std::bitset<32>;

namespace ECS{
    namespace ComponentManager {

        /**
         * @brief This class handles the creation and indexing of the differents SparseArrays.
         *
         * Using its registerComponent with a given type,  one can create a SparseArray and index it to the type.
         */
        class ComponentManager {
        public:

            /**
             * @brief Create and add to the map a SparseArray of the given type
             *
             * Construct a SparseArray of the given Component type if it hasn't been mapped already.
             * If an already mapped type is given, an exception is raised.
             * Once the SparseArray is created, this function maps it to the given type ID using getTypeId().
             *
             * @tparam Component Component type of the sparseArray to be created and added to the map.
             * @return Reference to the created SparseArray in the map.
             */
            template <class Component>
            SparseArray<Component> &registerComponent() {
                if (_sparseArrays.count(std::type_index(typeid(Component))) != 0) {
                    std::cerr << "A SparseArray of this type already exists." << std::endl;
                    throw std::runtime_error("SparseArray for this component type already registered.");
                }
                _sparseArrays[std::type_index(typeid(Component))] = SparseArray<Component>();
                return std::any_cast<SparseArray<Component>&>(_sparseArrays[std::type_index(typeid(Component))]);
            };

            /**
             * @brief Gets the sparseArray corresponding to the given type.
             *
             * Gets the SparseArray corresponding to the component type given in the parameters.
             *
             * @tparam Component Component type of the sparseArray to get.
             * @return The SparseArray corresponding to the given Component type.
             */
            template <class Component>
            SparseArray<Component> &getComponents(){
                return std::any_cast<SparseArray<Component>&>(_sparseArrays.at(std::type_index(typeid(Component))));
            };

            /**
             * @brief Gets a const reference to the sparseArray corresponding to the given type.
             *
             * Gets a const reference to the SparseArray corresponding to the component type given in the parameters.
             *
             * @tparam Component Component type of the sparseArray to get.
             * @return The const reference to the SparseArray corresponding to the given Component type.
             */
            template <class Component>
            SparseArray<Component> const &getComponents() const{
                return std::any_cast<const SparseArray<Component>&>(_sparseArrays.at(std::type_index(typeid(Component))));
            };

            void entityDestroyed(std::size_t entity, Signature signature) {
                for (std::size_t i = 0; i < signature.size(); i++) {
                    if (signature[i]) {
                        std::type_index componentType = ECS::CTypeRegistry::getTypeFromId(i);
                        auto it = _sparseArrays.find(componentType);
                        if (it != _sparseArrays.end()) {
                            try {
                                auto& sparseArray = std::any_cast<SparseArray<std::optional<std::any>&>>(it->second);
                                if (entity < sparseArray.size()) {
                                    sparseArray[entity] = std::nullopt;
                                }
                            } catch (const std::bad_any_cast& e) {
                                std::cerr << "Bad any_cast for component type: " << componentType.name() << ", error: " << e.what() << std::endl;
                            }
                        }
                    }
                }
            }

        private:

            /**
             * @brief Attribute that hold the different Components SparseArray mapped to their type
             *
             * _sparseArrays is an unordered map containing each type_index as a key and the corresponding SparseArray as data.
             * The SparseArray are kept in a std::any container and it is the ComponentManager's responsability to cast it to the right type.
             */
            std::unordered_map<std::type_index, std::any> _sparseArrays;
        };
    }
}
