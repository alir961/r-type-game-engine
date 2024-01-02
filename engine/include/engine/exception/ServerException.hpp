/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include <exception>
#include <string>

namespace RType {

    class ServerException : public std::exception {
    public:
        /**
         * Construct an ServerException with reason
         *
         * @param reason exception reason
         */
        explicit ServerException(std::string reason) : _reason(std::move(reason)) {};

        /**
         * Retrieve the exception reason
         *
         * @return reason as a C-style string
         */
        [[nodiscard]] const char *what() const noexcept override {
            return _reason.c_str();
        };

    private:
        std::string _reason;
    };

}
