#include <Client.hh>

#include <algorithm>
#include <vector>

#include <IXWebSocket.h>

#include <Coder/Writer.hh>
#include <EntityComponentSystem/Entity.hh>
#include <ServerSimulation.hh>

using shared::ecs::Entity;

namespace server
{
    Client::Client(Simulation *simulation, ix::WebSocket *socket)
        : socket(socket),
          simulation(simulation)
    {
    }

    // TODO: use spatial hashing to render only the close entities
    // TODO: move to shared::Simulation
    std::vector<Entity *> Client::FindEntitiesInView()
    {
        std::vector<Entity *> entities;

        for (Entity *entity : simulation->entities)
            entities.push_back(entity);

        return entities;
    }

    void Client::SendUpdate()
    {
        std::vector<Entity *> entitiesInView = FindEntitiesInView();
        shared::coder::Writer writer;
        writer.U8(0);

        // TODO: fix this ugly pile of shit
        simulation->WriteBinary(writer, [entitiesInView, this](Entity *entity) -> shared::EntityUpdateType
                                { 
            if (std::find(entitiesInView.begin(), entitiesInView.end(), entity) == entitiesInView.end())
            {
                view.erase(std::find(view.begin(), view.end(), entity));
                return shared::EntityUpdateType::Deleted;
            }

            bool isCreation = std::find(view.begin(), view.end(), entity) == view.end();

            if (isCreation)
            {
                view.push_back(entity);
                return shared::EntityUpdateType::Created;
            }
            else
                return shared::EntityUpdateType::Updated; });

        socket->sendBinary(writer.Data());
    }
}
