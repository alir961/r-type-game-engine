/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** GraphicEntityFactory.cpp
*/

#include "../../include/entities/GraphicEntityFactory.hpp"

std::shared_ptr<GraphicBullet> GraphicEntityFactory::createGraphicBullet(std::shared_ptr<Entity> &entity) {
    return std::make_shared<GraphicBullet>(entity);
}

std::shared_ptr<GraphicMonster> GraphicEntityFactory::createGraphicMonster(std::shared_ptr<Entity> &entity) {
    return std::make_shared<GraphicMonster>(entity);
}

std::shared_ptr<GraphicStarship> GraphicEntityFactory::createGraphicStarship(std::shared_ptr<Entity> &entity) {
    return std::make_shared<GraphicStarship>(entity);
}
