#pragma once

#include <cstddef>
#include <cstdint>
#include <string>

namespace shared::coder
{
    class Reader
    {
    public:
        size_t at = 0;
        size_t size;
        uint8_t *buffer;

        Reader(uint8_t *buffer, size_t size);

        uint8_t U8();
        uint16_t U16();
        uint32_t U32();
        uint32_t Vu();
        int32_t Vi();
        std::string String();
        float Float();
        uint8_t operator[](size_t i);
    };
}