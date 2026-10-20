/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** ConsoleModule.hpp
*/

#pragma once

#include <map>
#include <string>
#include <vector>
#include "engine/modules/console/IConsoleModule.hpp"

namespace RType {

    using History = std::vector<std::string>;

    /**
     * @brief Command registry with built-in "help" and "clear".
     */
    class ConsoleModule : public IConsoleModule {
    public:
        static constexpr std::size_t MAX_HISTORY = 200;

        void load() override;
        void unload() override;

        void registerCommand(const std::string &name, const std::string &help, ConsoleCommand command) override;
        void execute(const std::string &line) override;
        void print(const std::string &line) override;
        [[nodiscard]] const History &getHistory() const override;
        [[nodiscard]] const History &getTypedLines() const override;
        [[nodiscard]] bool isOpen() const override;
        void setOpen(bool open) override;

    private:
        struct Command {
            std::string help;
            ConsoleCommand run;
        };

        std::map<std::string, Command> _commands;
        History _history;
        History _typedLines;
        bool _open = false;
    };
}
