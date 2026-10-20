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
#include "Difficulty.hpp"
#include "engine/tools/Thread.hpp"
#include <mutex>

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
        std::recursive_mutex _mutex; /**< Guards the game state shared by the game loop and the network thread. */
        int _tickNumber = 0;
        Difficulty _difficulty = Difficulty::NORMAL;
        int _ticksUntilMonster = 0;   /**< Countdowns, so a difficulty change applies right away. */
        int _ticksUntilStarship = 0;
        int _ticksUntilVolley = 0;
        int _lastMonsterID = 0;
        int _lastStarshipID = 0;
        std::map<int, int> _lastBulletStarship;

        /**
         * Run the simulation at TICK_PER_SECOND until the server stops
         */
        void serverLoop();

        /**
         * Advance the world by one tick, then send every player its updates
         */
        void serverLoopIterate();

        void movePlayerBullets();

        void moveMonsters();

        void sendMessage(MessageType type, const std::string_view &data);

    public:
        /**
         * Initialize a default GameLogic
         */
        GameLogic(RType::UDPAdapter *adapter);

        /**
         * Retrieve the current sessions manager
         *
         * @return Reference to SessionManager _instance
         */
        [[nodiscard]] SessionManager &getSessionManager() {
            return _sessionManager;
        }

        /**
         * Retrieve the current entities manager
         *
         * @return Reference to EntityManager _instance
         */
        [[nodiscard]] EntityManager &getEntityManager() {
            return _entityManager;
        }

        /**
         * Retrieve the current entity factory
         *
         * @return Reference to EntityFactory _instance
         */
        [[nodiscard]] EntityFactory &getFactory() {
            return _factory;
        }

        [[nodiscard]] bool isStopped();

        /**
         * Lock the game state: hold it while handling a network message
         */
        [[nodiscard]] std::unique_lock<std::recursive_mutex> lock() {
            return std::unique_lock(_mutex);
        }

        /**
         * Send each player the messages queued for it, to its own address
         */
        void flushAllClients();

        /**
         * Change the difficulty for everyone on the server and tell every player
         */
        void setDifficulty(Difficulty difficulty);

        [[nodiscard]] Difficulty getDifficulty() const {
            return _difficulty;
        }

        /**
         * Send a message right away to one player (e.g. the connection reply)
         */
        void sendTo(int sessionID, MessageType type, const std::string_view &data);

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

        void sendBulletStarshipDetails(const EntityPtr& entity);

        void sendStarshipDetails(const EntityPtr& entity);

        void sendMonsterDetails(const EntityPtr& entity);

        void sendStaticEntityDetails(const EntityPtr& entity);

        void createMonsterEntity();

        void createStaticEntity(int staticID, float startX, float startY);

        int getNextMonsterID();

        int getNextStarshipID();

        int getNextBulletStarshipID(int starshipID);

        bool move(Direction direction, EntityPtr entity);

        /**
         * Move a player ship, keeping it inside the screen instead of killing it at the edges
         *
         * @param direction Where the player wants to go
         * @param entity The player entity
         */
        void movePlayer(Direction direction, EntityPtr entity);

        void moveLeft(EntityPtr entity);

        void moveRight(EntityPtr entity);

        void moveDown(EntityPtr entity);

        void moveUp(EntityPtr entity);

        void checkHits(EntityPtr entityPtr);

        bool hit(EntityPtr entityPtr, EntityPtr entity);

        void setDamageEntity(EntityPtr entityPtr, EntityPtr entity);

        void putDamage(EntityPtr entityPtr, EntityPtr entity);

        EntityPtr getPlayerEntity(int playerID);

        void checkEntitySessions(EntityPtr entity);

        void createStarshipEntity();

        void createBulletStarshipEntity(EntityPtr entity);

        void moveStarships();

        void moveStarshipsBullets();
    };

}
