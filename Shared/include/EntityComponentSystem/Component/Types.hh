#pragma once

namespace shared::ecs::component::types
{
    constexpr size_t componentCount = 2;
    
    // TODO: check if the constructor has signature `Entity *`
    template <class Component>
    concept component = requires(Component a)
    {
        // check if the component instance has `updated` and a static `ID`
        a.updated;
        Component::ID;
    };
}
