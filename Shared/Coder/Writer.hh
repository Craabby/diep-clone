#pragma once

#include <cstddef>
#include <cstdint>
#include <std/string.hh>
#include <std/vector.hh>

namespace shared
{
    // TODO: implicitly cast to Reader
    struct Writer
    {
        std2::Vector<uint8_t> data;

        Writer() = default;
        Writer(const Writer &) = delete;

        Writer &U8(uint8_t value);
        Writer &U16(uint16_t value);
        Writer &U32(uint32_t value);
        Writer &Float(float value);
        Writer &Vu(uint32_t value);
        Writer &Vi(int32_t value);
        Writer &String(const std2::String &string);
        const std2::Vector<uint8_t> &Data() const;
    };
}
