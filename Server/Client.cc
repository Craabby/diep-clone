#include <Server/Client.hh>

#include <cmath>
#include <std/optional.hh>

#include <polynet.hpp>

#include <Server/GameServer.hh>
#include <Shared/Util.hh>

Client::Client(GameServer *server, pn::tcp::Connection &&socket)
    : server(server),
      socket(std2::Move(socket)),
      camera(server->simulation.entityFactory.Create())
{
    std2::Optional<shared::ecs::component::Camera> &camera = server->simulation.entityFactory.Get(this->camera).camera;
    camera.Emplace(this->camera);
    camera->child = server->simulation.entityFactory.Create();
    uint32_t child = camera->child;
    server->simulation.entityFactory.Get(child).physics.Emplace(child);
    shared::ecs::component::Physics &childPhysics = *server->simulation.entityFactory.Get(child).physics;
    float mapSize = server->simulation.entityFactory.Get(server->arena).arena->mapSize;
    childPhysics.xPosition = shared::RandomFloat() * mapSize;
    childPhysics.yPosition = shared::RandomFloat() * mapSize;
    float angle = shared::RandomFloat() * 3.1415927410125732;
    childPhysics.xVelocity = cos(angle) * 5;
    childPhysics.yVelocity = sin(angle) * 5;
}

Client::~Client()
{
    uint32_t child = server->simulation.entityFactory.Get(camera).camera->child;
    if (child != 0)
        server->simulation.entityFactory.Delete(child);
    server->simulation.entityFactory.Delete(camera);
}

bool Client::Connected()
{
    char thing = 69;
    return socket.recv(&thing, 1, MSG_DONTWAIT) != 0;
}

void Client::Tick()
{
    shared::Writer writer;
    writer.U8(0);
    server->simulation.WriteBinary(writer, &*server->simulation.entityFactory.Get(camera).camera);

    Send(writer);
}

int32_t Client::Send(const shared::Writer &writer)
{
    Assert(Connected());
    uint32_t size = writer.Data().Size();
    const uint8_t *data = writer.Data().Data();
	char *packet = new char[size + 8];
	*(uint32_t *)packet = packetIndex;
	*(uint32_t *)&packet[4] = size;
	std2::memory::Move(packet + 8, data, size);
	int32_t error = socket.send(packet, size + 8);
	packetIndex++;
	delete[] packet;

    return error;
}

bool Client::operator==(const Client &other)
{
    return camera == other.camera;
}
