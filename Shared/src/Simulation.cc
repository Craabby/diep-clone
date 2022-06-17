#include <Simulation.hh>

#include <chrono>
#include <iostream>
#include <thread>

#include <EntityComponentSystem/Entity.hh>

namespace shared
{
    Simulation::Simulation()
    {
        RunGameLoop();
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

    ecs::Entity *Simulation::CreateEntity()
    {
        ecs::Entity *entity = new ecs::Entity(this);

        entities.push_back(entity);

        return entity;
    }
}
