#pragma once

namespace shared::ecs::component::types
{
    template <class Component>
    concept component = requires(Component a)
    {
        // check if the component instance has `updated` and a static `ID`
        a.updated;
        Component::ID;
    };
}
