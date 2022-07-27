#include <iostream>

#include <Shared/Coder/Writer.hh>
#include <Shared/EntityComponentSystem/Entity.hh>
#include <Shared/Simulation.hh>

int main()
{
    shared::Simulation simulation;

    uint32_t entityId = simulation.entityFactory.Create();
    shared::ecs::Entity &entity = simulation.entityFactory.Get(entityId);

    entity.Append<shared::ecs::component::Camera>();

    shared::Writer writer;
    simulation.WriteBinary(writer, &entity.Get<shared::ecs::component::Camera>());
}
