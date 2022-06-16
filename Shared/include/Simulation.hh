#pragma once

#include <vector>

namespace shared
{
    namespace ecs
    {
        class Entity;
    }

    class Simulation
    {
        std::vector<ecs::Entity *> entities;

    public:
        Simulation();
    };
}