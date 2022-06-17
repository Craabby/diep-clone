#pragma once

#include <array>
#include <cstdint>
#include <functional>
#include <vector>

#include <EntityComponentSystem/Component/Types.hh>

namespace shared
{
    namespace coder
    {
        class Reader;
        class Writer;
    }

    namespace ecs
    {
        class Entity;
        namespace component
        {
            class Basic;
            class Physics;
        }
    }

    class Simulation
    {
        uint32_t nextId = 0;
        std::vector<ecs::Entity *> entities;
        std::array<std::vector<void *>, ecs::component::types::COMPONENT_COUNT> entityComponentTable;

    public:
        Simulation();

        ecs::Entity *CreateEntity();
        void Tick();
        void RunGameLoop();
        uint32_t GetNextId();

        coder::Writer WriteBinary(std::function<bool(ecs::Entity *)> isCreation);
        void FromBinary(coder::Reader &reader);

        template <ecs::component::types::component Component>
        const std::vector<Component *> &Get()
        {
            return *(std::vector<Component *> *)&entityComponentTable[Component::ID];
        }
    };
}
