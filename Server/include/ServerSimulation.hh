#pragma once
#include <Simulation.hh>

namespace ix
{
    class WebSocket;
}
namespace server
{
    class Client;

    class Simulation : public shared::Simulation
    {
    public:
        std::vector<Client *> clients;

        Simulation();

        void AddClient(ix::WebSocket *);
        void DeleteClient(ix::WebSocket *);
        void RunGameLoop();
        void Tick();
        void SendUpdate();
    };
}
