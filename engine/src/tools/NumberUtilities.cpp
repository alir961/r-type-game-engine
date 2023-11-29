/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#include "tools/NumberUtilities.hpp"
#include "exception/ServerException.hpp"

int64_t RType::parseToLong(const char *string) {
    char *pointer = nullptr;
    const int64_t parsed = std::strtol(string, &pointer, 10);

    if (string == pointer)
        throw ServerException("Unable to parse long for this string");
    return parsed;
}

u_int64_t RType::parseToUnsignedLong(const char *string) {
    char *pointer = nullptr;
    const u_int64_t parsed = std::strtoul(string, &pointer, 10);

    if (string == pointer)
        throw ServerException("Unable to parse long for this string");
    return parsed;
}
