/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#include <iostream>
#include <ctime>
#include <sstream>
#include <iomanip>
#include "LoggerModule.hpp"

extern "C" {
RType::IModule *initializeLoggerModule() {
    return new RType::LoggerModule();
}

void destroy(RType::LoggerModule *library) {
    delete library;
}
}

void RType::LoggerModule::load() {}

void RType::LoggerModule::unload() {}

void RType::LoggerModule::setLogLevel(RType::LogLevel level) {
    _logLevel = level;
}

void RType::LoggerModule::log(RType::LogLevel level, const std::string &message) {
    if (level < _logLevel)
        return;
    std::string displayLog = formatMessage(level, message);

    if (level >= WARN)
        std::cerr << displayLog << "\n";
    else std::cout << displayLog << "\n";
}

void RType::LoggerModule::debug(const std::string &message) {
    log(DEBUG, message);
}

void RType::LoggerModule::info(const std::string &message) {
    log(INFO, message);
}

void RType::LoggerModule::warn(const std::string &message) {
    log(WARN, message);
}

void RType::LoggerModule::error(const std::string &message) {
    log(ERROR, message);
}

std::string RType::LoggerModule::getTimeString() {
    std::time_t now = std::time(nullptr);
    std::tm *localTime = std::localtime(&now);
    std::ostringstream oss;

    oss << std::put_time(localTime, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

std::string RType::LoggerModule::formatMessage(RType::LogLevel level, const std::string &message) {
    std::string prefix;
    if (level == DEBUG) prefix = "\e[1;37m[DEBUG]\e[0m";
    if (level == INFO) prefix = "\e[1;0m[INFO]\e[0m";
    if (level == WARN) prefix = "\e[1;33m[WARN]\e[0m";
    if (level == ERROR) prefix = "\e[1;31m[ERROR]\e[0m";

    return ("(" + getTimeString() + ") " + prefix + ": " + message);
}
