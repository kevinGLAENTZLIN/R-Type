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
#include "../../ECS/Component/Textfield/Textfield.hh"

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
#include "../../ECS/System/GetDeadEntities/GetDeadEntities.hh"
#include "../../ECS/System/AIFiringProjectile/AIFiringProjectile.hh"
#include "../../ECS/System/TextfieldInput/TextfieldInput.hh"
#include "../../ECS/System/RenderTextfield/RenderTextfield.hh"

#include "../../ECS/RessourcePool/RessourcePool.hh"

#include "../../Utils/enemiesTypeEnum.hpp"

#define CONVERT_ACMD_TO_CMD(TYPE, CMD_CATEGORY, CMD_INDEX)  _network->convertACommandToCommand<TYPE>(_network->createCommand(static_cast<uint8_t>(CMD_CATEGORY), static_cast<uint8_t>(CMD_INDEX)))

namespace Rtype {
    enum GameState {
        MENU,
        PLAY,
    };

    class Network;

    class Game {
    public:
        Game(std::shared_ptr<Rtype::Network> network, bool render);
        ~Game();

        void run();
        void runServer();
        void movePlayer(int id, double x, double y);
        void initGame(int id);

        bool getJoiningGame();
        void setIsJoiningGame(bool state);
        bool getIsAvailableGames();
        void setIsAvailableGames(bool state);

        std::vector<std::tuple<int, int, int>> getAvailableGames();
        void addAvailableGames(int game_id, int nb_player, int nb_player_max);
        void clearAvailableGames();
        void createPlayer(int id, float pos_x, float pos_y, int invincibility);
        void createOtherPlayer(int id, float pos_x, float pos_y);
        void createEnemy(enemiesTypeEnum_t enemyType, float pos_x, float pos_y, int health);
        void createEnemy(int entityId, enemiesTypeEnum_t enemyType, float pos_x, float pos_y, int health);
        void createBoss1();
        void createProjectile(int entityId, int projectileId);
        void failToConnect();
        void joinGame();

    private:
        std::size_t createCyclingEnemy(enemiesTypeEnum_t enemyType, float pos_x, float pos_y, float dest_x, float dest_y);
        void createEnemyBydoShots(int id);
        void createPlayerProjectile(int entityId, int projectileId);
        void loadMusic();
        void destroyProjectile(std::size_t entityID);
        void createBackgroundLayers(float speed, std::string modelPath, int numberOfPanel);
        void update();
        void updateMenu();
        void render();
        void renderMenu();
        void switchState(GameState newState);
        void initMenu();
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
        void DrawProgressBar(int progress);
        void LoadAssets();
        std::vector<std::size_t> getAllInputs();
        void sendInput(std::vector<std::size_t> vec);
        void sendProjectile();

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
        std::map<int, std::size_t> _serverToLocalPlayersId;
        std::map<int, std::size_t> _serverToLocalEnemiesId;
        std::map<int, std::size_t> _serverToLocalProjectilesId;
        std::map<std::string, std::size_t> _mapEntityMusic;
        ECS::RessourcePool _ressourcePool;
        std::shared_ptr<Rtype::Network> _network;
        bool _isJoiningGame;
        bool _isAvailableGames;
        bool _isRendering;
        bool _modelCreated;
        std::vector<std::tuple<int, int, int>> _availableGames;
    };
};
