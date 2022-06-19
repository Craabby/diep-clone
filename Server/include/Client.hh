#pragma once

namespace ix
{
    class WebSocket;
}

namespace server
{
    class Simulation;
    class Client
    {
    public:
        Simulation *simulation;

        Client(ix::WebSocket *);
        void SendUpdate();
    };
}
