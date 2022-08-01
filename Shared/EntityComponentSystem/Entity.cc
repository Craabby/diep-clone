#include <Shared/EntityComponentSystem/Entity.hh>

#include <iostream>

#include <Shared/Coder/Writer.hh>
#include <Shared/Coder/Reader.hh>

namespace shared::ecs
{
	Entity::Entity()
	{
	}

	Entity::~Entity()
	{
		if (Has<component::Camera>())
			delete &Get<component::Camera>();
		if (Has<component::Physics>())
			delete &Get<component::Physics>();
	}

	void Entity::Reset()
	{
		if (Has<component::Camera>())
			Get<component::Camera>().updated = false;
		if (Has<component::Physics>())
			Get<component::Physics>().updated = false;
	}

	// used for both creations and updates
	void Entity::WriteBinary(Writer &writer)
	{
		uint32_t componentFlags = 0;

		componentFlags |= (Has<component::Camera>() && Get<component::Camera>().updated) << component::Camera::ID;
		componentFlags |= (Has<component::Physics>() && Get<component::Physics>().updated) << component::Physics::ID;

		writer.Vu(componentFlags);

		if (Has<component::Camera>() && Get<component::Camera>().updated)
			Get<component::Camera>().WriteBinary(writer);
		if (Has<component::Physics>() && Get<component::Physics>().updated)
			Get<component::Physics>().WriteBinary(writer);
	}

	void Entity::ReadBinary(Reader &reader, bool created)
	{
		uint32_t componentFlags = reader.Vu();

		if (componentFlags & (1 << component::Camera::ID))
		{
			if (created)
				Append<component::Camera>();
			Get<component::Camera>().ReadBinary(reader);
		}
		if (componentFlags & (1 << component::Physics::ID))
		{
			if (created)
				Append<component::Physics>();
			Get<component::Physics>().ReadBinary(reader);
		}
	}
}
