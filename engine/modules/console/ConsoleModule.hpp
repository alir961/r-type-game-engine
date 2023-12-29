/*
** EPITECH PROJECT, 2023
** NEWRTYPE
** File description:
** ConsoleModule
*/

#pragma once
#include <engine/modules/IModule.hpp>
#include <vector>
#include <string>

namespace RType {

    class ConsoleModule : public IModule {
    public:
        void load() override;
        void unload() override;

        void addMessage(const std::string& message);
        void setInput(const std::string& input);
        const std::vector<std::string>& getMessages() const;
        const std::string& getInput() const;
    private:
        std::vector<std::string> messages;
        std::string input;
    };
}
