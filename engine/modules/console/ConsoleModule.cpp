/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** ConsoleModule.cpp
*/

#include <sstream>
#include "ConsoleModule.hpp"

extern "C" {
RType::IModule *initializeConsoleModule() {
    return new RType::ConsoleModule();
}

void destroy(RType::ConsoleModule *library) {
    delete library;
}
}

void RType::ConsoleModule::load() {
    registerCommand("help", "list the commands", [this](const std::vector<std::string> &) {
        std::string text = "Commands:";

        for (const auto &[name, command]: _commands)
            text += "\n  " + name + " - " + command.help;
        return text;
    });
    registerCommand("clear", "clear the console", [this](const std::vector<std::string> &) {
        _history.clear();
        return std::string();
    });
    print("Developer console. Type 'help' for the list of commands.");
}

void RType::ConsoleModule::unload() {
    // Commands may capture objects of the game: drop them with the module.
    _commands.clear();
}

void RType::ConsoleModule::registerCommand(const std::string &name, const std::string &help, ConsoleCommand command) {
    _commands[name] = Command{help, std::move(command)};
}

void RType::ConsoleModule::execute(const std::string &line) {
    std::istringstream stream(line);
    std::vector<std::string> words;

    for (std::string word; stream >> word;)
        words.push_back(word);
    if (words.empty())
        return;
    _typedLines.push_back(line);
    print("> " + line);
    const auto command = _commands.find(words[0]);
    if (command == _commands.end()) {
        print("Unknown command '" + words[0] + "'. Type 'help'.");
        return;
    }
    try {
        std::istringstream output(command->second.run({words.begin() + 1, words.end()}));

        for (std::string outputLine; std::getline(output, outputLine);)
            print(outputLine);
    } catch (const std::exception &exception) {
        print(std::string("Error: ") + exception.what());
    }
}

void RType::ConsoleModule::print(const std::string &line) {
    _history.push_back(line);
    if (_history.size() > MAX_HISTORY)
        _history.erase(_history.begin());
}

const RType::History &RType::ConsoleModule::getHistory() const {
    return _history;
}

const RType::History &RType::ConsoleModule::getTypedLines() const {
    return _typedLines;
}

bool RType::ConsoleModule::isOpen() const {
    return _open;
}

void RType::ConsoleModule::setOpen(bool open) {
    _open = open;
}
