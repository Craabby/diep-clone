#pragma once
#include <Simulation.hh>

namespace server
{
    class Simulation : public shared::Simulation
    {
    public:
        Simulation();

        void RunGameLoop();
    };
}
