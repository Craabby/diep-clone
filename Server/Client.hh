#pragma once

#include <polynet.hpp>

#include <Shared/Coder/Writer.hh>

struct GameServer;

struct Client
{
    uint32_t camera;
    GameServer *server;
    pn::tcp::Connection socket;
    uint32_t packetIndex = 1;

    Client(GameServer *, pn::tcp::Connection);

    void Delete();
    void Tick();
    void Send(const shared::Writer &);
    bool operator==(const Client &);
};
