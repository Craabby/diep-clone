#include <ServerSimulation.hh>

#include <iostream>
#include <thread>

#include <IXWebSocket.h>

#include <Client.hh>

namespace server
{
    Simulation::Simulation()
    {
    }

    void Simulation::AddClient(ix::WebSocket *socket)
    {
        clients.push_back(new Client(this, socket));
    }

    void Simulation::DeleteClient(ix::WebSocket *socket)
    {
        // i hate iterators
        Client *client = nullptr;
        size_t i = 0;
        for (; i < clients.size(); i++)
            if (clients.at(i)->socket == socket)
            {
                client = clients.at(i);
                break;
            }
        clients.erase(clients.begin() + i);
        delete client;
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
        shared::Simulation::Tick();

        SendUpdate();
    }

    void Simulation::SendUpdate()
    {
        for (Client *client : clients)
            client->SendUpdate();
    }
}
