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
        class Reader;
        class Writer;
    }
}

namespace shared::ecs
{
    class Entity
    {
        Simulation *simulation;
        std::array<void *, component::types::COMPONENT_COUNT> m_Components = {nullptr, nullptr};

        void WriteComponents(coder::Writer &);
        void WriteBinaryCreation(coder::Writer &);
        void WriteBinaryUpdate(coder::Writer &);
        void FromBinaryCreation(coder::Reader &);
        void FromBinaryUpdate(coder::Reader &);
        void ReadComponents(coder::Reader &);

    public:
        uint32_t id;
        Entity(Simulation *);
        ~Entity();

        // template spam :D
        template <bool isCreation>
        void WriteBinary(coder::Writer &writer)
        {
            if constexpr (isCreation) WriteBinaryCreation(writer);
            else WriteBinaryUpdate(writer);
        }
        template <bool isCreation>
        void FromBinary(coder::Reader &reader)
        {
            if constexpr (isCreation) FromBinaryCreation(reader);
            else FromBinaryUpdate(reader);
        }

        template <component::types::component Component>
        Component &Get()
        {
            if (m_Components[Component::ID] == nullptr)
                throw std::runtime_error("tried to get nonexistant component from entity");
            return *(Component *)m_Components[Component::ID];
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
