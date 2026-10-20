/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** ClientViewport.hpp
*/

#pragma once

#include "views/IView.hpp"
#include "UDPClient.hpp"
#include "components/Background.hpp"
#include "entities/Explosion.hpp"
#include "components/Effects.hpp"
#include "components/ConsoleOverlay.hpp"
#include "engine/modules/logger/ILoggerModule.hpp"
#include <engine/modules/animation/IAnimationModule.hpp>
#include <engine/modules/ModuleProvider.hpp>
#include <SFML/System/Clock.hpp>
#include <engine/Logger.hpp>
#include <engine/ecs/EntityManager.hpp>
#include <memory>
#include <optional>
#include <vector>
#include <algorithm>

namespace RType {

    class MenuView;
    class OptionsView;
    class PauseView;
    class GameView;
    class LoginView;
    class LoadView;
    class DeadView;
    class GraphicalModule;
    class AnimationModule;

    /**
     * @enum views
     * @brief Enumeration representing different states of the game view.
     */
    enum class ViewState {
        MENU = 0,     /**< Main menu state. */
        OPTIONS = 1,  /**< Options menu state. */
        GAME = 2,     /**< In-game state. */
        PAUSE = 3,    /**< Pause state. */
        LOGIN = 4,     /**< Game over state. */
        OPTIONSGAME = 5,
        LOADSCREEN = 6,
        DEAD = 7,
        HOWTOPLAY = 8,     /**< Controls and enemies guide, opened from the main menu. */
        HOWTOPLAYGAME = 9, /**< Same guide, opened from the pause menu. */
        DIFFICULTY = 10,   /**< Difficulty choice, before starting a game. */
    };

    /**
     * @class ClientViewport
     * @brief Represents the main game view handling graphics, input, and entities.
     */
    class ClientViewport {

        using MessageHandlerFunction = std::function<void(const std::vector<std::string> &)>;

    private:
        ViewState _viewState = ViewState::LOGIN;                          /**< Current state of the game view. */
        sf::Clock _animationClock;                                         /**< Clock for managing animations and time-related operations. */
        std::vector<GraphicEntityPtr> _graphicEntities;                   /**< Vector of graphic entities in the game. */
        std::shared_ptr<IView> _selectedView;
        UDPClientPtr _client;
        sf::Event _event{};
        ModuleProviderPtr _provider = ModuleProvider::getInstance();
        IGraphicalModule *_graphicalModule = _provider->loadAndGetModule<IGraphicalModule>(ModuleType::GRAPHICAL);
        ILoggerModule *_logger = _provider->loadAndGetModule<ILoggerModule>(ModuleType::LOGGER);
        std::unordered_map<std::string, MessageHandlerFunction> _handlers; ///< Map of message handlers.
        EntityManager _entityManager;
        GraphicEntityPtr _playerEntity = nullptr;
        std::optional<ViewState> _pendingView;                            /**< View to switch to at the next safe point. */
        std::vector<ExplosionPtr> _explosions;                            /**< Explosions currently playing. */
        std::unique_ptr<Background> _menuBackground;                       /**< Starfield behind the menus (built once the window exists). */
        std::string _serverAddress;                                        /**< "hostname:port" of the last connection attempt. */
        sf::Clock _shootClock;                                             /**< Limits the fire rate. */
        std::string _difficulty = "normal";                                /**< Difficulty announced by the server. */
        std::unique_ptr<ConsoleOverlay> _console;                          /**< Developer console (F2), when its module is loaded. */
        sf::Clock _frameClock;                                             /**< Measures the frame rate for the "fps" command. */
        float _fps = 0.0F;
        bool _showFps = false;

        /**
         * @brief Load the optional modules (sound, particles, console); the game runs without them.
         */
        void loadOptionalModules();

        void drawFps();

        void destroyGraphicEntity(GraphicEntityPtr entity);

        /**
         * @brief Replace the current view if setView was called since the last check.
         */
        void applyPendingView();

        /**
         * @brief True in every view where the game keeps running behind (game, pause, in-game menus).
         */
        [[nodiscard]] bool isInGame() const;

        /**
         * @brief Private method to handle drawing operations.
         */
        void draw();

        /**
         * @brief Private method to update entities based on elapsed time.
         * @param deltaTime Elapsed time since the last update.
         */
        void updateEntities(float deltaTime);

        /**
         * @brief Private method to handle input for a specific graphic _entity.
         * @param entity The graphic entity to handle input for.
         */
        void handleGameInput();

