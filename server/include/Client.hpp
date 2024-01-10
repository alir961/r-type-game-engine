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
        std::string _color = "turquoise";

    public:
        Client() = default;

        void setPlayerName(const std::string &playerName) {_playerName = playerName;};

        void setWindowWidth(const float &windowWidth) {_windowWidth = windowWidth;};

        void setWindowHeight(const float &windowHeight) {_windowHeight = windowHeight;};

        void setPlayerEntity(const EntityPtr &playerEntity) {_playerEntity = playerEntity;};

        void setNextColor() {
            if (_color == "turquoise")
                _color = "purple";
            else if (_color == "purple")
                _color = "green";
            else if (_color == "green")
                _color = "red";
            else if (_color == "red")
                _color = "blue";
            else
                _color = "turquoise";
        };

        std::string getColor() const {return _color;};

        [[nodiscard]] std::string getPlayerName() const {return _playerName;};

        [[nodiscard]] float getWindowWidth() const {return _windowWidth;};

        [[nodiscard]] float getWindowHeight() const {return _windowHeight;};

        [[nodiscard]] EntityPtr getEntity() const {return _playerEntity;};
    };

    using Session = std::shared_ptr<Client>;

}
