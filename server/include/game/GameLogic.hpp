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
        explicit GameLogic() = default;

        [[nodiscard]] SessionManager &getSessionManager() {
            return _sessionManager;
        }

        [[nodiscard]] EntityManager &getEntityManager() {
            return _entityManager;
        }

        [[nodiscard]] EntityFactory &getFactory() {
            return _factory;
        }
    };

}
