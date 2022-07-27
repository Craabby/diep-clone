#pragma once

#include <cstdint>
#include <array>

#include <Shared/EntityComponentSystem/Component/Physics.hh>
#include <Shared/EntityComponentSystem/Component/Camera.hh>
#include <Shared/Optional.hh>

namespace shared::ecs
{
	class Entity
	{
		std::array<void *, 2> components = {nullptr};
	public:

		static constexpr uint32_t MAX_ITEMS = 131072;
		uint32_t id;

		Entity();

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
			components[T::ID] = new T();
		}

		template <typename T>
		bool Has()
		{
			return components[T::ID] != nullptr;
		}

        void WriteBinary(Writer &, bool isCreation);
        void ReadBinary(Reader &, bool isCreation);
	};
}
