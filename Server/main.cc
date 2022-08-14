#include <iostream>
#include <thread>
#include <cfenv>

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include <Server/GameServer.hh>
#include <Shared/Util.hh>

using Server = websocketpp::server<websocketpp::config::asio>;

int main()
{
    feenableexcept(shared::GetFloatExceptionFlags());

    Server *server = new Server;
    std::thread([server]()
                {
        server->set_access_channels(websocketpp::log::alevel::none);
        server->clear_access_channels(websocketpp::log::alevel::none);
        server->init_asio();
        server->listen(28623);
        server->set_max_message_size(1024);
        server->start_accept();
        server->run(); })
        .detach();
    
    std::thread([server]()
                { GameServer gameServer(server); })
        .join();
}
