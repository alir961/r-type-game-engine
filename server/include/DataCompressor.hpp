/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** my_r-type
*/

#pragma once

#include <iostream>
#include "compression/IDataCompression.hpp"

namespace RType {

    class DataCompressor {
    private:
        IDataCompression *compressionAlgorithm;

    public:
        DataCompressor(IDataCompression *algo) : compressionAlgorithm(algo) {}

        std::string compressData(const std::string &data) {
            return compressionAlgorithm->compress(data);
        }

        std::string decompressData(const std::string &compressedData) {
            return compressionAlgorithm->decompress(compressedData);
        }
    };
}