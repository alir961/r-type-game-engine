/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** GraphicEntityFactory.cpp
*/

#include "../../include/entities/GraphicEntityFactory.hpp"

using namespace RType;

std::shared_ptr<GraphicBullet> GraphicEntityFactory::createGraphicBullet(engine::ecs::Entity &entity) {
    return std::make_shared<GraphicBullet>(entity);
}

std::shared_ptr<GraphicMonster> GraphicEntityFactory::createGraphicMonster(engine::ecs::Entity &entity) {
    return std::make_shared<GraphicMonster>(entity);
}

std::shared_ptr<GraphicStarship> GraphicEntityFactory::createGraphicStarship(engine::ecs::Entity &entity) {
    return std::make_shared<GraphicStarship>(entity);
}
