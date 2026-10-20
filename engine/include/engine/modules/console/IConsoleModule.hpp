/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** IConsoleModule.hpp
*/

#pragma once

#include <functional>
#include <string>
#include <vector>
#include "engine/modules/IModule.hpp"

namespace RType {

    /**
     * @brief A console command: receives the words after its name, returns what to print.
     */
    using ConsoleCommand = std::function<std::string(const std::vector<std::string> &args)>;

    /**
     * @brief In-game developer console: a command registry with a history.
     *
     * The game registers its commands and draws the console; the module parses and runs them.
     */
    class IConsoleModule : public IModule {
    public:
        void load() override = 0;
        void unload() override = 0;

        virtual void registerCommand(const std::string &name, const std::string &help, ConsoleCommand command) = 0;

        /**
         * @brief Run a command line and print it with its output.
         */
        virtual void execute(const std::string &line) = 0;

        virtual void print(const std::string &line) = 0;

        [[nodiscard]] virtual const std::vector<std::string> &getHistory() const = 0;

        /**
         * @brief Previously typed command lines, oldest first (for ↑ / ↓).
         */
        [[nodiscard]] virtual const std::vector<std::string> &getTypedLines() const = 0;

        [[nodiscard]] virtual bool isOpen() const = 0;

        virtual void setOpen(bool open) = 0;
    };

}
