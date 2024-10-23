/*
** EPITECH PROJECT, 2024
** R-Type - Game : Game
** File description:
** Game class is the main class to game.
** It will handle game and state.
*/

#pragma once

#include "../../ECS/Core/Core.hpp"

#include "../../ECS/Entity/Button/Button.hh"

#include "../../ECS/Component/Health/Health.hh"
#include "../../ECS/Component/Position/Position.hpp"
#include "../../ECS/Component/Velocity/Velocity.hh"
#include "../../ECS/Component/Hitbox/Hitbox.hh"
#include "../../ECS/Component/Text/Text.hh"
#include "../../ECS/Component/Input/Input.hh"
#include "../../ECS/Component/Projectile/Projectile.hh"
#include "../../ECS/Component/Background/Background.hpp"
#include "../../ECS/Component/AI/AI.hh"
#include "../../ECS/Component/Button/Button.hh"
#include "../../ECS/Component/Music/Music.hh"
#include "../../ECS/Component/Sound/Sound.hh"

#include "../../ECS/System/SystemManager/SystemManager.hpp"

#include "../../ECS/System/Velocity/Velocity.hpp"
#include "../../ECS/System/Collision/Collision.hh"
#include "../../ECS/System/ProjectileCollision/ProjectileCollision.hh"
#include "../../ECS/System/InputUpdates/InputUpdates.hh"
#include "../../ECS/System/Render3D/Render3D.hh"
#include "../../ECS/System/Render2D/Render2D.hh"
#include "../../ECS/System/Background/Background.hh"
#include "../../ECS/System/UpdateVelocityAI/UpdateVelocityAI.hh"
#include "../../ECS/System/RenderText/RenderText.hh"
#include "../../ECS/System/RenderButton/RenderButton.hh"
#include "../../ECS/System/ButtonClick/ButtonClick.hh"

#include "../../ECS/RessourcePool/RessourcePool.hh"

#include "../../Utils/enemiesTypeEnum.hpp"

#include "../Network/Network.hpp"

namespace Rtype {
    enum GameState {
        MENU,
        PLAY,
    };

    class Game {
    public:
        Game(std::shared_ptr<Rtype::Network> network);
        ~Game();

        void run();
        void createPlayer(int id, float pos_x, float pos_y);
        void createOtherPlayer(int id, float pos_x, float pos_y);
        void createEnemy(enemiesTypeEnum_t enemyType, float pos_x, float pos_y);
        void movePlayer(int id, float x, float y);
        void createEnemyProjectile(int id);

    private:
        void createPlayerProjectile(std::size_t entityID);
        void destroyProjectile(std::size_t entityID);
        void createBackgroundLayers(float speed, std::string modelPath, int numberOfPanel);
        void update();
        void updateMenu();
        void render();
        void renderMenu();
        void switchState(GameState newState);
        void initMenu();
        void initGame();
        void joinGame();
        void initOptions();
        void joinRandomGame();
        void joinGameID();
        void initPlayOption();
        void initCreationGame();
        void destroyEntityMenu();
        void destroyEntityLayer();
        void destroyEntityText();
        void destroyMusic();
        void createMusic(std::string path, std::string name);
        void playMusic(std::string name);
        void stopMusic(std::string name);
        void playFromMusic(std::string name, float sec);
        void updateMusic(std::string name);
        void playSound(std::string name);
        void createSound(std::string path, std::string name);
        void updatePlayerCountText();

        std::shared_ptr<Rtype::Network> _network;
        std::map<std::string, ECS::Components::Musica> _musicMap;
        std::map<std::string, ECS::Components::SoundEffect> _soundMap;
        GameState _currentState;
        bool _isRunning;
        short _playerCount;
        short _selectedDifficulty;
        std::size_t _playerCountTextEntity;
        std::unique_ptr<ECS::Core::Core> _core;
        raylib::Window _window;
        raylib::Camera3D _camera;
        std::map<int, std::size_t> _mapID;
        std::map<std::string, std::size_t> _mapEntityMusic;
        ECS::RessourcePool _ressourcePool;
    };
};
