#include <Simulation.hh>

#include <chrono>
#include <iostream>
#include <thread>

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
}
