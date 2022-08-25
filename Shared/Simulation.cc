#include <Shared/Simulation.hh>

#include <algorithm>
#include <std/algorithm.hh>
#include <std/vector.hh>

#include <Shared/Coder/Reader.hh>
#include <Shared/Coder/Writer.hh>

namespace shared
{
    std2::Vector<uint32_t> Simulation::FindEntitiesInView(ecs::component::Camera *viewer)
    {
        std2::Vector<uint32_t> ids;

        for (uint32_t i = 0; i < MAX_ITEMS; i++)
        {
            if (entityFactory.Exists(i))
                ids.Emplace(i);
        }

        return ids;
    }

    EntityUpdateType Simulation::FindEntityUpdateType(uint32_t id, ecs::component::Camera *viewer)
    {
        using ecs::component::Camera;

        ecs::Entity &entity = entityFactory.Get(id);
        if (entity.camera && entity.camera->ownerId != viewer->ownerId)
            return EntityUpdateType::Private;

        std2::Vector<uint32_t> entitiesInView = FindEntitiesInView(viewer);
        if (std2::Find(entitiesInView.begin(), entitiesInView.end(), id) == entitiesInView.end())
        {
            // delete
            viewer->view.Erase<true>(std2::Find(viewer->view.begin(), viewer->view.end(), id).Index());
            return EntityUpdateType::Deleted;
        }

        return EntityUpdateType::Updated;
    }

    void Simulation::WriteBinary(Writer &writer, ecs::component::Camera *viewer)
    {
        std2::Vector<uint32_t> deletions;
        std2::Vector<uint32_t> updates;

        std2::Vector<uint32_t> entitiesInView = FindEntitiesInView(viewer);

        for (uint32_t entityId : entitiesInView)
        {
            EntityUpdateType updateType = FindEntityUpdateType(entityId, viewer);

            if (updateType == EntityUpdateType::Deleted)
                deletions.Emplace(entityId);
            if (updateType == EntityUpdateType::Updated)
                updates.Emplace(entityId);
        }

        // the id may end up being 0
        // the arrays are null terminated
        for (uint32_t id : deletions)
            writer.Vu(id + 1);
        writer.U8(0);
        for (uint32_t id : updates)
        {
            writer.Vu(id + 1);
            entityFactory.Get(id).WriteBinary(writer);
        }
        writer.U8(0);
    }

    void Simulation::ReadBinary(Reader &reader)
    {
        while (true)
        {
            uint32_t id = reader.Vu();
            if (id == 0)
                break;
            id--;

            entityFactory.Delete(id);
        }

        while (true)
        {
            uint32_t id = reader.Vu();
            if (id == 0)
                break;
            id--;

            bool isCreated = entityFactory.Exists(id) == false;

            if (isCreated)
                entityFactory.Create(id);
            entityFactory.Get(id).ReadBinary(reader, isCreated);
        }
    }
}
