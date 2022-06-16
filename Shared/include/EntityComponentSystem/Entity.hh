#pragma once

namespace shared
{
    class Simulation;
}

namespace shared::ecs
{
    class Entity
    {
        Simulation *simulation;

    public:
        Entity(Simulation *);
    };
}