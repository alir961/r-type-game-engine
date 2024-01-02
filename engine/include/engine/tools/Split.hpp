/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** my_rtype
*/

#pragma once

#include "vector"
#include "iostream"

namespace RType {
    class Split {
    public:
        Split() = default;
        ~Split() = default;
        static std::vector<std::string> split(const std::string &str, const std::string &separators);
        static bool isSeparator(const char c, const std::string &separators);
    };
}
