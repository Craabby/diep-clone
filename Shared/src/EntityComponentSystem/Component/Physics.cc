#include <EntityComponentSystem/Component/Physics.hh>

#include <Coder/Reader.hh>
#include <Coder/Writer.hh>
#include <EntityComponentSystem/Entity.hh>

namespace shared::ecs::component
{
    Physics::Physics(Entity *entity)
        : entity(entity)
    {
    }

    void Physics::WriteBinary(coder::Writer &writer)
    {
        writer.Vu(position.X());
        writer.Vu(position.Y());
    }

    void Physics::FromBinary(coder::Reader &reader)
    {
        position.X(reader.Vu());
        position.Y(reader.Vu());
    }
}
