#include <Client.hh>

#include <algorithm>
#include <vector>

#include <IXWebSocket.h>

#include <Coder/Writer.hh>
#include <EntityComponentSystem/Entity.hh>
#include <ServerSimulation.hh>

namespace server
{
    Client::Client(Simulation *simulation, ix::WebSocket *socket)
        : socket(socket),
          simulation(simulation)
    {
    }

    void Client::SendUpdate()
    {
        shared::coder::Writer writer;
        writer.U8(0);
        simulation->WriteBinary(writer, [this](shared::ecs::Entity *entity)
                                { return std::find_if(view.begin(), view.end(), [entity](shared::ecs::Entity *possibleCreation)
                                                      { return possibleCreation->id == entity->id; }) == view.end(); });

        socket->sendBinary(writer.Data());
    }
}
