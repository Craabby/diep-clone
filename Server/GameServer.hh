#pragma once

#include <vector>

#include <polynet.hpp>

#include <Server/Client.hh>
#include <Shared/Simulation.hh>

struct GameServer
{
    uint32_t arena;
    pn::tcp::Server &server;
    std::vector<Client> clients;
    shared::Simulation simulation;

    GameServer(pn::tcp::Server &);
    GameServer(const GameServer &) = delete;

    void Tick();
    void RunGameLoop();
    void Listen();
};
