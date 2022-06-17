#include <Simulation.hh>

#include <chrono>
#include <functional>
#include <iostream>
#include <thread>

#include <Coder/Reader.hh>
#include <Coder/Writer.hh>
#include <EntityComponentSystem/Entity.hh>

namespace shared
{
    Simulation::Simulation()
    {
    }

    void Simulation::RunGameLoop()
    {
        while (true)
        {
            using namespace std::chrono_literals;
            Tick();
            std::this_thread::sleep_for(40ms);
        }
    }

    void Simulation::Tick()
    {
    }

    uint32_t Simulation::GetNextId()
    {
        // chose an id
        return (uint32_t)entities.size();
    }

    ecs::Entity *Simulation::CreateEntity()
    {
        ecs::Entity *entity = new ecs::Entity(this);

        entity->id = GetNextId();

        entities.push_back(entity);

        return entity;
    }

    coder::Writer Simulation::WriteBinary(std::function<bool(ecs::Entity *)> isCreation)
    {
        coder::Writer writer;

        writer.Vu(0);

        for (ecs::Entity *entity : entities)
        {
            bool creation = isCreation(entity);

            // the first bit of this value represents if the entity is a creati on
            // it also contains the id bitshifted by one
            // to reduce bandwidth usage
            writer.Vu(creation | (entity->id << 1));

            entity->WriteBinary(writer, creation);
        }

        return writer;
    }
}
