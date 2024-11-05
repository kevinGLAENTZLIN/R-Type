/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Factory
*/

#pragma once
#if defined(_WIN32)
	#define NOGDI
	#define NOUSER
#endif

#if defined(_WIN32)
	#undef near
	#undef far
#endif

#include "../ICommand.hh"
#include "../ACommand.hpp"
#include "../../Utils/ParametersMap/ParametersMap.hpp"
#include <functional>
#include <iostream>
#include <map>
#include <memory>

#include "../Commands/Game_info/Client_connection/Client_connection.hh"
#include "../Commands/Game_info/Create_game/Create_game.hh"
#include "../Commands/Game_info/Games_available/Games_available.hh"
#include "../Commands/Game_info/Game_result/Game_result.hh"
#include "../Commands/Game_info/Join_game/Join_game.hh"
#include "../Commands/Game_info/Level_complete/Level_complete.hh"
#include "../Commands/Game_info/Client_disconnect/Client_disconnect.hh"
#include "../Commands/Game_info/Missing_packages/Missing_packages.hh"

#include "../Commands/Player/Attack/Attack.hh"
#include "../Commands/Player/Die/Die.hh"
#include "../Commands/Player/Hit_wall/Hit_wall.hh"
#include "../Commands/Player/Move/Move.hh"
#include "../Commands/Player/Position/Position.hh"
#include "../Commands/Player/Power_up/Power_up.hh"
#include "../Commands/Player/Score/Score.hh"
#include "../Commands/Player/Spawn/Spawn.hh"

#include "../Commands/Enemy/Attack/Attack.hh"
#include "../Commands/Enemy/Die/Die.hh"
#include "../Commands/Enemy/Spawn/Spawn.hh"
#include "../Commands/Enemy/Destroy/Destroy.hh"
#include "../Commands/Enemy/Damage/Damage.hh"

#include "../Commands/Boss/Attack/Attack.hh"
#include "../Commands/Boss/Die/Die.hh"
#include "../Commands/Boss/Spawn/Spawn.hh"

#include "../Commands/Power_up/Spawn/Spawn.hh"

#include "../Commands/Projectile/Fired/Fired.hh"
#include "../Commands/Projectile/Hit/Hit.hh"

namespace Rtype
{
    namespace Command
    {
        class Factory {
            public:
                /**
                * @brief Constructs a Factory object and initializes the command map.
                *
                * This constructor sets up a mapping between command category/index pairs and
                * their respective command creation functions. It allows the factory to create
                * command objects dynamically based on these mappings.
                */
                Factory();

                /**
                * @brief Destructs the Factory object.
                *
                * Default destructor; clears any internal resources if necessary.
                */
                ~Factory() = default;

                /**
                * @brief Creates a command object based on a category and index identifier.
                *
                * This method retrieves the appropriate command creation function from the map
                * using the provided category and index, and returns a unique pointer to the
                * newly created command object. If the category/index pair is not mapped,
                * it returns a null pointer.
                *
                * @param cmd_category The command category identifier.
                * @param cmd_index The command index within the category.
                * @return A unique pointer to an `ACommand` object, or nullptr if the command is not found.
                */
                std::unique_ptr<Rtype::Command::ACommand> createCommand(uint8_t cmd_category, uint8_t cmd_index);

            protected:
            private:
                std::map<std::pair<uint8_t, uint8_t>, std::function<std::unique_ptr<ACommand>()>> _commandMap;
        };
    }
}
