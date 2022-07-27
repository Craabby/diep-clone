#include <Shared/EntityComponentSystem/Component/Physics.hh>

#include <Shared/Coder/Reader.hh>
#include <Shared/Coder/Writer.hh>
#include <Shared/EntityComponentSystem/Component/Types.hh>

namespace shared::ecs::component
{
    Physics::Physics(uint32_t ownerId)
        : ownerId(ownerId),
          updated(true)
    {
    }

    DEFINE_COMPONENT_FIELD(float, Physics, X)
    DEFINE_COMPONENT_FIELD(float, Physics, Y)

    // float Physics::X()
    // {
    //     return m_X;
    // }

    // float Physics::Y()
    // {
    //     return m_Y;
    // }

    // float Physics::X(float x)
    // {
    //     m_X = x;
    //     updated = true;
    //     return x;
    // }

    // float Physics::Y(float y)
    // {
    //     m_Y = y;
    //     updated = true;
    //     return y;
    // }

    void Physics::WriteBinary(Writer &writer)
    {
        writer.Float(X());
        writer.Float(Y());
    }

    void Physics::ReadBinary(Reader &reader)
    {
        X(reader.Float());
        Y(reader.Float());
    }
}
