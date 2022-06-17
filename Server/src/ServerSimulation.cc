#include <ServerSimulation.hh>

#include <thread>

namespace server
{
    Simulation::Simulation()
    {
    }

    void Simulation::RunGameLoop()
    {
        std::thread([this](){
            this->shared::Simulation::RunGameLoop();
        }).detach();
    }
}
