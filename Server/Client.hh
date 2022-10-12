#pragma once

#include <polynet.hpp>

#include <Shared/Coder/Writer.hh>

struct GameServer;

struct Client
{
    uint32_t camera;
    uint32_t packetIndex = 1;
    GameServer *server;
    pn::tcp::Connection socket;

    Client(GameServer *, pn::tcp::Connection &&);
    ~Client();

    bool Connected();
    void Tick();
    int32_t Send(const shared::Writer &);
    bool operator==(const Client &);
};
