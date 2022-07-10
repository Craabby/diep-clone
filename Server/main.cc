#include <iostream>

#include <Shared/EntityComponentSystem/Entity.hh>
#include <Shared/Simulation.hh>

int main()
{
    shared::Simulation simulation;

    uint32_t entityId = simulation.entityFactory.Create();
    shared::ecs::Entity &entity = simulation.entityFactory.Get(entityId);
}
