/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include "engine/modules/IModule.hpp"

namespace RType {

    enum LogLevel {
        DEBUG, INFO, WARN, ERROR
    };

    class ILoggerModule : public IModule {
    public:
        virtual void load() = 0;
        virtual void unload() = 0;

        virtual void setLogLevel(LogLevel level) = 0;

        virtual void log(LogLevel log, const std::string &message) = 0;
        virtual void debug(const std::string &message) = 0;
        virtual void info(const std::string &message) = 0;
        virtual void warn(const std::string &message) = 0;
        virtual void error(const std::string &message) = 0;
    };

}
