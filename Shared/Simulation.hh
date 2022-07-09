#pragma once

#include <Shared/Factory.hh>
#include <Shared/EntityComponentSystem/Entity.hh>

namespace shared
{
    class Simulation
    {
        void Tick();

    public:
        static constexpr uint32_t MAX_ITEMS = 256;

        Factory<ecs::Entity> entityFactory;
        uint32_t id;

        Simulation();
        void RunGameLoop();
    };
}
