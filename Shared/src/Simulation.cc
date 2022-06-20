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

    void Simulation::WriteBinary(coder::Writer &writer, std::function<EntityUpdateType(ecs::Entity *)> updateTypeOf)
    {
        using ecs::Entity;
        std::vector<Entity *> deletions;
        std::vector<Entity *> updates;
        std::vector<Entity *> creations;

        for (Entity *entity : entities)
        {
            EntityUpdateType updateType = updateTypeOf(entity);

            if (updateType == EntityUpdateType::Deleted)
                deletions.push_back(entity);
            if (updateType == EntityUpdateType::Updated)
                updates.push_back(entity);
            if (updateType == EntityUpdateType::Created)
                creations.push_back(entity);
        }

        for (Entity *entity : deletions)
            writer.Vu(entity->id);
        writer.U8(0);
        for (Entity *entity : updates)
        {
            writer.Vu(entity->id);
            entity->WriteBinary<false>(writer);
        }
        writer.U8(0);
        for (Entity *entity : creations)
        {
            writer.Vu(entity->id);
            entity->WriteBinary<true>(writer);
        }
        writer.U8(0);
    }

    void Simulation::FromBinary(coder::Reader &reader)
    {
        using ecs::Entity;

        // deletions
        while (true)
        {
            uint32_t id = reader.Vu();
            if (id == 0)
                break;
            entities.erase(std::find_if(entities.begin(), entities.end(), [id](Entity *entity)
                                        { return entity->id == id; }));
        }

        // updates
        while (true)
        {
            uint32_t id = reader.Vu();
            if (id == 0)
                break;
            
            (*std::find_if(entities.begin(), entities.end(), [id](Entity *entity)
                                        { return entity->id == id; }))->FromBinary<false>(reader);
        }

        // creations
        while (true)
        {
            uint32_t id = reader.Vu();
            if (id == 0)
                break;
            
            // i love heap allocation :D
            Entity *entity = new Entity(this);
            entity->id = id;
            nextId = id;
            entities.push_back(entity);
            entity->FromBinary<true>(reader);
        }
    }
}
