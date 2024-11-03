/*
** EPITECH PROJECT, 2024
** R-Type - Components : Input
** File description:
** Input Component
*/
#pragma once

#include <iostream>
#include <vector>

namespace ECS {
    namespace Components {

        class Input {
        public:
            /**
            * @brief Constructor to Input component.
            *
            * Constructor for the input component, which  represent the
            * input of the entities in the video game,
            *
            * @tparam void.
            * @return void.
            */
            Input();

            /**
            * @brief Destructor to Input component.
            *
            * Destructor for the input component.
            *
            * @tparam void.
            * @return void.
            */
            ~Input() = default;

            /**
            * @brief Set the inputs of the entity.
            *
            * Set the inputs of the entity.
            *
            * @tparam std::vector<std::size_t> inputs.
            * @return void.
            */
            void setInputs(const std::vector<std::size_t> & inputs);

            /**
            * @brief Get the inputs of the entity.
            *
            * Get the inputs of the entity.
            *
            * @tparam void.
            * @return std::vector<std::size_t>.
            */
            std::vector<std::size_t> getInputs() const;

            /**
            * @brief Check if the input contains the input to search.
            *
            * Check if the input contains the input to search.
            *
            * @tparam std::size_t toSearch.
            * @return bool.
            */
            bool contains(std::size_t toSearch);

        private:
            std::vector<std::size_t> _lastInputs;
        };
    }
}
