#pragma once

#include <array>
#include <bitset>
#include <stdexcept>

#include <EntityComponentSystem/Component/Types.hh>

namespace shared
{
    class Simulation;

    namespace coder
    {
        class Writer;
    }
}

namespace shared::ecs
{
    class Entity
    {
        Simulation *simulation;
        std::array<void *, component::types::componentCount> m_Components;

    public:
        uint32_t id;
        Entity(Simulation *);
        ~Entity();

        void WriteBinary(coder::Writer &, bool);

        template <component::types::component Component>
        Component &Get()
        {
            if (m_Components[Component::ID] == nullptr)
                throw std::runtime_error("tried to get nonexistant component from entity");
            return *(Component *)&m_Components[Component::ID];
        }

        template <component::types::component Component>
        void AppendComponent()
        {
            if (m_Components[Component::ID] != nullptr)
                throw std::runtime_error("tried to append component to entity which already has the component");

            m_Components[Component::ID] = (void *)(new Component(this));
        }

        template <component::types::component Component>
        bool Has()
        {
            return m_Components[Component::ID] != nullptr;
        }
    };
}
