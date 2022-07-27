#pragma once

#include <cstdint>
#include <vector>

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
        static constexpr uint32_t ID = 0;
        bool updated;
        uint32_t ownerId;

        std::vector<uint32_t> view;

        Camera(uint32_t ownerId);

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
