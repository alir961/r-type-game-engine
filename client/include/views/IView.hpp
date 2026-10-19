/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include "IDrawable.hpp"
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
         * @brief Pure virtual function for drawing objects on an SFML RenderWindow.
         * @param window The SFML RenderWindow on which to draw the objects.
         * @param entities A vector of shared pointers to AGraphicEntity objects to be drawn.
         */
        void draw(std::vector<GraphicEntityPtr> entities) override = 0;

        void setPlayerEntity(const GraphicEntityPtr &playerEntity) { _playerEntity = playerEntity; };

        [[nodiscard]] GraphicEntityPtr getPlayerEntity() const { return _playerEntity; };

    protected:
        ILoggerModule *_logger = ModuleProvider::getInstance()->get<ILoggerModule>(ModuleType::LOGGER);

    private:
        GraphicEntityPtr _playerEntity = nullptr;
    };

    using ClientView = std::shared_ptr<IView>;

}