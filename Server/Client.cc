#include <Server/Client.hh>

#include <Server/GameServer.hh>

Client::Client(GameServer *server, websocketpp::connection_hdl connectionHdl)
    : server(server),
      connectionHdl(connectionHdl),
      camera(server->simulation.entityFactory.Create())
{
}

Client::~Client()
{
}

void Client::Tick()
{
    shared::Writer writer;
    writer.U8(0);
    server->simulation.WriteBinary(writer, &*server->simulation.entityFactory.Get(camera).camera);

    Send(writer);
}

void Client::Delete()
{
}

void Client::Send(const shared::Writer &writer)
{
    server->server->get_con_from_hdl(connectionHdl)->send((void *)writer.Data().data(), writer.Data().size(), websocketpp::frame::opcode::value::binary);
}
