#include <cstdint>
#include <iostream>

#include <IXHttp.h>
#include <IXWebSocketServer.h>

#include <Coder/Writer.hh>
#include <Coder/Reader.hh>
#include <EntityComponentSystem/Entity.hh>
#include <EntityComponentSystem/Component/Physics.hh>
#include <ServerSimulation.hh>

void stuff(const shared::coder::Writer &thing)
{
    for (uint8_t a : thing.Data())
        std::cout << std::to_string(a) << " ";
    std::cout << std::endl;
}

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
        webSocket.sendBinary(ix::IXWebSocketSendData(std::vector<uint8_t>{32, 32, 32, 32, 33}));
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
