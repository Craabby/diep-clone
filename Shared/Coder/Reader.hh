#pragma once

#include <cstddef>
#include <cstdint>
#include <std/string.hh>

namespace shared
{
    struct Writer;

    // TODO: implicitly cast to Writer
    struct Reader
    {
        uint8_t *buffer;
        size_t at = 0;
        size_t size;

        Reader(uint8_t *buffer, size_t size);
        Reader(const Reader &) = delete;

        uint8_t U8();
        uint16_t U16();
        uint32_t U32();
        uint32_t Vu();
        int32_t Vi();
        std2::String String();
        float Float();
        uint8_t operator[](size_t i);
    };
}
