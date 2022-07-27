#include <Shared/Simulation.hh>

#include <algorithm>

namespace shared
{
    Simulation::Simulation()
    {
    }

    void Simulation::RunGameLoop()
    {
    }

    std::vector<uint32_t> Simulation::FindEntitiesInView(ecs::component::Camera *viewer)
    {
        std::vector<uint32_t> ids;

        for (uint32_t i = 0; i < MAX_ITEMS; i++)
        {
            if (entityFactory.Exists(i))
                ids.push_back(i);
        }

        return ids;
    }

    EntityUpdateType Simulation::FindEntityUpdateType(uint32_t id, ecs::component::Camera *viewer)
    {
        using ecs::component::Camera;

        ecs::Entity &entity = entityFactory.Get(id);
        if (entity.Has<Camera>() && entity.Get<Camera>().ownerId != viewer->ownerId)
            return EntityUpdateType::Private;

        std::vector<uint32_t> entitiesInView = FindEntitiesInView(viewer);
        if (std::find(entitiesInView.begin(), entitiesInView.end(), id) == entitiesInView.end())
        {
            // delete
            viewer->view.erase(std::find(viewer->view.begin(), viewer->view.end(), id));
            return EntityUpdateType::Deleted;
        }

        bool isCreation = std::find(viewer->view.begin(), viewer->view.end(), id) == viewer->view.end();

        if (isCreation)
        {
            viewer->view.push_back(id);
            return EntityUpdateType::Created;
        }
        else
            return EntityUpdateType::Updated;
    }

    void Simulation::WriteBinary(Writer &writer, ecs::component::Camera *viewer)
    {
        std::vector<uint32_t> deletions;
        std::vector<uint32_t> updates;
        std::vector<uint32_t> creations;

        std::vector<uint32_t> entitiesInView = FindEntitiesInView(viewer);

        for (uint32_t entityId : entitiesInView)
        {
            EntityUpdateType updateType = FindEntityUpdateType(entityId, viewer);
        }
    }

    void Simulation::ReadBinary(Reader &)
    {
        
    }
}
