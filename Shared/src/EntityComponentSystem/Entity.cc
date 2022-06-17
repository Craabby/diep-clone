#include <EntityComponentSystem/Entity.hh>

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
}