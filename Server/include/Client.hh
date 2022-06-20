#pragma once

#include <vector>

namespace ix
{
    class WebSocket;
}

namespace shared::ecs
{
    class Entity;
}

namespace server
{
    class Simulation;
    class Client
    {
        std::vector<shared::ecs::Entity *> view;
        
    public:
        Simulation *simulation;
        ix::WebSocket *socket;

        Client(Simulation *, ix::WebSocket *);
        void SendUpdate();
    };
}
