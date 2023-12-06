/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include <iostream>

namespace RType {

    class IDataCompression {
    public:
        virtual std::string compress(const std::string &data) = 0;
        virtual std::string decompress(const std::string &compressedData) = 0;
        virtual ~IDataCompression() = default;
        IDataCompression(const IDataCompression&) = delete;
        IDataCompression& operator=(const IDataCompression&) = delete;
        IDataCompression(IDataCompression&&) = default;
        IDataCompression& operator=(IDataCompression&&) = default;
    protected:
        IDataCompression() = default;
    };
}
