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

            void entityDestroyed(std::size_t entityID) {
                // Parcourt chaque SparseArray (chaque type de composant)
                for (auto& [typeIndex, sparseArrayAny] : _sparseArrays) {
                    // On essaie de caster vers un SparseArray de std::optional
                    try {
                        auto& sparseArray = std::any_cast<SparseArray<std::optional<std::any>>&>(sparseArrayAny);

                        // Si l'ID d'entité est valide dans ce tableau, on le détruit
                        if (entityID < sparseArray.size()) {
                            sparseArray[entityID] = std::nullopt; // Composant supprimé
                        }
                    } catch (const std::bad_any_cast& e) {
                        // On ignore si le cast échoue (ce n'est pas le bon type de SparseArray)
                        std::cerr << "Failed to cast SparseArray: " << e.what() << std::endl;
                    }
                }
            };

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
