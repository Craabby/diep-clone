#include <iostream>

#include <Shared/Coder/Writer.hh>
#include <Shared/EntityComponentSystem/Entity.hh>
#include <Shared/Simulation.hh>

using namespace shared::ecs::component;

shared::Simulation simulation;

uint32_t entityId = simulation.entityFactory.Create();
uint32_t entityId2 = simulation.entityFactory.Create();
shared::ecs::Entity &entity = simulation.entityFactory.Get(entityId);
shared::ecs::Entity &entity2 = simulation.entityFactory.Get(entityId2);

void Tick()
{
    shared::Writer writer;
    simulation.WriteBinary(writer, &entity.Get<Camera>());

    for (uint8_t x : writer.Data())
        std::cout << std::to_string(x) << " ";

    std::cout << std::endl;
    entity.Reset();
    entity2.Reset();
}

int main()
{
    entity.Append<Camera>();
    entity2.Append<Physics>();

    Physics &p = entity2.Get<Physics>();
    p.X(1000);
    p.Y(2000);

    Tick();
    Tick();
    p.X(p.X() + 1);
    Tick();
    Tick();
}
