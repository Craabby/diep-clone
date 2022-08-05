#include <iostream>

#include <Server/GameServer.hh>

GameServer::GameServer(Server *server)
    : server(server)
{
    arena = simulation.entityFactory.Create();
    std::cout << "creating game server" << std::endl;
    shared::ecs::Entity &arenaEntity = simulation.entityFactory.Get(arena);
    arenaEntity.arena.emplace(arena);

    std::cout << "listening" << std::endl;
    Listen();
    std::cout << "starting loop" << std::endl;
    RunGameLoop();
}

void GameServer::RunGameLoop()
{
    while (true)
    {
        using namespace std::chrono;
        time_point start = system_clock::now();
        Tick();
        time_point end = system_clock::now();
        duration<double> difference = end - start;
        int64_t deltaTime = (int64_t)duration_cast<microseconds>(difference).count();
        usleep(40'000 - (deltaTime < 40'000 ? deltaTime : 39'999));

        time_point otherEnd = system_clock::now();
        std::cout << std::endl
                  << std::endl
                  << "tick took: " << (double)duration_cast<nanoseconds>(difference).count() / 1'000'000 << " ms" << std::endl
                  << "time elapsed: " << (double)duration_cast<nanoseconds>(duration<double>(otherEnd - start)).count() / 1'000'000 << " ms" << std::endl;
    }
}

void GameServer::Tick()
{
    for (Client &client : clients)
        client.Tick();
    for (shared::ecs::Entity &entity : simulation.entityFactory)
        entity.Reset();
}

void GameServer::Listen()
{
    namespace placeholders = websocketpp::lib::placeholders;
    server->set_open_handler([this](websocketpp::connection_hdl connection)
                             {
        std::cout << "client connected" << std::endl;
        Client client = Client(this, connection);
        clients.push_back(client); 
        
        server->get_con_from_hdl(client.connectionHdl)->set_close_handler([&](websocketpp::connection_hdl)
                              {
            clients.erase(std::find(clients.begin(), clients.end(), client));
            client.Delete();
        }); });
}
