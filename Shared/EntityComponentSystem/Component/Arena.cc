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
        magicTest = 0x12345678;
    }

    DEFINE_COMPONENT_FIELD(uint32_t, Arena, magicTest)

    void Arena::WriteBinary(Writer &writer)
    {
        writer.Vu(*magicTest);
    }

    void Arena::ReadBinary(Reader &reader)
    {
    }
}
