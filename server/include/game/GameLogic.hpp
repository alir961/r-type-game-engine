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
#include "engine/tools/Thread.hpp"

namespace RType {

    constexpr int TICK_PER_SECOND = 60;
    constexpr int EPSILON_TIME_MS = 1000 / TICK_PER_SECOND;

    class GameLogic {
    private:
        UDPAdapter *_adapter;
        SessionManager _sessionManager;
        EntityManager _entityManager;
        EntityFactory _factory = EntityFactory(&_entityManager);
        Thread _thread;
        int _tickNumber;

        void serverLoopIterate();

        void moveBulletPlayer();

        void sendMessage(MessageType type, const std::string_view &data);

    public:
        /**
         * Initialize a default GameLogic
         */
        GameLogic(RType::UDPAdapter *adapter);

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

        [[nodiscard]] bool isStopped();

        EntityPtr createPlayerEntity(int sessionID, const Session &session);

        void createBulletPlayerEntity(int sessionID);

        static Direction getDirection(MessageType type);

        void checkEntitiesStatus();

        void sendAllMessages(int sessionID);

        void sendAllEntities(int sessionID);

        void sendMessageFromEntity(const EntityPtr& entity);

        void addMessageClients(int sessionID, MessageType type, const std::string_view &data);

        void sendPlayerDetails(const EntityPtr& entity);

        void sendBulletPlayerDetails(const EntityPtr& entity);
    };

}
