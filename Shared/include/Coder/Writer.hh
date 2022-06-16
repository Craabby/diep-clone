#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace shared::coder
{
    class Writer
    {
        std::vector<uint8_t> data;

    public:
        Writer &U8(uint8_t value);
        Writer &U16(uint16_t value);
        Writer &U32(uint32_t value);
        Writer &Float(float value);
        Writer &Vu(uint32_t value);
        Writer &Vi(int32_t value);
        Writer &String(const std::string &string);
        const std::vector<uint8_t> &Data() const;
    };
}
