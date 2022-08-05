#pragma once

#include <websocketpp/server.hpp>

#include <Shared/Coder/Writer.hh>

struct GameServer;

struct Client
{
    uint32_t camera;
    GameServer *server;
    websocketpp::connection_hdl connectionHdl;

    Client(GameServer *, websocketpp::connection_hdl);
    ~Client();

    void Delete();
    void Tick();
    void Send(const shared::Writer &);
    bool operator==(const Client &);
};
