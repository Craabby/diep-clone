#include <EntityComponentSystem/Component/Basic.hh>

#include <Coder/Writer.hh>
#include <EntityComponentSystem/Entity.hh>

namespace shared::ecs::component
{
    Basic::Basic(Entity *entity)
        : entity(entity)
    {
    }

    void Basic::WriteBinary(coder::Writer &writer)
    {
    }
}
