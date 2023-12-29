/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once
#include <engine/modules/IModule.hpp>
#include <vector>
#include <string>

namespace RType {

    using History = std::vector<std::string>;

    class ConsoleModule : public IModule {
    public:
        void load() override;
        void unload() override;

        /**
         * @brief Adds a message to the console history.
         * @param message The message to add to the history.
         */
        void addToHistory(const std::string& message);

        /**
         * @brief Sets the current input for the console.
         * @param input The input to set for the console.
         */
        void setInput(const std::string& input);

        /**
         * @brief Gets the console history.
         * @return A const reference to the console history.
         */
        [[nodiscard]] const History& getHistory() const;

        /**
         * @brief Gets the current input for the console.
         * @return A const reference to the current input.
         */
        [[nodiscard]] const std::string& getInput() const;
    private:
        History _history;
        std::string _input;
    };
}
