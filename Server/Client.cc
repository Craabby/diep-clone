#include <Server/Client.hh>

#include <cmath>

#include <polynet.hpp>

#include <Server/GameServer.hh>
#include <Shared/Util.hh>

Client::Client(GameServer *server, pn::tcp::Connection socket)
    : server(server),
      socket(socket),
      camera(server->simulation.entityFactory.Create())
{
    std::optional<shared::ecs::component::Camera> &camera = server->simulation.entityFactory.Get(this->camera).camera;
    camera.emplace(this->camera);
    camera->child = server->simulation.entityFactory.Create();
    uint32_t child = camera->child;
    server->simulation.entityFactory.Get(child).physics.emplace(child);
    shared::ecs::component::Physics &childPhysics = *server->simulation.entityFactory.Get(child).physics;
    float mapSize = server->simulation.entityFactory.Get(server->arena).arena->mapSize;
    childPhysics.xPosition = shared::RandomFloat() * mapSize;
    childPhysics.yPosition = shared::RandomFloat() * mapSize;
    float angle = shared::RandomFloat() * 3.1415927410125732;
    childPhysics.xVelocity = cos(angle) * 5;
    childPhysics.yVelocity = sin(angle) * 5;
}

void Client::Delete()
{
    uint32_t child = server->simulation.entityFactory.Get(camera).camera->child;
    if (child != 0)
        server->simulation.entityFactory.Delete(child);
    server->simulation.entityFactory.Delete(camera);
}

void Client::Tick()
{
    shared::Writer writer;
    writer.U8(0);
    server->simulation.WriteBinary(writer, &*server->simulation.entityFactory.Get(camera).camera);

    Send(writer);
}

void Client::Send(const shared::Writer &writer)
{
    uint32_t size = writer.Data().size();
    const uint8_t *data = writer.Data().data();
	char *packet = new char[size + 8];
	*(uint32_t *)packet = packetIndex;
	*(uint32_t *)&packet[4] = size;
	memcpy(packet + 8, data, size);
	socket.send(packet, size + 8);
    for (uint32_t i = 0; i < size + 8; i++)
        std::cout << std::to_string((uint8_t)packet[i]) << " ";
    std::cout << std::endl;
	packetIndex++;
	delete[] packet;
}

bool Client::operator==(const Client &other)
{
    return camera == other.camera;
}
