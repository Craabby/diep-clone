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

		void WriteComponents(Writer &);
		void WriteBinaryCreation(Writer &);
		void WriteBinaryUpdate(Writer &);
		void ReadBinaryCreation(Reader &);
		void ReadBinaryUpdate(Reader &);
		void ReadComponents(Reader &);

	public:
		static constexpr uint32_t MAX_ITEMS = 131072;
		uint32_t id;

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

		template <bool isCreation>
		void WriteBinary(Writer &writer)
		{
			if constexpr (isCreation)
				WriteBinaryCreation(writer);
			else
				WriteBinaryUpdate(writer);
		}
		template <bool isCreation>
		void ReadBinary(Reader &reader)
		{
			if constexpr (isCreation)
				ReadBinaryCreation(reader);
			else
				ReadBinaryUpdate(reader);
		}
	};
}
