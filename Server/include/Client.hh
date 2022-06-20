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
        shared::ecs::Entity *camera;
        std::vector<shared::ecs::Entity *> view;
        std::vector<shared::ecs::Entity *> FindEntitiesInView();

    public:
        Simulation *simulation;
        ix::WebSocket *socket;

        Client(Simulation *, ix::WebSocket *);
        ~Client();
        void SendUpdate();
    };
}
