#pragma once

#include <array>
#include <cstdint>
#include <std2/optional.hh>

#include <Shared/EntityComponentSystem/Component/Arena.hh>
#include <Shared/EntityComponentSystem/Component/Physics.hh>
#include <Shared/EntityComponentSystem/Component/Camera.hh>

namespace shared::ecs
{
	struct Entity
	{
		static constexpr uint32_t MAX_ITEMS = 1 << 17;
		uint32_t id;
		std2::Optional<component::Arena> arena;
		std2::Optional<component::Physics> physics;
		std2::Optional<component::Camera> camera;

		Entity();
		Entity(const Entity &) = delete;

		void Tick();
		void Reset();
		void WriteBinary(Writer &writer);
		void ReadBinary(Reader &reader, bool created = true);
	};
}
