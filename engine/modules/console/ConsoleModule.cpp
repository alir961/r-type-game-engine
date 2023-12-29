/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#include "ConsoleModule.hpp"
#include <iostream>

extern "C" {
RType::IModule *initializeConsoleModule() {
    return new RType::ConsoleModule();
}

void destroy(RType::ConsoleModule *library) {
    delete library;
}
}

void RType::ConsoleModule::load() {
    std::cout << "Load Console Module\n";
}

void RType::ConsoleModule::unload() {
    std::cout << "Unload Console Module\n";
}

void RType::ConsoleModule::addToHistory(const std::string &message) {
    _history.push_back(message);
}

void RType::ConsoleModule::setInput(const std::string &input) {
    _input = input;
}

const RType::History &RType::ConsoleModule::getHistory() const {
    return _history;
}

const std::string &RType::ConsoleModule::getInput() const {
    return _input;
}
