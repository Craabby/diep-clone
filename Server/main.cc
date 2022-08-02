#include <iostream>
#include <optional>

#include <Shared/Coder/Reader.hh>
#include <Shared/Coder/Writer.hh>
#include <Shared/EntityComponentSystem/Entity.hh>
#include <Shared/Simulation.hh>

using namespace shared::ecs::component;

struct GameSimulation
{
    shared::Simulation simulation;
};

GameSimulation simulation{};
shared::Simulation clientSimulation{};

shared::Factory<shared::ecs::Entity> &entities = simulation.simulation.entityFactory;
uint32_t entityId = entities.Create();
uint32_t entityId2 = entities.Create();
shared::ecs::Entity &entity = entities.Get(entityId);
shared::ecs::Entity &entity2 = entities.Get(entityId2);

void Tick()
{
    shared::Writer writer;
    simulation.simulation.WriteBinary(writer, &*entity.camera);

    for (uint8_t x : writer.Data())
        std::cout << std::to_string(x) << " ";

    std::cout << std::endl;

    shared::Reader reader = writer;
    clientSimulation.ReadBinary(reader);

    std::cout << *entity2.physics->y << " " << *clientSimulation.entityFactory.Get(1).physics->y << std::endl;

    entity.Reset();
    entity2.Reset();
}

int main()
{
        std::cout << sizeof(GameSimulation) << std::endl;

        entity.camera.emplace(entityId);
        entity2.physics.emplace(entityId2);

        Physics &p = *entity2.physics;
        p.x = 1000;
        p.y = 2000;

        Tick();
        Tick();
        p.x += 1;
        p.y += 100;
        Tick();
        p.x += 1;
        p.y += 100;
        Tick();
        p.x += 1;
        p.y += 100;
        Tick();
        p.x += 1;
        p.y += 100;
        Tick();
        Tick();

        entity.~Entity();
        entity2.~Entity();
}
