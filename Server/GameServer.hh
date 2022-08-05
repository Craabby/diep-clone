#pragma once

#include <vector>

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include <Server/Client.hh>
#include <Shared/Simulation.hh>

using Server = websocketpp::server<websocketpp::config::asio>;

struct GameServer
{
    uint32_t arena;
    Server *server;
    std::vector<Client *> clients;
    shared::Simulation simulation;

    GameServer(Server *);
    GameServer(const GameServer &) = delete;

    void Tick();
    void RunGameLoop();
    void Listen();
};
