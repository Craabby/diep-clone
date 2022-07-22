#pragma once

#include <cstdint>

namespace shared
{
    class Writer;
    class Reader;
}

namespace shared::ecs::component
{
    class Camera
    {
        float m_X = 0;
        float m_Y = 0;
        float m_Fov = 1;

    public:
        static constexpr uint32_t ID = 1;

        uint32_t ownerId;

        float X();
        float X(float);
        float Y();
        float Y(float);
        float Fov();
        float Fov(float);

        void WriteBinary(Writer &);
        void ReadBinary(Reader &);
    };
}
