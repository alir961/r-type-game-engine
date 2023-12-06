/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include <iostream>

#include "IDataCompression.hpp"

namespace RType {

    class LZ4Algorithm : public IDataCompression {
    public:
        std::string compress(const std::string &data) override;
        std::string decompress(const std::string &compressedData) override;
    };

}
