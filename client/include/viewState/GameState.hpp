/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** GameView.hpp
*/

#pragma once
#include "IDraw.hpp"

namespace RType {
    /**
     * @class GameState
     * @brief Represents a state where entities are drawn.
     */
    class GameState : public IDraw {
    public:
        /**
         * @brief Constructor for GameState.
         * @param window The SFML RenderWindow.
         * @param gameView The GameView associated with the state.
         */
        GameState(sf::RenderWindow &window, GameView &gameView) : _gameView(gameView) {}

        /**
         * @brief Draws entities on the SFML RenderWindow.
         * @param window The SFML RenderWindow on which to draw entities.
         * @param graphicEntities A vector of shared pointers to AGraphicEntity objects.
         */
        void draw(sf::RenderWindow &window, std::vector<std::shared_ptr<RType::AGraphicEntity>> graphicEntities) override {
            for (auto &entity: graphicEntities) {
                entity->draw(window);
            }
        }
    private:
        GameView &_gameView; /**< The associated GameView. */
    };
}
