#include <EntityComponentSystem/Component/Physics.hh>

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
}
