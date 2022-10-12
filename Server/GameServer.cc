#include <Server/GameServer.hh>

#include <iostream>
#include <thread>
#include <std2/move.hh>

#include <polynet.hpp>

GameServer::GameServer(pn::tcp::Server &server)
    : server(server)
{
    arena = simulation.entityFactory.Create();
    shared::ecs::Entity &arenaEntity = simulation.entityFactory.Get(arena);
    arenaEntity.arena.Emplace(arena);
    arenaEntity.arena->mapSize = 8500;

    Listen();
    RunGameLoop();
}

void GameServer::RunGameLoop()
{
    while (true)
    {
        // using namespace std::chrono;
        // time_point start = system_clock::now();
        Tick();
        // time_point end = system_clock::now();
        // duration<double> difference = end - start;
        // int64_t deltaTime = (int64_t)duration_cast<microseconds>(difference).count();
        usleep(40'000 /* - (deltaTime < 40'000 ? deltaTime : 39'999)*/);
    }
}

void GameServer::Tick()
{
    for (std2::size_t i = 0; i < clients.Size(); i++)
    {
        Client &client = clients.At(i);
        if (!client.Connected())
        {
            std::cout << "client deleted\n";
            clients.Erase<true>(i);
        }
    }
    for (shared::ecs::Entity &entity : simulation.entityFactory)
        entity.Tick();
    for (Client &client : clients)
        client.Tick();
    for (shared::ecs::Entity &entity : simulation.entityFactory)
        entity.Reset();
}

void GameServer::Listen()
{
    std::thread([&]()
                { Assert(!server.listen([&](pn::tcp::Connection &socket, void *)
                                        { 
            std::cout << "client connected" << std::endl;
            clients.Emplace(this, std2::Move(socket));

            return true; })); })
        .detach();
    // server->set_open_handler([this](websocketpp::connection_hdl connection)
    //                          {
    //     std::cout << "client connected" << std::endl;

    //     server->get_con_from_hdl(clients.emplace_back(this, connection).connectionHdl)->set_close_handler([&](websocketpp::connection_hdl connection)
    //                           {
    //         std::cout << "client destroyed" << std::endl;
    //         auto clientIterator = std::find_if(clients.begin(), clients.end(), [&](Client &a)
    //         { return server->get_con_from_hdl(a.connectionHdl) == server->get_con_from_hdl(connection); });
    //         clientIterator->Delete();
    //         clients.erase(clientIterator);
    //     }); });
}
