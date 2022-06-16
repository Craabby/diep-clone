#include <EntityComponentSystem/Entity.hh>

namespace shared::ecs
{
    Entity::Entity(Simulation *simulation)
        : simulation(simulation)
    {
    }
}