/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include <iostream>
#include <bitset>

namespace RType {

    class BinaryEncoder {
    private:
        static char binaryToChar(const std::bitset<8> binaryChunk) {
            return static_cast<char>(binaryChunk.to_ulong());
        }
    };

}
