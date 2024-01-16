/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** my_r-type
*/

#include "../../include/game/GameLogic.hpp"

extern "C" {
bool _stop = false;

void stopServer(int) {
    if (_stop) exit(EXIT_FAILURE);
    std::cout << "Stopping the server [...]\n";
    _stop = true;
}
}

RType::GameLogic::GameLogic(RType::UDPAdapter *adapter) : _adapter(adapter) {
    signal(SIGINT, &stopServer);

    _thread.run([this]() { serverLoopIterate(); });
}

void RType::GameLogic::serverLoopIterate() {
    if (_stop) return;

    std::this_thread::sleep_for(std::chrono::milliseconds(EPSILON_TIME_MS));
    _tickNumber++;
    moveBulletPlayer();
    serverLoopIterate();
}


bool RType::GameLogic::isStopped() {
    if (_stop)
        _thread.wait();
    return _stop;
}

void RType::GameLogic::moveBulletPlayer() {
    for (auto &entity: _entityManager.getEntities()) {
        if (Split::split(entity->getEntityName(), " ")[0] == "bulletPlayer") {
            entity->move(Direction::RIGHT, _entityManager.getEntities(), _sessionManager.getWindowWidth(),
                         _sessionManager.getWindowHeight());
            char buffer[100];
            sprintf(buffer, "move %s\n", entity->getEntityName().c_str());
            sendMessage(MessageType::MOVE_PLAYER_BULLET, buffer);
        }
    }
}

void RType::GameLogic::sendMessage(RType::MessageType type, const std::string_view &data) {
    const RType::Message response = RType::NetworkMessageBuilder(type)
            .setData(data)
            .build();
    _adapter->sendData(response);
}
