/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include "engine/modules/logger/ILoggerModule.hpp"

namespace RType {

    class LoggerModule : public ILoggerModule {
    private:
        LogLevel _logLevel = DEBUG;

        [[nodiscard]] std::string getTimeString();
        [[nodiscard]] std::string formatMessage(LogLevel level, const std::string &message);

    public:
        void load() override;
        void unload() override;
        
        void setLogLevel(LogLevel level) override;

        void log(LogLevel level, const std::string &message) override;
        void debug(const std::string &message) override;
        void info(const std::string &message) override;
        void warn(const std::string &message) override;
        void error(const std::string &message) override;
    };

}
