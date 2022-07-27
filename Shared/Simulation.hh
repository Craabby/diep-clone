#pragma once

#include <Shared/Factory.hh>
#include <Shared/EntityComponentSystem/Component/Camera.hh>
#include <Shared/EntityComponentSystem/Entity.hh>

namespace shared
{
    enum class EntityUpdateType : uint8_t
    {
        Updated,
        Created,
        Deleted,
        Private
    };

    class Simulation
    {
        void Tick();
        std::vector<uint32_t> FindEntitiesInView(ecs::component::Camera *viewer);
        EntityUpdateType FindEntityUpdateType(uint32_t id, ecs::component::Camera *);

    public:
        static constexpr uint32_t MAX_ITEMS = 4;

        Factory<ecs::Entity> entityFactory;
        uint32_t id;

        Simulation();
        void RunGameLoop();

        void WriteBinary(Writer &, ecs::component::Camera *viewer);
        void ReadBinary(Reader &);
    };
}
