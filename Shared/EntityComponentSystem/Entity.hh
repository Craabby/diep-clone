#pragma once

#include <array>
#include <cstdint>
#include <optional>

#include <Shared/EntityComponentSystem/Component/Physics.hh>
#include <Shared/EntityComponentSystem/Component/Camera.hh>

namespace shared::ecs
{
	struct Entity
	{
		static constexpr uint32_t MAX_ITEMS = 5;
		uint32_t id;
		std::optional<component::Physics> physics;
		std::optional<component::Camera> camera;

		Entity();
        Entity(const Entity &) = delete;

		void Reset();
		void WriteBinary(Writer &writer);
		void ReadBinary(Reader &reader, bool created = true);
	};
}
