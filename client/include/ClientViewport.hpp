/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** ClientViewport.hpp
*/

#pragma once

#include "views/IView.hpp"
#include "UDPClient.hpp"
#include "../../engine/include/engine/modules/ModuleProvider.hpp"
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
    class DeadView;
    class WinView;
    class GameView;
    class LoginView;
    class GraphicalModule;

    constexpr uint32_t WINDOW_WIDTH = 1920;
    constexpr uint32_t WINDOW_HEIGHT = 1080;
    constexpr int WINDOW_FPS = 60;

    /**
     * @enum views
     * @brief Enumeration representing different states of the game view.
     */
    enum class ViewState {
        MENU = 0,     /**< Main menu state. */
        OPTIONS = 1,  /**< Options menu state. */
        GAME = 2,     /**< In-game state. */
        PAUSE = 3,    /**< Pause state. */
        DEAD = 4,     /**< Game over state. */
        LOGIN = 5,     /**< Game over state. */
        WIN = 6,      /**< Won game state. */
        OPTIONSGAME = 7
    };

    /**
     * @class ClientViewport
     * @brief Represents the main game view handling graphics, input, and entities.
     */
    class ClientViewport {
    private:
        sf::RenderWindow _window = sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "R-Type");
        ViewState _viewState = ViewState::LOGIN;                          /**< Current state of the game view. */
        sf::Clock _animationClock;                                         /**< Clock for managing animations and time-related operations. */
        std::vector<GraphicEntityPtr> _graphicEntities;                   /**< Vector of graphic entities in the game. */
        std::shared_ptr<IView> _selectedView;
        UDPClient _client;
        sf::Event event{};
        IGraphicalModule *_graphicalModule;
        ModuleProvider _provider = ModuleProvider();

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
        void handleInput(const GraphicEntityPtr &entity) const;

        /**
         * @brief Private method to handle basic input.
         */
        void basicInput();

        /**
         * @brief Private method to launch the SFML window and test keyboard input for a specific _entity.
         * @param entity The graphic entities to test with keyboard input.
         */
        void launchWindow(const GraphicEntityPtr &entity);

    public:
        /**
         * @brief Constructor for the ClientViewport class.
         */
        explicit ClientViewport(asio::io_context &ioContext, UDP::endpoint endpoint);

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
        void addGraphicEntity(GraphicEntityPtr entity);

        /**
         * @brief Method to retrieve a graphic entity by name
         * @param name The entity name
         * @return Find entity or nullptr
         */
        GraphicEntityPtr getGraphicEntityByName(const std::string &name) const {
            for (const auto &entity: _graphicEntities) {
                if (entity->getEntityName() == name)
                    return entity;
            }
            std::cerr << "Unable tu find entity " << name << "\n";
            return nullptr;
        }

        /**
         * Retrieve current SFML event
         * @return The event
         */
        [[nodiscard]] sf::Event getEvent() const {
            return event;
        }
    };
}

#include "views/MenuView.hpp"
#include "views/OptionsView.hpp"
#include "views/PauseView.hpp"
#include "views/DeadView.hpp"
#include "views/WinView.hpp"
#include "views/GameView.hpp"
#include "views/LoginView.hpp"
#include "entities/GraphicEntityFactory.hpp"
