/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include "IDrawable.hpp"
#include "../components/Ui.hpp"
#include "../components/Effects.hpp"
#include "engine/modules/logger/ILoggerModule.hpp"
#include "engine/modules/ModuleProvider.hpp"

namespace RType {

    class IView : public IDrawable {
    public:
        /**
         * @brief Pure virtual function for update graphical object for next render.
         */
        virtual void update() = 0;

        /**
         * @brief Called once for every window event (key presses, typing, clicks).
         * @param event The SFML event.
         */
        virtual void handleEvent(const sf::Event &event) { (void) event; }

        /**
         * @brief Pure virtual function for drawing objects on an SFML RenderWindow.
         * @param window The SFML RenderWindow on which to draw the objects.
         * @param entities A vector of shared pointers to AGraphicEntity objects to be drawn.
         */
        void draw(std::vector<GraphicEntityPtr> entities) override = 0;

        void setPlayerEntity(const GraphicEntityPtr &playerEntity) { _playerEntity = playerEntity; };

        [[nodiscard]] GraphicEntityPtr getPlayerEntity() const { return _playerEntity; };

    protected:
        ILoggerModule *_logger = ModuleProvider::getInstance()->get<ILoggerModule>(ModuleType::LOGGER);

        /**
         * @brief Draw the running game dimmed, behind an in-game menu.
         */
        static void drawDimmedGame(const std::vector<GraphicEntityPtr> &entities) {
            IGraphicalModule *module = ModuleProvider::getInstance()->get<IGraphicalModule>(ModuleType::GRAPHICAL);
            RectShape dim = module->createRectShape();

            for (const auto &entity: entities)
                entity->draw();
            Particles::draw();
            dim->setSize(Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
            dim->setBackgroundColor(Theme::Dim);
            dim->draw();
        }

    private:
        GraphicEntityPtr _playerEntity = nullptr;
    };

    using ClientView = std::shared_ptr<IView>;

}