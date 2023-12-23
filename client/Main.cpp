#include "GameView.hpp"
#include "include/entities/GraphicEntityFactory.hpp"
#include <engine/Logger.hpp>
#include <engine/ecs/Entity.hpp>
#include <engine/ecs/EntityManager.hpp>

using namespace RType;

int main() {
    try {
        GameView gameView;
        EntityManager entityManager;

        //        auto bulletEntity = entityManager.createEntity();
        //        auto monsterEntity = entityManager.createEntity();
        auto starshipEntity = entityManager.createEntity();

        //        auto graphicBullet = GraphicEntityFactory::createGraphicBullet(bulletEntity);
        //        auto graphicMonster = GraphicEntityFactory::createGraphicMonster(monsterEntity);
        auto graphicStarship = GraphicEntityFactory::createGraphicStarship(starshipEntity);

        //        gameView.addGraphicEntity(graphicBullet);
        //        gameView.addGraphicEntity(graphicMonster);
        gameView.addGraphicEntity(graphicStarship);

        logInformation("Starting game view...");
        gameView.start();

    } catch (const std::exception &e) {
        // error here because logError is undefined logError("Exception caught in main: " + std::string(e.what()));
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
