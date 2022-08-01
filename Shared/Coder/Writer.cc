#include <Shared/Coder/Writer.hh>

#include <vector>

namespace shared
{
    const std::vector<uint8_t> &Writer::Data() const
    {
        return data;
    }

    Writer &Writer::U8(uint8_t value)
    {
        data.push_back(value);

        return *this;
    }

    Writer &Writer::U16(uint16_t value)
    {
        U8(value);
        U8(value >> 8);

        return *this;
    }

    Writer &Writer::U32(uint32_t value)
    {
        U8(value);
        U8(value >> 8);
        U8(value >> 16);
        U8(value >> 24);

        return *this;
    }

    Writer &Writer::Float(float value)
    {
        U32(*(uint32_t *)&value);

        return *this;
    }

    Writer &Writer::Vu(uint32_t value)
    {
        do
        {
            uint32_t byte = value & 255;
            value >>= 7;
            if (value != 0)
                byte |= 128;
            U8(byte);
        } while (value);

        return *this;
    }

    Writer &Writer::Vi(int32_t value)
    {
        Vu((0 - (value < 0)) ^ (value << 1));

        return *this;
    }

    Writer &Writer::String(const std::string &value)
    {
        for (size_t i = 0; i < value.size(); i++)
            U8(value.at(i));
        U8(0);

        return *this;
    }
}