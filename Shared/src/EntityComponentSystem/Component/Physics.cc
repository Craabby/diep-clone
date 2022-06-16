#include <EntityComponentSystem/Component/Physics.hh>

#include <EntityComponentSystem/Entity.hh>

namespace shared::ecs::component
{
    Physics::Physics(Entity *entity)
        : entity(entity)
    {
    }
}
