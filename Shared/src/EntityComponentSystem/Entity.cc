#include <EntityComponentSystem/Entity.hh>

#include <Coder/Reader.hh>
#include <Coder/Writer.hh>
#include <EntityComponentSystem/Component/Basic.hh>
#include <EntityComponentSystem/Component/Physics.hh>
#include <EntityComponentSystem/Component/Types.hh>

template <shared::ecs::component::types::component Component>
inline void DeleteComponent(shared::ecs::Entity *entity)
{
    if (entity->Has<Component>())
        delete &entity->Get<Component>();
}

namespace shared::ecs
{
    Entity::Entity(Simulation *simulation)
        : simulation(simulation)
    {
    }

    Entity::~Entity()
    {
        DeleteComponent<component::Basic>(this);
        DeleteComponent<component::Physics>(this);
    }

    void Entity::WriteComponents(coder::Writer &writer)
    {
        if (Has<component::Basic>())
            Get<component::Basic>().WriteBinary(writer);
        if (Has<component::Physics>())
            Get<component::Physics>().WriteBinary(writer);
    }

    void Entity::WriteBinaryCreation(coder::Writer &writer)
    {
        uint32_t componentFlags = 0;

        componentFlags |= Has<component::Basic>() << component::Basic::ID;
        componentFlags |= Has<component::Physics>() << component::Physics::ID;

        writer.Vu(componentFlags);

        WriteComponents(writer);
    }

    void Entity::WriteBinaryUpdate(coder::Writer &writer)
    {
        WriteComponents(writer);
    }

    void Entity::ReadComponents(coder::Reader &reader)
    {
        if (Has<component::Basic>())
            Get<component::Basic>().FromBinary(reader);
        if (Has<component::Physics>())
            Get<component::Physics>().FromBinary(reader);
    }

    void Entity::FromBinaryCreation(coder::Reader &reader)
    {
        uint32_t componentFlags = reader.Vu();
        if (componentFlags & (1 << component::Basic::ID))
            AppendComponent<component::Basic>();
        if (componentFlags & (1 << component::Physics::ID))
            AppendComponent<component::Physics>();

        ReadComponents(reader);
    }

    void Entity::FromBinaryUpdate(coder::Reader &reader)
    {
        ReadComponents(reader);
    }
}
