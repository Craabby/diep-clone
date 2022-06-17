#include <cstdint>
#include <iostream>

#include <IXHttp.h>
#include <IXWebSocketServer.h>

#include <ServerSimulation.hh>

int32_t main()
{
    server::Simulation simulation;
    ix::WebSocketServer server(8001);

    server.setOnClientMessageCallback([&](std::shared_ptr<ix::ConnectionState> connectionState, ix::WebSocket &webSocket, const ix::WebSocketMessagePtr &msg)
                                      { 
        std::cout << "client did something" << std::endl; 
        webSocket.disableAutomaticReconnection();
        if (msg->type == ix::WebSocketMessageType::Open)
        {
            std::cout << "new websocket created" << std::endl;
            shared::ecs::Entity *entity = simulation.CreateEntity();
        } });


    server.listen();
    server.start();

    pause();
}
