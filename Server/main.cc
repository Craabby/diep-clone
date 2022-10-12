#define STD2_OPTIONAL_SAFE
#define STD2_VECTOR_SAFE

#include <cstdlib>

#include <std/cstdint.hh>

#include <polynet.hpp>
#include <Server/GameServer.hh>

// uint32_t packetIndex = 1;

// void Send(pn::tcp::Connection &connection, uint32_t size, const char *data)
// {
// 	char *packet = new char[size + 8];
// 	*(uint32_t *)packet = packetIndex;
// 	*(uint32_t *)&packet[4] = size;
// 	memcpy(packet + 8, data, size);
// 	for (uint32_t i = 0; i < size + 8; i++)
// 		std::cout << std::to_string(packet[i]) << " ";
// 	std::cout << std::endl;
// 	connection.send(packet, size + 8);
// 	packetIndex++;
// 	delete[] packet;
// }

// int main()
// {
// 	pn::tcp::Server server;
// 	server.bind("0.0.0.0", 8000);
// 	server.listen([&](pn::tcp::Connection &connection, void *)
// 				  { 
// 					std::cout << "connection" << std::endl;
// 					Send(connection, 8, "abcdefgh");
// 					Send(connection, 12, "abcdefghijkl");
// 					Send(connection, 4, "abcd");
// 					return true; });
// }

int main()
{
    pn::init();
	pn::tcp::Server tcpServer;
	int32_t error = tcpServer.bind("0.0.0.0", 60006);
	Assert(!error);

	GameServer server{tcpServer};
	server.Listen();
}
