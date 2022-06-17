#include <Simulation.hh>

#include <algorithm>
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
        nextId++;
        return nextId;
    }

    ecs::Entity *Simulation::CreateEntity()
    {
        ecs::Entity *entity = new ecs::Entity(this);

        entity->id = GetNextId();

        entities.push_back(entity);

        return entity;
    }

    void Simulation::DestroyEntity(ecs::Entity *entity)
    {
        entities.erase(std::find(entities.begin(), entities.end(), entity));
        delete entity;
    }

    coder::Writer Simulation::WriteBinary(std::function<bool(ecs::Entity *)> isCreation)
    {
        coder::Writer writer;

        for (ecs::Entity *entity : entities)
        {
            bool creation = isCreation(entity);

            // the first bit of this value represents if the entity is a creati on
            // it also contains the id bitshifted by one
            // to reduce bandwidth usage
            writer.Vu(creation | (entity->id << 1));

            entity->WriteBinary(writer, creation);
        }

        writer.Vu(0);

        return writer;
    }

    void Simulation::FromBinary(coder::Reader &reader)
    {
        while (true)
        {
            uint32_t idAndCreation = reader.Vu();
            if (idAndCreation == 0)
                break;
            uint32_t id = idAndCreation >> 1;
            bool creation = idAndCreation & 1;
            ecs::Entity *entity = new ecs::Entity(this);
            entity->id = id;
            nextId = id;
            entities.push_back(entity);

            entity->FromBinary(reader, creation);
        }
    }
}
