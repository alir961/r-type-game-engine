/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** my_r-type
*/

#pragma once


#include <deque>
#include <iostream>
#include <mutex>
#include <vector>
#include <engine/ecs/Entity.hpp>
#include <engine/network/NetworkMessage.hpp>
#include <engine/network/UDPAdapter.hpp>

namespace RType {

    class Client {
    private:
        std::string _playerName;
        EntityPtr  _playerEntity = nullptr;
        float _windowWidth;
        float _windowHeight;
        std::string _color = "turquoise";
        std::deque<Message> _messageQueue;
        UDP::endpoint _endpoint; /**< Where this player's packets come from, and where its updates go. */
        std::mutex _queueMutex;
        int _lastBulletID = 0;

    public:
        Client() = default;

        void setPlayerName(const std::string &playerName) {_playerName = playerName;};

        void setWindowWidth(const float &windowWidth) {_windowWidth = windowWidth;};

        void setWindowHeight(const float &windowHeight) {_windowHeight = windowHeight;};

        void setPlayerEntity(const EntityPtr &playerEntity) {_playerEntity = playerEntity;};

        void addMessage(const Message &message);

        Message getLastMessage();

        /**
         * @brief Take every queued message at once (used to flush them at the end of a tick).
         */
        std::deque<Message> takeMessages();

        void setEndpoint(const UDP::endpoint &endpoint) {_endpoint = endpoint;};

        [[nodiscard]] const UDP::endpoint &getEndpoint() const {return _endpoint;};

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

        [[nodiscard]] EntityPtr getEntity() const {return _playerEntity;}

        [[nodiscard]] int getNextBulletID();
    };

    using Session = std::shared_ptr<Client>;

}
