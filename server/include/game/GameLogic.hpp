/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include "../SessionManager.hpp"
#include "engine/ecs/EntityManager.hpp"
#include "EntityFactory.hpp"

namespace RType {

    class GameLogic {
    private:
        SessionManager _sessionManager;
        EntityManager _entityManager;
        EntityFactory _factory = EntityFactory(&_entityManager);

    public:
        /**
         * Initialize a default GameLogic
         */
        explicit GameLogic() = default;

        /**
         * Retrieve the current sessions manager
         *
         * @return Reference to SessionManager instance
         */
        [[nodiscard]] SessionManager &getSessionManager() {
            return _sessionManager;
        }

        /**
         * Retrieve the current entities manager
         *
         * @return Reference to EntityManager instance
         */
        [[nodiscard]] EntityManager &getEntityManager() {
            return _entityManager;
        }

        /**
         * Retrieve the current entity factory
         *
         * @return Reference to EntityFactory instance
         */
        [[nodiscard]] EntityFactory &getFactory() {
            return _factory;
        }
    };

}
