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
     * @class DeadState
     * @brief Represents a state where entities are not drawn.
     */
    class DeadState : public IDraw {
    public:
        /**
         * @brief Constructor for DeadState.
         * @param window The SFML RenderWindow.
         * @param gameView The GameView associated with the state.
         */
        DeadState(sf::RenderWindow &window, GameView &gameView) : _gameView(gameView) {}

        /**
         * @brief Draws entities on the SFML RenderWindow.
         * @param window The SFML RenderWindow on which to draw entities.
         * @param graphicEntities A vector of shared pointers to AGraphicEntity objects.
         */
        void draw(sf::RenderWindow &window, std::vector<std::shared_ptr<RType::AGraphicEntity>> graphicEntities) override {
        }
    private:
        GameView &_gameView; /**< The associated GameView. */
    };
}
