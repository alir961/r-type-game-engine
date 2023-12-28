/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** GameView.hpp
*/

#pragma once

#include "entities/GraphicEntity.hpp"
#include "entities/GraphicEntityFactory.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <engine/Logger.hpp>
#include <engine/ecs/EntityManager.hpp>
#include <memory>
#include <vector>

constexpr uint32_t WINDOW_WIDTH = 1920;
constexpr uint32_t WINDOW_HEIGHT = 1080;

namespace RType {
    class MenuState;
    class OptionsState;
    class PauseState;
    class DeadState;
    class GameState;
    class LoginState;
    /**
     * @enum viewState
     * @brief Enumeration representing different states of the game view.
     */
    enum class ViewState {
        MENU = 0,     /**< Main menu state. */
        OPTIONS = 1,  /**< Options menu state. */
        GAME = 2,     /**< In-game state. */
        PAUSE = 3,    /**< Pause state. */
        DEAD = 4,     /**< Game over state. */
        LOGIN = 5     /**< Game over state. */
    };

    /**
     * @class GameView
     * @brief Represents the main game view handling graphics, input, and entities.
     */
    class GameView {
    private:
        sf::RenderWindow _window;                                         /**< SFML Render Window for rendering graphics. */
        ViewState _viewState;                                             /**< Current state of the game view. */
        sf::Clock animationClock;                                         /**< Clock for managing animations and time-related operations. */
        std::vector<std::shared_ptr<AGraphicEntity>> _graphicEntities;    /**< Vector of graphic entities in the game. */
        std::shared_ptr<MenuState> _menuState;                            /**< Shared ptr to the Menu ViewState. */
        std::shared_ptr<OptionsState> _optionsState;                      /**< Shared ptr to the Options ViewState. */
        std::shared_ptr<PauseState> _pauseState;                          /**< Shared ptr to the Pause ViewState. */
        std::shared_ptr<DeadState> _deadState;                            /**< Shared ptr to the Dead ViewState. */
        std::shared_ptr<GameState> _gameState;                            /**< Shared ptr to the Game ViewState. */
        std::shared_ptr<LoginState> _loginState;                           /**< Shared ptr to the Login ViewState. */

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
         * @brief Private method to handle input for a specific graphic entity.
         * @param entity The graphic entity to handle input for.
         */
        void handleInput(std::shared_ptr<AGraphicEntity> &entity);

        /**
         * @brief Private method to launch the SFML window and test keyboard input for a specific entity.
         * @param entity The graphic entity to test with keyboard input.
         */
        void launchWindow(std::shared_ptr<AGraphicEntity> entity); // put graphical entity by parameters to test entity move with keyboard input : function is handleInput

    public:
        /**
         * @brief Constructor for the GameView class.
         */
        explicit GameView();

        /**
         * @brief Destructor for the GameView class.
         */
        ~GameView() = default;

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
         * @brief Method to add a graphic entity to the game.
         * @param entity The graphic entity to be added.
         */
        void addGraphicEntity(std::shared_ptr<AGraphicEntity> entity);
    };
}

#include "viewState/MenuState.hpp"
#include "viewState/OptionsState.hpp"
#include "viewState/PauseState.hpp"
#include "viewState/DeadState.hpp"
#include "viewState/GameState.hpp"
#include "viewState/LoginState.hpp"
