/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** my_rtype
*/

#include "../../include/engine/tools/Split.hpp"

std::vector<std::string> RType::Split::split(const std::string &str, const std::string &separators)
{
    (void) separators;
    std::string tmp;
    std::vector<std::string> result;
    for (std::size_t i = 0; i < str.size(); i++) {
        if (isSeparator(str[i], separators)) {
            for (; i < str.size() && isSeparator(str[i], separators); i++);
            if (!tmp.empty())
                result.push_back(tmp);
            tmp.clear();
            i--;
        } else
            tmp += str[i];
    }
    if (!tmp.empty())
        result.push_back(tmp);
    return result;
}

bool RType::Split::isSeparator(const char c, const std::string &separators)
{
    for (std::size_t i = 0; i < separators.size(); i++)
        if (separators[i] == c)
            return true;
    return false;
}
