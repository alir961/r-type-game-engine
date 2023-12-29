/*
** EPITECH PROJECT, 2023
** NEWRTYPE
** File description:
** ConsoleModule
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

void RType::ConsoleModule::addMessage(const std::string& message) {
   messages.push_back(message);
}

void RType::ConsoleModule::setInput(const std::string& input) {
   this->input = input;
}

const std::vector<std::string>& RType::ConsoleModule::getMessages() const {
   return messages;
}

const std::string& RType::ConsoleModule::getInput() const {
   return input;
}