        /**
         * @brief Handle one-shot game keys (color change) from window events.
         */
        void handleGameEvent(const sf::Event &event);

        /**
         * @brief Private method to launch the SFML window and test keyboard input for a specific _entity.
         * @param entity The graphic entities to test with keyboard input.
         */
        void launchWindow();

    public:
        /**
         * @brief Constructor for the ClientViewport class.
         */
        explicit ClientViewport();

        /**
         * @brief Destructor for the ClientViewport class.
         */
        ~ClientViewport() = default;

        /**
         * @brief Method to start the game loop.
         * @return Exit code or status of the game.
         */
        int start();

        /**
         * @brief Method to set the current view state.
         * @param state The new view state to set.
         */
        void setView(ViewState state);

        /**
         * @brief Register the game commands in the console module (call again after reloading it).
         */
        void setupConsole();

        /**
         * @return "hostname:port" of the last connection attempt
         */
        [[nodiscard]] const std::string &getServerAddress() const { return _serverAddress; }

        /**
         * @return The username of the connected player, empty when not connected
         */
        [[nodiscard]] std::string getUsername() const { return _client ? _client->getUsername() : ""; }

        /**
         * @return The last score received for the local player
         */
        [[nodiscard]] int getScore() const { return _client ? _client->getScore() : 0; }

        /**
         * @brief Ask the server to switch difficulty (it applies to every player on it).
         * @param difficulty "easy", "normal" or "hard"
         */
        void requestDifficulty(const std::string &difficulty);

        /**
         * @return The difficulty the server is running ("easy", "normal" or "hard")
         */
        [[nodiscard]] const std::string &getDifficulty() const { return _difficulty; }

        /**
         * @brief Method to add a graphic _entity to the game.
         * @param entity The graphic _entity to be added.
         */
        void addGraphicEntity(const GraphicEntityPtr &entity);

        /**
         * @brief Method to retrieve a graphic entity by name
         * @param name The entity name
         * @return Find entity or nullptr
         */
        GraphicEntityPtr getGraphicEntityByName(const std::string &name) const;

        /**
         * Retrieve current SFML _event
         * @return The _event
         */
        [[nodiscard]] sf::Event getEvent() const;

        /**
         * Try connecting to the game server
         *
         * @param hostname Server hostname
         * @param port Server port
         * @param username Player username
         */
        void connectToServer(const std::string& hostname, int port, std::string username);

        /**
         * Destroy network connection and wait thread
         */
        void closeConnectionToServer();

        /**
         * Assign each MessageType to a corresponding action
         */
        void setHandlers();

        void handleMessageFromServer();

        void player(const std::vector<std::string> &splitMessage);
        void bulletPlayer(const std::vector<std::string> &splitMessage);
        void monster(const std::vector<std::string> &splitMessage);
        void staticEntity(const std::vector<std::string> &splitMessage);
        void starship(const std::vector<std::string> &splitMessage);
        void bulletStarship(const std::vector<std::string> &splitMessage);
        void death(const std::vector<std::string> &splitMessage);
        void disconnect(const std::vector<std::string> &splitMessage);
        void changePlayerColor(const std::vector<std::string> &splitMessage);

        void createNewPlayer(const std::vector<std::string> &splitMessage);
        void updatePlayer(const std::vector<std::string> &splitMessage);
        void createNewBulletPlayer(const std::vector<std::string> &splitMessage);
        void updateBulletPlayer(const std::vector<std::string> &splitMessage);
        void createNewMonster(const std::vector<std::string> &splitMessage);
        void updateMonster(const std::vector<std::string> &splitMessage);
        void createNewStatic(const std::vector<std::string> &splitMessage);
        void updateStatic(const std::vector<std::string> &splitMessage);
        void createNewStarship(const std::vector<std::string> &splitMessage);
        void updateStarship(const std::vector<std::string> &splitMessage);
        void createNewStarshipBullet(const std::vector<std::string> &splitMessage);
        void updateStarshipBullet(const std::vector<std::string> &splitMessage);
    };
}

#include "views/MenuView.hpp"
#include "views/OptionsView.hpp"
#include "views/PauseView.hpp"
#include "views/GameView.hpp"
#include "views/LoginView.hpp"
#include "views/LoadView.hpp"
#include "views/DeadView.hpp"
#include "views/HowToPlayView.hpp"
#include "views/DifficultyView.hpp"
#include "entities/GraphicEntityFactory.hpp"
