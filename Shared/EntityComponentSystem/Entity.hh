#pragma once

#include <array>
#include <cassert>
#include <cstdint>

#include <Shared/EntityComponentSystem/Component/Physics.hh>
#include <Shared/EntityComponentSystem/Component/Camera.hh>

namespace shared::ecs
{
	struct Entity
	{
		static constexpr uint32_t MAX_ITEMS = 131072;
		uint32_t id;
		std::array<void *, 2> components = {nullptr};

		Entity();
		~Entity();

		void Reset();

		template <typename T>
		T &Get()
		{
			assert(components[T::ID] != nullptr);
			return *(T *)components[T::ID];
		}

		template <typename T>
		void Append()
		{
			assert(components[T::ID] == nullptr);
			components[T::ID] = new T(id);
		}

		template <typename T>
		bool Has()
		{
			return components[T::ID] != nullptr;
		}

		void WriteBinary(Writer &writer);
		void ReadBinary(Reader &reader, bool created = true);
	};
}
