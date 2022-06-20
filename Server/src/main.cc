#include <cstdint>
#include <iostream>

#include <IXHttp.h>
#include <IXWebSocketServer.h>

#include <Coder/Writer.hh>
#include <Coder/Reader.hh>
#include <EntityComponentSystem/Entity.hh>
#include <EntityComponentSystem/Component/Physics.hh>
#include <ServerSimulation.hh>

int32_t main()
{
    server::Simulation simulation;
    // server::Simulation simulation2;

    // shared::ecs::Entity *entityTest = simulation.CreateEntity();
    // std::cout << entityTest->id << std::endl;
    // entityTest->AppendComponent<shared::ecs::component::Physics>();
    // entityTest->Get<shared::ecs::component::Physics>().position.X(1000);

    // shared::coder::Writer writer = simulation.WriteBinary([](shared::ecs::Entity *)
    //                                                       { return false; });
    // stuff(writer);

    ix::WebSocketServer server(8001);

    server.setOnClientMessageCallback([&](std::shared_ptr<ix::ConnectionState> connectionState, ix::WebSocket &webSocket, const ix::WebSocketMessagePtr &msg)
                                          {
        std::cout << static_cast<uint32_t>(msg->type) << std::endl;
        webSocket.disableAutomaticReconnection();
        if (msg->type == ix::WebSocketMessageType::Open)
        {
            simulation.AddClient(&webSocket);
            std::cout << "new websocket created" << std::endl;
            shared::ecs::Entity *entity = simulation.CreateEntity();
        } 
        else if (msg->type == ix::WebSocketMessageType::Close)
        {
            std::cout << "socket closed" << std::endl;
            simulation.DeleteClient(&webSocket);
        } });

    server.listen();
    server.start();

    simulation.RunGameLoop();

    pause();
}
