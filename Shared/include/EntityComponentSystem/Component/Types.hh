#pragma once

namespace shared::ecs::component::types
{
    constexpr size_t COMPONENT_COUNT = 3;
    
    // TODO: check if the constructor has signature `Entity *`
    template <class Component>
    concept component = requires(Component a)
    {
        a.updated;
        a.WriteBinary;
        Component::ID;
    };
}
