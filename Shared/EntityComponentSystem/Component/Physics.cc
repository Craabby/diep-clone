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

    DEFINE_COMPONENT_FIELD(float, Physics, x)
    DEFINE_COMPONENT_FIELD(float, Physics, y)

    void Physics::WriteBinary(Writer &writer)
    {
        writer.Float(*x);
        writer.Float(*y);
    }

    void Physics::ReadBinary(Reader &reader)
    {
        x = reader.Float();
        y = reader.Float();
    }
}
