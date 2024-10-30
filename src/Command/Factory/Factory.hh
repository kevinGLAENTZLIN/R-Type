/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Factory
*/

#pragma once
<<<<<<< HEAD
#if defined(_WIN32)           
	#define NOGDI             // All GDI defines and routines
	#define NOUSER            // All USER defines and routines
#endif

#include "raylib-cpp.hpp"

#if defined(_WIN32)           // raylib uses these names as function parameters
	#undef near
	#undef far
#endif
#include "../ICommand.hh"
#include "../ACommand.hpp"
=======

>>>>>>> d669fe12eeee9ddacaae29b8270b4933c164e2b4
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

#include "../Commands/Player/Attack/Attack.hh"
#include "../Commands/Player/Die/Die.hh"
#include "../Commands/Player/Hit_wall/Hit_wall.hh"
#include "../Commands/Player/Move/Move.hh"
#include "../Commands/Player/Power_up/Power_up.hh"
#include "../Commands/Player/Score/Score.hh"
#include "../Commands/Player/Spawn/Spawn.hh"

#include "../Commands/Enemy/Attack/Attack.hh"
#include "../Commands/Enemy/Die/Die.hh"
#include "../Commands/Enemy/Spawn/Spawn.hh"

#include "../Commands/Boss/Attack/Attack.hh"
#include "../Commands/Boss/Die/Die.hh"
#include "../Commands/Boss/Spawn/Spawn.hh"

// #include "../Commands/Power_up/"

#include "../Commands/Projectile/Fired/Fired.hh"
#include "../Commands/Projectile/Hit/Hit.hh"

namespace Rtype
{
    namespace Command
    {
        class Factory {
            public:
                Factory();
                ~Factory() = default;

                std::unique_ptr<Rtype::Command::ACommand> createCommand(uint8_t cmd_category, uint8_t cmd_index);

            protected:
            private:
                std::map<std::pair<uint8_t, uint8_t>, std::function<std::unique_ptr<ACommand>()>> _commandMap;
        };
    }
}
