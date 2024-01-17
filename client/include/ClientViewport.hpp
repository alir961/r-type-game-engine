/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** ClientViewport.hpp
*/

#pragma once

#include "views/IView.hpp"
#include "UDPClient.hpp"
#include "engine/modules/logger/ILoggerModule.hpp"
#include <engine/modules/animation/IAnimationModule.hpp>
#include <engine/modules/ModuleProvider.hpp>
#include <SFML/System/Clock.hpp>
#include <engine/Logger.hpp>
#include <engine/ecs/EntityManager.hpp>
#include <memory>
#include <vector>
#include <algorithm>

namespace RType {

    class MenuView;
    class OptionsView;
    class PauseView;
    class GameView;
    class LoginView;
    class LoadView;
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
        IGraphicalModule *_graphicalModule;
        IAnimationModule *_animationModule;
        ILoggerModule *_logger = _provider->loadAndGetModule<ILoggerModule>(ModuleType::LOGGER);
        std::unordered_map<std::string, MessageHandlerFunction> _handlers; ///< Map of message handlers.
        EntityManager _entityManager;
        GraphicEntityPtr _playerEntity = nullptr;

        GraphicEntityPtr getGraphicEntity(const std::string &entityName);
        void destroyGraphicEntity(GraphicEntityPtr entity);

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
        void handleInput() const;

        /**
         * @brief Private method to handle basic input.
         */
        void basicInput();

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
        void death(const std::vector<std::string> &splitMessage);
        void disconnect(const std::vector<std::string> &splitMessage);
        void changePlayerColor(const std::vector<std::string> &splitMessage);

        void createNewPlayer(const std::vector<std::string> &splitMessage);
        void updatePlayer(const std::vector<std::string> &splitMessage);
        void createNewBulletPlayer(const std::vector<std::string> &splitMessage);
        void updateBulletPlayer(const std::vector<std::string> &splitMessage);
    };
}

#include "views/MenuView.hpp"
#include "views/OptionsView.hpp"
#include "views/PauseView.hpp"
#include "views/GameView.hpp"
#include "views/LoginView.hpp"
#include "views/LoadView.hpp"
#include "entities/GraphicEntityFactory.hpp"
