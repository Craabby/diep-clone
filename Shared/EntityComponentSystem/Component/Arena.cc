#include <Shared/EntityComponentSystem/Component/Arena.hh>

#include <Shared/Coder/Reader.hh>
#include <Shared/Coder/Writer.hh>
#include <Shared/EntityComponentSystem/Component/Types.hh>

namespace shared::ecs::component
{
    Arena::Arena(uint32_t ownerId)
        : ownerId(ownerId),
          updated(true)
    {
    }

    void Arena::WriteBinary(Writer &writer)
    {
    }

    void Arena::ReadBinary(Reader &reader)
    {
    }
}
