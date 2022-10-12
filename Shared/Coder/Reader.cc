#include <Shared/Coder/Reader.hh>

#include <std2/string.hh>

#include <Shared/Coder/Writer.hh>

namespace shared
{
    Reader::Reader(uint8_t *buffer, size_t size)
        : buffer(buffer),
          size(size)
    {
    }

    uint8_t Reader::U8()
    {
        uint8_t value = (*this)[at];
        at++;
        return value;
    }

    uint16_t Reader::U16()
    {
        uint16_t value = U8() | U8() << 8;
        return value;
    }

    uint32_t Reader::U32()
    {
        uint32_t value = U16() | U16() << 16;
        return value;
    }

    uint32_t Reader::Vu()
    {
        uint32_t out = 0;
        uint32_t i = 0;

        while ((*this)[at] & 0x80)
        {
            out |= (U8() & 0x7f) << i;
            i += 7;
        }
        out |= (U8() & 0x7f) << i;

        return out;
    }

    int32_t Reader::Vi()
    {
        uint32_t out = Vu();
        return (0 - (out & 1)) ^ (out >> 1);
    }

    float Reader::Float()
    {
        uint32_t uint32Value = U32();
        return *(float *)&uint32Value;
    }

    std2::String Reader::String()
    {
        std2::String string;
        while ((*this)[at] != 0)
        {
            string += (*this)[at];
            at++;
        };

        return string;
    }

    uint8_t Reader::operator[](size_t i)
    {
        if (i > size)
            return 0;
        return buffer[i];
    }
}