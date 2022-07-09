#include <iostream>

#include <Shared/Simulation.hh>

int main()
{
    shared::Factory<shared::Simulation> simulations;
    uint32_t simulation = simulations.Create();
    simulations.Get(simulation)->RunGameLoop();
    
}
