#pragma once

#include <array>
#include <cassert>
#include <cstdint>
#include <optional>

#include <Shared/EntityComponentSystem/Component/Physics.hh>
#include <Shared/EntityComponentSystem/Component/Camera.hh>

namespace shared::ecs
{
	struct Entity
	{
		static constexpr uint32_t MAX_ITEMS = 131072;
		uint32_t id;
		uint64_t magic = 111111111111111;
		std::optional<component::Camera> camera;
		std::optional<component::Physics> physics;

		Entity();
        Entity(const Entity &) = delete;

		void Reset();
		void WriteBinary(Writer &writer);
		void ReadBinary(Reader &reader, bool created = true);
	};
}
