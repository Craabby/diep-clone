#pragma once

#include <std/vector.hh>

#include <Shared/Factory.hh>
#include <Shared/EntityComponentSystem/Entity.hh>

namespace shared
{
    namespace ecs::component
    {
        class Camera;
    }
    enum class EntityUpdateType : uint8_t
    {
        Updated,
        Deleted,
        Private
    };

    struct Simulation
    {
        static constexpr uint32_t MAX_ITEMS = 4;
        Factory<ecs::Entity> entityFactory;
        uint32_t id;

        Simulation() = default;
        Simulation(const Simulation &) = delete;

        void WriteBinary(Writer &, ecs::component::Camera *viewer);
        void ReadBinary(Reader &);
        std2::Vector<uint32_t> FindEntitiesInView(ecs::component::Camera *viewer);
        EntityUpdateType FindEntityUpdateType(uint32_t id, ecs::component::Camera *);
    };
}
