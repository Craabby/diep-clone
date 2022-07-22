#pragma once

#include <cstdint>

#include <Shared/EntityComponentSystem/Component/Physics.hh>
#include <Shared/Optional.hh>

namespace shared::ecs
{
	class Entity
	{
	public:
		Optional<component::Physics> physics;

		static constexpr uint32_t MAX_ITEMS = 131072;
		uint32_t id;

		Entity();

        void WriteBinary(Writer &, bool isCreation);
        void ReadBinary(Reader &, bool isCreation);
	};
}
