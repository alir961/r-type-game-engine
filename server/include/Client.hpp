/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** my_r-type
*/

#pragma once


#include <iostream>
#include <engine/ecs/Entity.hpp>

namespace RType {
    class Client {
    private:
        std::string _playerName;
        EntityPtr  _playerEntity;
        float _windowWidth;
        float _windowHeight;

    public:
        Client() = default;

        void setPlayerName(const std::string &playerName) {_playerName = playerName;};

        void setWindowWidth(const float &windowWidth) {_windowWidth = windowWidth;};

        void setWindowHeight(const float &windowHeight) {_windowHeight = windowHeight;};

        void setPlayerEntity(const EntityPtr &playerEntity) {_playerEntity = playerEntity;};

        [[nodiscard]] std::string getPlayerName() const {return _playerName;};

        [[nodiscard]] float getWindowWidth() const {return _windowWidth;};

        [[nodiscard]] float getWindowHeight() const {return _windowHeight;};

        [[nodiscard]] EntityPtr getEntity() const {return _playerEntity;};
    };
}
